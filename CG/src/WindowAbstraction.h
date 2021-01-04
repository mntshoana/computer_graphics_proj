#ifndef MY_WINDOW_CONSTANT
#define MY_WINDOW_CONSTANT

#include "pch.h"

#include "OpenglDebugger.h"
#include "Events.h"

using EventCallbackFn = std::function<void(Event&)>;

class WindowProperties
{
public:
	std::string title;
	unsigned int width;
	unsigned int height;
	bool vSync;


	EventCallbackFn EventCallback;

	WindowProperties(const std::string& title = "CG Simulation",
		unsigned int width = displayWidth * 0.70f,	unsigned int height = displayHeight * 0.70f,
		bool vSync = false,  		EventCallbackFn fn = nullptr)
		: title(title), width(width), height(height), vSync(vSync), EventCallback(fn)
	{
	}	
};

class WindowAbstraction
{
public:
	WindowAbstraction() = default; // use compiler generated
	virtual ~WindowAbstraction() {}

	virtual void OnUpdate() = 0;
	
	virtual unsigned int GetWidth() const = 0;
	virtual unsigned int GetHeight() const = 0;

	virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
	virtual void SetVSync(bool enabled) = 0;
	virtual bool isVSync() const = 0;
	
	virtual bool NotClosed () = 0;
};

class MicrosoftWindow : public WindowAbstraction
{
private:
	GLFWwindow* window;
	WindowProperties properties;
public:
	MicrosoftWindow(const WindowProperties& settings);
	virtual ~MicrosoftWindow();

	void OnUpdate() override;

	inline unsigned int GetWidth() const override { return properties.width; }
	inline unsigned int GetHeight() const override { return properties.height; }
	inline GLFWwindow const* const GetWindowHandle() { return window; }

	inline void SetEventCallback(const EventCallbackFn& callback) override
	{ properties.EventCallback = callback; }
	void SetVSync(bool enabled) override;
	bool isVSync() const override;

	inline bool NotClosed () override;
private:
	virtual void Initialize(const WindowProperties& settings);
	virtual void Shutdown();
};

#endif
