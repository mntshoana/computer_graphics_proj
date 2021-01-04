#ifndef SOLAR_SYSTEM_TEST
#define SOLAR_SYSTEM_TEST

#include "Test.h"
#define numberOfPlanets 12

class SolarSystemTest : public Test
{
public:
	SolarSystemTest();
	~SolarSystemTest();

	void OnUpdate(float deltaTime) override;
	void OnRender() override;
	void OnImGuiRender() override;
	virtual void OnKey(KeyPressedEvent& e) override;
	virtual void OnScroll(MouseScrollEvent& e) override;

private:
	VertexArrayObject voaState;
	Renderer renderer;

	void SetPlanetValues();
public:
	Attribute attr;
	Shader shader;
private:
	std::unique_ptr<Shape> shape;
	std::unique_ptr<VertexBuffer> vb;
	std::unique_ptr<IndexBuffer> ib;

	Texture sun, mercury, venus, earth, moon, mars, jupiter, saturn, saturnRing, uranus, neptune, pluto;

	glm::mat4 scale, rotation, revolve, revolveAroundEarth;
	glm::mat4 model, view, projection, transformation;

	// Camera
	glm::vec3 scalor,rotar;
	glm::vec3 cameraPosition, cameraDirection, cameraOrientation;
	float angle;
	float speed;
};
#endif