#ifndef TEXTURE_CONSTANT
#define TEXTURE_CONSTANT

#include "stb/stb_image.h"
#include "OpenglDebugger.h"

class Texture
{
private:
	unsigned int textureID;
	std::string filePath;
	unsigned char* buffer;
	int width, height, bitsPerPixel;
public:
	Texture(const std::string& imagePath);
	~Texture();

	void Bind(unsigned int slot = 1);
	void Unbind();

	int GetWidth()const;
	int GetHeight()const;
};
#endif // !TEXTURE_CONSTANT
