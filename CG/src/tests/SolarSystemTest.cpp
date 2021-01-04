#include "SolarSystemTest.h"

SolarSystemTest::SolarSystemTest()
	: shader(path + "/shaders/Basic.shader"),
	sun(path + "/textures/sun.ppm"), mercury(path + "/textures/mercury.ppm"),
	venus(path + "/textures/venus.ppm"), earth(path + "/textures/earth.ppm"),
	moon(path + "/textures/moon.ppm"),	mars(path + "/textures/mars.ppm"),
	jupiter(path + "/textures/jupiter.ppm"),	saturn(path + "/textures/saturn.ppm"),
	saturnRing(path + "/textures/saturn-ring.ppm"), uranus(path + "/textures/uranus.ppm"),
	neptune(path + "/textures/neptune.ppm"), pluto(path + "/textures/pluto.ppm")
{
	shape = std::make_unique<Sphere>(50.0f);
	ib = std::make_unique<IndexBuffer>(&shape->indices[0], shape->getIndexCount());
	vb = std::make_unique<VertexBuffer>(&shape->vertices[0], shape->getVertexSizeb());

	attr.push<float>(3);
	attr.push<float>(2);
	voaState.AddBuffers(*vb, attr);

	// Transformation variables
	angle = 0;
	speed = 1;
	rotar = glm::vec3(1.f, 1.f, 0.0f);
	scalor = glm::vec3(0.06f);
	

	projection = glm::perspective(glm::radians(65.0f),  // zoom 90 degrees (extra wide) 30 degrees (zoomed in)
		aspectRatio,
		0.01f,										// zNear
		20*depth);										// zFar		
	
	// Camera position at
	cameraPosition = glm::vec3(0.0, 0.0f, 1000);
	cameraDirection = glm::vec3(0.0f, 0.0f, -500);
	cameraOrientation = glm::vec3(0.0f, 1.0f, 0.0f);

	view = glm::lookAt(
		cameraPosition,						// Camera position
		cameraPosition + cameraDirection,	// where to look at
		cameraOrientation					// orientation (up or upside down)
	);
	// Projection = glm::ortho( -depth, depth, -depth, depth, -depth, depth);

	glEnable(GL_BLEND); ASSESS_LINE;
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); ASSESS_LINE;
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);	
	glEnable(GL_STENCIL_TEST);

	scale = glm::scale(glm::mat4(1), scalor);

	shader.Bind();
	shader.SetUniform("u_texture", 1); // needs to match bound texture slot	
	shader.SetUniform("u_model", model);
	shader.SetUniform("u_view", view);
	shader.SetUniform("u_projection", projection);
	shader.SetUniform("u_transformation", glm::mat4(1));
}

