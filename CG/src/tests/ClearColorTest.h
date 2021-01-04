#ifndef TEST_CLEAR_COLOR_TEST
#define TEST_CLEAR_COLOR_TEST

#include "Test.h"

class ClearColorTest : public Test
{
public:
	ClearColorTest();
	~ClearColorTest();


	void OnUpdate(float deltaTime) override;
	void OnRender() override;
	void OnImGuiRender() override;
private:
	glm::vec4 color;
	Renderer renderer;
};
#endif