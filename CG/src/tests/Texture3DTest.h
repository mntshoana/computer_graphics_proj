#ifndef TEXTURE_3D_TEST
#define TEXTURE_3D_TEST

#include "Test.h"


class Texture3DTest : public Test
{
public:
	Texture3DTest();
	~Texture3DTest();

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
	glm::mat4 model, view, projection, transformation;

	glm::vec3 scale;

	float angle;
	glm::vec3 rotar;
	glm::vec3 translation;

};
#endif