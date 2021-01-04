#include "Application.h"


Application::Application()
{
	currentApplication = mainMenu  = nullptr;

	window = std::unique_ptr<WindowAbstraction>( new MicrosoftWindow(WindowProperties()));
	window->SetEventCallback(BIND_EVENT(Application::OnEvent));
}
void Application::OnEvent(Event& e)
{
	std::cout << e.ToString() << std::endl;
	if (e.IsInCategory(KeyboardEventCategory))
		currentApplication->OnKey(static_cast<KeyPressedEvent&>(e));
	if (e.IsInCategory(MouseEventCategory))
		if (dynamic_cast<MouseScrollEvent*>(&e))
			currentApplication->OnScroll(static_cast<MouseScrollEvent&>(e));
}

void Application::Run()
{
	//OPENGL READY
	
	mainMenu = new Selector(currentApplication);
	
	currentApplication = mainMenu;
	mainMenu->AddTest<ClearColorTest>("Clear Color Test");
	mainMenu->AddTest<TextureTest>("Texture Test");
	mainMenu->AddTest<Texture3DTest>("Texture3DTest");
	mainMenu->AddTest<SolarSystemTest>("Solar System Test");
	/* Loop until the user closes the window */
	
	while (window->NotClosed()) 
	{
		// Render ready

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		if (currentApplication != nullptr) // Run a test - prevent null pointe error
		{
			currentApplication->OnUpdate(0);
			currentApplication->OnRender();

			ImGui::Begin("currentApplication mainMenu");
			if (currentApplication != mainMenu) 
			{
				// Draw a back button
				if (ImGui::Button("<BACK"))
				{
					// IF BACK IS CLICKED
					// Change delete current test and await new test

					delete currentApplication;
					currentApplication = mainMenu;
				}
			}
			
			currentApplication->OnImGuiRender();
			ImGui::End();			

			// Render everything in the pipeline
			ImGui::Render(); // ImGui creates a lot of opengl errors
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData()); CLEAR_ALL_ERRORS;
		}
		window->OnUpdate();
	}
	// Clean up
	if (currentApplication != mainMenu)
		delete mainMenu;
	delete currentApplication;
}
int main(void)
{	
	Application app;
	app.Run();
	return 0;
}
