#include "Texture.h"

Texture::Texture(const std::string& imagePath)
	: textureID(0), filePath(imagePath), buffer(nullptr), width(0), height(0), bitsPerPixel(0)
{
	glGenTextures(1, &textureID); ASSESS_LINE;
	glBindTexture(GL_TEXTURE_2D, textureID); ASSESS_LINE;

	// load texture
	stbi_set_flip_vertically_on_load(1);
	buffer = stbi_load(filePath.c_str(), &width, &height, &bitsPerPixel, 4); // 4 Desired Channels RGBA
	if (!buffer)
		; // Error, file did not load

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); ASSESS_LINE; // linearly resample everything
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); ASSESS_LINE; // scale up if area larger than texture size
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); ASSESS_LINE; // horizontal wrap mode shouldn't extend the area
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); ASSESS_LINE;// vertical wrap mode shouldn't extend the area

	glTexImage2D(GL_TEXTURE_2D, 0,		// Not a multilevel texture
		GL_RGBA8,			// internal format (How openGL will store your data
		width,
		height,
		0,					// no border
		GL_RGBA,			// format of the data we are supplying
		GL_UNSIGNED_BYTE,	// type of data we are supplying
		buffer				// pointer to pixels
	); ASSESS_LINE;

	glBindTexture(GL_TEXTURE_2D, textureID); ASSESS_LINE;

	// Clean up
	if (buffer) // contains data
		stbi_image_free(buffer);
}

Texture::~Texture()
{
	glBindTexture(GL_TEXTURE_2D, 0); ASSESS_LINE;
	glDeleteTextures(1, &textureID); ASSESS_LINE;
}

void Texture::Bind(unsigned int slot)
{
	glActiveTexture(GL_TEXTURE0 + slot); ASSESS_LINE;
	glBindTexture(GL_TEXTURE_2D, textureID); ASSESS_LINE;
}

void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0); ASSESS_LINE;
}

int Texture::GetWidth() const
{
	return width;
}

int Texture::GetHeight() const
{
	return height;
}
