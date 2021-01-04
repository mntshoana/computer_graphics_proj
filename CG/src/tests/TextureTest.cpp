#include "TextureTest.h"

TextureTest::TextureTest()
	: shader(path + "/shaders/Basic.shader"), texture( path +"/textures/texture.jpg")
{
	shape = std::make_unique<Square>(20.0f);

	ib = std::make_unique<IndexBuffer>(&shape->indices[0] , shape->getIndexSizeb());
	vb = std::make_unique<VertexBuffer>(&shape->vertices[0], shape->getVertexSizeb());
	
	attr.push<float>(3);
	attr.push<float>(2);
	voaState.AddBuffers(*vb, attr);

	translationVec = glm::vec3(0.0f, 0.0f, 0.0f);
	scaleVec = glm::vec3(1.0f, 1.0f, 1.0f);

	view = glm::lookAt(
		glm::vec3(0, 0, 50), // the position of your camera, in world space
		glm::vec3(0, 0, 0),  // where you want to look at, in world space
		glm::vec3(0, 1, 0)   // (0,-1,0) would make you looking upside-down
	);

	projection = glm::ortho(-(float)displayWidth / 2, (float)displayWidth / 2,		// left, right
							-(float)displayHeight / 2, (float)displayHeight / 2,	// bottom, top 
							-depth, depth);											// zNear, zFar								

	glEnable(GL_BLEND); ASSESS_LINE;
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); ASSESS_LINE;

	shader.Bind();
	texture.Bind();
	shader.SetUniform("u_texture", 1); // needs to match bound texture slot	
	shader.SetUniform("u_projection", projection);
	shader.SetUniform("u_view", view);
	shader.SetUniform("u_model", glm::mat4(1.0f));
}
TextureTest::~TextureTest()
{
	glDisable(GL_BLEND); ASSESS_LINE;

	shader.Unbind();
	texture.Unbind();
	ib->Unbind();
	vb->Unbind();
	voaState.UnBind();
}
void TextureTest::OnUpdate(float deltaTime)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); ASSESS_LINE;
	renderer.Clear();
}
void TextureTest::OnRender()
{
	transformation = glm::scale(glm::translate(glm::mat4(1), translationVec), scaleVec);
	shader.SetUniform("u_transformation", transformation);

	renderer.Draw(voaState, *vb, *ib);
}
void TextureTest::OnImGuiRender()
{
	// A simple ImGui window. We use a Begin/End pair to created a named window.

	ImGui::SliderFloat("X", &translationVec.x, -(float)displayWidth/2, (float)displayWidth/2); // Edit 1 float using a slider 
	ImGui::SliderFloat("Y", &translationVec.y, -(float)displayHeight / 2, (float)displayHeight / 2); // Edit 1 float using a slider from 0.0f to 1.0f
	ImGui::SliderFloat2("Scale", &scaleVec.x, 20.0f, 100.0f);
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
		1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}
