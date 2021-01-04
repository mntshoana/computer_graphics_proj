#shader vertex
#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 texturePosition;
out vec2 vtexturePosition;

uniform mat4 u_model, u_view, u_projection, u_transformation;
void main()
{
	gl_Position = u_projection  * u_view * u_model * u_transformation * position ;
	vtexturePosition =  texturePosition;
}

#shader fragment
#version 330 core

in vec2 vtexturePosition;
layout (location=0) out vec4 color;
uniform sampler2D u_texture;

void main()
{
	color = texture(u_texture, vtexturePosition);
}