void SolarSystemTest::OnRender()
{
	view = glm::lookAt(
		cameraPosition,						// Camera position
		cameraPosition + cameraDirection,	// where to look at
		cameraOrientation					// orientation (up or upside down)
	);	
	rotation = glm::rotate(glm::mat4(1), angle, rotar);


	sun.Bind();
	model = glm::scale(glm::mat4(1), glm::vec3(109.1f));
	revolve = glm::rotate(glm::mat4(1), angle / 80, rotar);
	transformation = revolve * scale;
	shader.SetUniform("u_model", model);
	shader.SetUniform("u_view", view);
	shader.SetUniform("u_transformation", transformation);
	renderer.Draw(voaState, *vb, *ib);

	// orbit 58.8 / 40
	mercury.Bind();
	model = glm::scale(glm::mat4(1), glm::vec3(0.766f));
	revolve = glm::rotate(glm::mat4(1), angle / 1.47f, glm::vec3(-0.5f, 0.5f, 0));
	transformation = revolve * glm::translate(glm::mat4(1), glm::vec3(281.55f)) * rotation * scale;
	shader.SetUniform("u_model", model);
	shader.SetUniform("u_view", view);
	shader.SetUniform("u_transformation", transformation);
	renderer.Draw(voaState, *vb, *ib);

	// orbit -244.4 / 40
	venus.Bind();
	model = glm::scale(glm::mat4(1), glm::vec3(1.9f));
	revolve = glm::rotate(glm::mat4(1), angle / -3.05f, glm::vec3(-0.5f, 0.5f, 0));
	transformation = revolve * glm::translate(glm::mat4(1), glm::vec3(170.25f)) * rotation * scale;
	shader.SetUniform("u_model", model);
	shader.SetUniform("u_view", view);
	shader.SetUniform("u_transformation", transformation);
	renderer.Draw(voaState, *vb, *ib);
	
	earth.Bind();
	model = glm::scale(glm::mat4(1.0f), glm::vec3(2));
	revolve = glm::rotate(glm::mat4(1), angle, glm::vec3(-0.5f, 0.5f, 0));
	transformation = revolve * glm::translate(glm::mat4(1), glm::vec3(240.05f)) * rotation * scale;
	shader.SetUniform("u_model", model);
	shader.SetUniform("u_view", view);
	shader.SetUniform("u_transformation", transformation);
	renderer.Draw(voaState, *vb, *ib);
	
	// transformation 240.05.1 / scale of 0.55484
	// Orbit 27.4 / 40
	moon.Bind();
	model = glm::scale(glm::mat4(1), glm::vec3(0.55484f));
	revolve = glm::rotate(glm::mat4(1), angle, glm::vec3(-0.5f, 0.5f, 0));
	revolveAroundEarth = glm::rotate(glm::mat4(1), angle / 0.685f, glm::vec3(-0.25f, 0.25f, 0.f));
	transformation = revolve * glm::translate(glm::mat4(1), glm::vec3(865.29f))
					* revolveAroundEarth * glm::translate(glm::mat4(1), glm::vec3(50))
					*rotation* scale; 
	shader.SetUniform("u_model", model);
	shader.SetUniform("u_view", view);
	shader.SetUniform("u_transformation", transformation);
	renderer.Draw(voaState, *vb, *ib);

	// Orbit 1.04 / 40
	mars.Bind();
	model = glm::scale(glm::mat4(1), glm::vec3(1.064f));
	revolve = glm::rotate(glm::mat4(1), angle * 0.54f, glm::vec3(-0.5f, 0.5f, 0));
	transformation = revolve * glm::translate(glm::mat4(1), glm::vec3(610.f)) * rotation * scale;
	shader.SetUniform("u_model", model);
	shader.SetUniform("u_view", view);
	shader.SetUniform("u_transformation", transformation);
	renderer.Draw(voaState, *vb, *ib);
	
	// Orbit 0.415 / 40
	jupiter.Bind();
	model = glm::scale(glm::mat4(1), glm::vec3(22.42f));
	revolve = glm::rotate(glm::mat4(1), angle * 0.44f, glm::vec3(-0.5f, 0.5f, 0));
	transformation = revolve * glm::translate(glm::mat4(1), glm::vec3(54.f))* rotation* scale;
	shader.SetUniform("u_model", model);
	shader.SetUniform("u_view", view);
	shader.SetUniform("u_transformation", transformation);
	renderer.Draw(voaState, *vb, *ib);
	
	
	saturn.Bind();
	model = glm::scale(glm::mat4(1), glm::vec3(18.9f));
	revolve = glm::rotate(glm::mat4(1), angle * 0.49f, glm::vec3(-0.5f, 0.5f, 0));
	transformation = revolve * glm::translate(glm::mat4(1), glm::vec3(165.f)) * rotation * scale;
	shader.SetUniform("u_model", model);
	shader.SetUniform("u_view", view);
	shader.SetUniform("u_transformation", transformation);
	renderer.Draw(voaState, *vb, *ib);

	
	saturnRing.Bind();
	transformation = revolve * glm::translate(glm::mat4(1), glm::vec3(165.f))
								* rotation * glm::scale(scale, glm::vec3(1.5f, 1.5f, 0.15f));
	shader.SetUniform("u_model", model);
	shader.SetUniform("u_view", view);
	shader.SetUniform("u_transformation", transformation);
	renderer.Draw(voaState, *vb, *ib);
	
	// Orbit -0.720 / 40
	uranus.Bind();
	model = glm::scale(glm::mat4(1), glm::vec3(8.02f));
	revolve = glm::rotate(glm::mat4(1), angle * -0.036f, glm::vec3(-0.5f, 0.5f, 0));
	transformation = revolve * glm::translate(glm::mat4(1), glm::vec3(600.f)) * rotation * scale;
	shader.SetUniform("u_model", model);
	shader.SetUniform("u_view", view);
	shader.SetUniform("u_transformation", transformation);
	renderer.Draw(voaState, *vb, *ib);

	
	// Orbit 0.673 / 40
	neptune.Bind();
	model = glm::scale(glm::mat4(1), glm::vec3(7.76f));
	revolve = glm::rotate(glm::mat4(1), angle * 0.03365f, glm::vec3(-0.5f, 0.5f, 0));
	transformation = revolve * glm::translate(glm::mat4(1), glm::vec3(1807.f)) * rotation * scale;
	shader.SetUniform("u_model", model);
	shader.SetUniform("u_view", view);
	shader.SetUniform("u_transformation", transformation);
	renderer.Draw(voaState, *vb, *ib);

	
	// Orbit 6.41 / 40
	pluto.Bind();
	model = glm::scale(glm::mat4(1), glm::vec3(0.372f));
	revolve = glm::rotate(glm::mat4(1), angle * 0.32025f, glm::vec3(-0.5f, 0.5f, 0));
	transformation = revolve * glm::translate(glm::mat4(1), glm::vec3(14568.f)) * rotation * scale;
	shader.SetUniform("u_model", model);
	shader.SetUniform("u_view", view);
	shader.SetUniform("u_transformation", transformation);
	renderer.Draw(voaState, *vb, *ib);
}


