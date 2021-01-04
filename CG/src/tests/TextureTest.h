#ifndef TEXTURE_COLOR_TEST
#define TEXTURE_COLOR_TEST


#include "tests/Test.h"

class TextureTest : public Test
{
public:
	TextureTest();
	~TextureTest();

	void OnUpdate(float deltaTime) override;
	void OnRender() override;
	void OnImGuiRender() override;

private:
	VertexArrayObject voaState;
	Renderer renderer;
	std::unique_ptr<VertexBuffer> vb;
	std::unique_ptr<IndexBuffer> ib;
public:
	Attribute attr;
	Shader shader;
	Texture texture;
private:
	std::unique_ptr<Shape> shape;
	glm::mat4 projection, view;
	glm::mat4 transformation;

	glm::vec3 translationVec;
	glm::vec3 scaleVec;

};
#endif
