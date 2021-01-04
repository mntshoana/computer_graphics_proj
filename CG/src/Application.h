#ifndef MY_APPLICATION_CONSTANT
#define MY_APPLICATION_CONSTANT

#include "OpenglDebugger.h"
#include "WindowAbstraction.h"

#include "tests/Selector.h"
#include "tests/ClearColorTest.h"
#include "tests/TextureTest.h"
#include "tests/Texture3DTest.h"
#include "tests/SolarSystemTest.h"

class Application
{
public:
	Application();
	void OnEvent(Event& e);
	void Run();
private:
	std::unique_ptr<WindowAbstraction> window;
	Test* currentApplication;
	Selector* mainMenu;
};

#endif