#include "OpenglDebugger.h"
#include <iostream>

bool noBugReport()
{
	switch (glGetError())
	{
	case(GL_NO_ERROR):
		return true;
	case(GL_INVALID_ENUM):
		std::cerr << "Error! Unacceptable value specified where enumeration expected "; break;
	case(GL_INVALID_VALUE):
		std::cerr << "Error! Numeric argument out of range "; break;
	case (GL_INVALID_OPERATION):
		std::cerr << "Error! Invalid operation in current state "; break;
	case(GL_INVALID_FRAMEBUFFER_OPERATION):
		std::cerr << "Error! Framebuffer object incomplete "; break;
	case(GL_OUT_OF_MEMORY):
		std::cerr << "Error! Not enough memory left "; break;
	default:
		std::cerr << "Unkown Error ";
	}
	std::cout << "in " << __FILE__ << " -> line " << __LINE__ << std::endl;
	return false;
}


int initializeImGui(GLFWwindow** window)
{
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(*window, true);
	ImGui_ImplOpenGL3_Init("#version 330 core");
	ImGui::StyleColorsDark(); // ImGui style
	return 0;
}

void terminateImGui()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}



void ClearAllErrors()
{
	while (glGetError());
	return;
}

unsigned  int importDisplayHeight() {
    CGDirectDisplayID *_dpy = new CGDirectDisplayID;
    *_dpy = CGMainDisplayID();
    int _windowHeight = CGDisplayPixelsHigh(*_dpy);
    delete _dpy;
    return _windowHeight;
}

unsigned int importDisplayWidth() {
    CGDirectDisplayID *_dpy = new CGDirectDisplayID;
    *_dpy = CGMainDisplayID();
    int _windowWidth = CGDisplayPixelsWide(*_dpy);
    delete _dpy;
    return _windowWidth;
}
