#include "Selector.h"


	// Only need to implement one function from Test
Selector::Selector(Test*& test) 
	: currentTest(test)
{
}
void Selector::OnImGuiRender()
{
	// Make buttons to display all tests
	for (auto& test : list)
	{
		// if the following buttons are clicked
		if (ImGui::Button(test.name.c_str()))
			currentTest = test.constructor(); // Construct Relavent Test
		else
		{
			// Clear Background Color
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f); ASSESS_LINE;
			renderer.Clear();
		}
	}
}