void SolarSystemTest::OnImGuiRender()
{
	// A simple ImGui window. We use a Begin/End pair to created a named window.
	ImGui::SliderFloat("speed", &speed, 0.05 , 5);
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
		1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}

void SolarSystemTest::OnUpdate(float deltaTime)
{
	if (angle >= 80 * glm::pi<float>())
		angle = -angle;
	else angle += speed * 0.001f;
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); ASSESS_LINE;
	renderer.Clear();
}

void SolarSystemTest::OnKey(KeyPressedEvent& e)
{
	float temp1, temp2; 
	float deltax = cameraDirection.x - cameraPosition.x;
	float deltay = cameraDirection.y - cameraPosition.y;
	float deltaz = cameraDirection.z - cameraPosition.z;
	switch (e.GetKeycode())
	{
	case  GLFW_KEY_LEFT: // rotate with respect to y
		temp1 = deltax * cosf(glm::radians(0.7f)) + deltaz * sinf(glm::radians(0.7f));
		temp2 = -deltax * sinf(glm::radians(0.7f)) + deltaz * cosf(glm::radians(0.7f));
		cameraDirection = glm::vec3(cameraPosition.x + temp1, cameraDirection.y, cameraPosition.z + temp2);
		return;
	case  GLFW_KEY_RIGHT:
		temp1 = deltax * cosf(glm::radians(-0.7f)) + deltaz * sinf(glm::radians(-0.7f));
		temp2 = -deltax * sinf(glm::radians(-0.7f)) + deltaz * cosf(glm::radians(-0.7f));
		cameraDirection = glm::vec3(cameraPosition.x + temp1, cameraDirection.y, cameraPosition.z + temp2);
		return;
	case  GLFW_KEY_UP: 
		temp1 = deltay * cosf(glm::radians(0.9f)) - deltaz * sinf(glm::radians(0.9f));
		temp2 = deltay * sinf(glm::radians(0.9f)) + deltaz * cosf(glm::radians(0.9f));
		cameraDirection = glm::vec3(cameraDirection.x, cameraPosition.y + temp1, cameraPosition.z + temp2); 
		return;
	case  GLFW_KEY_DOWN:
		temp1 = deltay * cosf(glm::radians(-0.9f)) - deltaz * sinf(glm::radians(-0.9f));
		temp2 = deltay * sinf(glm::radians(-0.9f)) + deltaz * cosf(glm::radians(-0.9f));
		cameraDirection = glm::vec3(cameraDirection.x, cameraPosition.y + temp1, cameraPosition.z + temp2);
		return;
	case GLFW_KEY_ESCAPE:
		cameraPosition = glm::vec3(0.0, 0.0f, 500);
		cameraDirection = glm::vec3(0.0f, 0.0f, -500);
		cameraOrientation = glm::vec3(0.0f, 1.0f, 0.0f);
		return;
	}
}
void SolarSystemTest::OnScroll(MouseScrollEvent& e)
{
	cameraPosition += e.GetYOffset()* 0.05f * cameraDirection;
}

SolarSystemTest::~SolarSystemTest()
{
	glDisable(GL_BLEND); ASSESS_LINE;
	glDisable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);

	glDisable(GL_STENCIL_TEST);

	ib->Unbind();
	vb->Unbind();
	voaState.UnBind();
}
