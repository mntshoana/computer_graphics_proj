#include "ClearColorTest.h"


ClearColorTest::ClearColorTest() : color{ 0.2f, 0.3f, 0.8f, 1.0f }
{
}
ClearColorTest::~ClearColorTest()
{
}
void ClearColorTest::OnUpdate(float deltaTime)
{
	glClearColor(color.r, color.g, color.b, color.a); ASSESS_LINE;
	renderer.Clear();
}
void ClearColorTest::OnRender()
{

}
void ClearColorTest::OnImGuiRender()
{
	ImGui::ColorEdit4("Clear Color", &color.x);
}