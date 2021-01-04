#ifndef TEST_CONSTANT
#define TEST_CONSTANT

#include "Renderer.h"
#include "Events.h"
#include <string>
#define path std::string("/Users/macgod/Dev/Computer Graphics/CG/data")
class Test
{
public:
	Test() {}
	virtual ~Test() { }

	virtual void OnUpdate(float deltaTime) {}
	virtual void OnRender() {}
	virtual void OnImGuiRender() {};
	using EventCallbackFn = std::function<void(KeyPressedEvent&)>;
	virtual void OnKey(KeyPressedEvent& e) {}
	virtual void OnScroll(MouseScrollEvent& e) {}
	
	const float depth = 2000.0f;
};

#endif
