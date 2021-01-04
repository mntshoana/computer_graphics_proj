#include "Texture3DTest.h"

Texture3DTest::Texture3DTest()
	: shader(path + "/shaders/Basic.shader"), texture(path + "/textures/jupiter.ppm")
{
	shape = std::make_unique<Cube>(130.0f);

	ib = std::make_unique<IndexBuffer>(&shape->indices[0], shape->getIndexSizeb());
	vb = std::make_unique<VertexBuffer>(&shape->vertices[0], shape->getVertexSizeb());

	attr.push<float>(3);
	attr.push<float>(2);
	voaState.AddBuffers(*vb, attr);

	scale = glm::vec3(1.0f, 1.0f, 1.0f);
	angle = glm::pi<float>();
	rotar = glm::vec3(1.0f, 1.0f, 0.0f);
	translation = glm::vec3(0);
	model = glm::mat4(1.0f);

	view = glm::lookAt(
		glm::vec3(0, 0, 100), // the position of your camera, in world space
		glm::vec3(0, 0, 0),  // where you want to look at, in world space
		glm::vec3(0, 1, 0)   // (0,-1,0) would make you looking upside-down
	);

	projection = glm::ortho(-(float)displayWidth / 2, (float)displayWidth / 2,		// left, right
							-(float)displayHeight / 2, (float)displayHeight / 2,	// bottom, top 
							-depth, depth);										// zNear, zFar		


	glEnable(GL_BLEND); ASSESS_LINE;
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); ASSESS_LINE;
	glEnable(GL_DEPTH_TEST); ASSESS_LINE;
	glDepthMask(GL_TRUE); ASSESS_LINE;
	glEnable(GL_STENCIL_TEST); ASSESS_LINE;

	shader.Bind();
	texture.Bind();

	shader.SetUniform("u_texture", 1); // needs to match bound texture slot	
	shader.SetUniform("u_projection", projection);
	shader.SetUniform("u_view", view);
	shader.SetUniform("u_model", model);
}
Texture3DTest::~Texture3DTest()
{
	glDisable(GL_BLEND); ASSESS_LINE;
	glDisable(GL_DEPTH_TEST); ASSESS_LINE;
	glDepthMask(GL_FALSE); ASSESS_LINE;
	glDisable(GL_STENCIL_TEST); ASSESS_LINE;

	shader.Unbind();
	texture.Unbind();
	ib->Unbind();
	vb->Unbind();
	voaState.UnBind();
}
void Texture3DTest::OnUpdate(float deltaTime)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); ASSESS_LINE;
	renderer.Clear();
}
void Texture3DTest::OnRender()
{
	transformation = glm::translate(glm::mat4(1.0f), translation);
	transformation = glm::scale(transformation, scale);
	transformation = glm::rotate(transformation, angle, rotar);
	shader.SetUniform("u_transformation", transformation);

	renderer.Draw(voaState, *vb, *ib);
}
void Texture3DTest::OnImGuiRender()
{
	// A simple ImGui window. We use a Begin/End pair to created a named window.
	ImGui::SliderFloat("X", &translation.x, -(float)displayWidth / 2, (float)displayWidth / 2); // Edit 1 float using a slider 
	ImGui::SliderFloat("Y", &translation.y, -(float)displayHeight / 2, (float)displayHeight / 2); // Edit 1 float using a slider from 0.0f to 1.0f
	ImGui::SliderFloat("Z", &translation.z, -depth, depth); // Edit 1 float using a slider from 0.0f to 1.0f
	ImGui::SliderFloat2("Scale", &scale.x, 1.0f, 10.0f);
	ImGui::SliderFloat("angle", &angle, 0.0f , 2 * glm::pi<float>());
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
		1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}
