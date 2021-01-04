#ifndef MY_EVENTS_SYSTEM
#define MY_EVENTS_SYSTEM

#include "pch.h"


#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() {return EventType::type; } \
							   virtual EventType GetEventType() const override {return GetStaticType(); } \
							   virtual const char* GetName() const override {return #type;} // As const character string

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategory() const override {return category; }



enum class EventType
{
	None = 0, WindowClose, WindowResize, windowFocus,
	WindowLostFocus, WindowMoved,
	AppTick, AppUpdate, AppRender,
	KeyPress, KeyRelease,
	MousePress, MouseRelease, MouseMove, MouseScroll
};

enum EventCategory
{
	None = 0,
	ApplicationEventCategory = 1,
	InputEventCategory = 1 << 1,
	KeyboardEventCategory = 1 << 2,
	MouseEventCategory = 1 << 3
};


class Event
{
	friend class EventDipatcher;
public:
	virtual EventType GetEventType() const = 0;
	virtual const char* GetName() const = 0;
	virtual int GetCategory() const = 0;
	virtual std::string ToString() const { return GetName(); }

	bool IsInCategory(EventCategory category) { return GetCategory() & category; }

	bool isHandled = false;
};

class EventDispatcher
{
private:
	Event& e;
public:
	EventDispatcher(Event& e) : e(e) 
	{
	}

	template <typename T>
	using EventFn = std::function<bool>(T&);

	template <typename T>
	bool Dispatch(EventFn<T> func)
	{
		if (e.GetEventType() == T::e())
		{
			e.isHandled = func(*(T*)&e); // Call the relavent type Event function
			return true;
		}
		return false;
	}


};
inline std::ostream& operator << (std::ostream& os, const Event& e)
{
	return os << e.ToString() << std::endl;
}

//----------------------------------------------------------------------------------

class WindowResizedEvent : public Event
{
private:
	unsigned int width, height;
public:
	WindowResizedEvent(unsigned int width, unsigned int height) : width(width), height(height) {}
	unsigned int GetWidth() const { return width; }
	unsigned int GetHeight() const { return height; }

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "WindowsResizeEvent: " << width << ", " << height << std::endl;
		return ss.str();
	}

	EVENT_CLASS_TYPE(WindowResize);
	EVENT_CLASS_CATEGORY(ApplicationEventCategory);
};

class WindowCloseEvent : public Event
{
public:
	WindowCloseEvent() {} // use compiler-generated version

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "WindowCloseEvent!!" << std::endl;
		return ss.str();
	}
	EVENT_CLASS_TYPE(WindowClose);
	EVENT_CLASS_CATEGORY(ApplicationEventCategory);
};

class AppTickEvent : public Event
{
public:
	AppTickEvent() {}

	EVENT_CLASS_TYPE(AppTick);
	EVENT_CLASS_CATEGORY(ApplicationEventCategory);
};

class AppUpdateEvent : public Event
{
public:
	AppUpdateEvent() {}

	EVENT_CLASS_TYPE(AppUpdate);
	EVENT_CLASS_CATEGORY(ApplicationEventCategory);
};

class AppRendereEvent : public Event
{
public:
	AppRendereEvent() {}

	EVENT_CLASS_TYPE(AppRender);
	EVENT_CLASS_CATEGORY(ApplicationEventCategory);
};
//-------------------------------------------------------------------------------
class KeyEvent : public Event
{
protected:
	int keycode;
	KeyEvent(int keycode) : keycode(keycode) {}
	
public:
	int GetKeycode() { return keycode; }

	EVENT_CLASS_CATEGORY(KeyboardEventCategory | InputEventCategory)
};

class KeyPressedEvent : public KeyEvent
{
private:
	int repeatCount;
public:
	KeyPressedEvent(int keycode, int repeatCount): KeyEvent(keycode), repeatCount(repeatCount) {}
	int GetRepeatCount() { return repeatCount; }

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "KeyPressedEvent: " << keycode << "( " << repeatCount << " repeats)" << std::endl;
		return ss.str();
	}

	EVENT_CLASS_TYPE(KeyPress);
};

class KeyReleaseEvent : public KeyEvent
{
public:
	KeyReleaseEvent(int keycode) : KeyEvent(keycode) {}

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "KeyReleaseEvent: " << keycode << std::endl;
		return ss.str();
	}

	EVENT_CLASS_TYPE(KeyRelease);
};

//------------------------------------------------------------------------------------------------------
class MouseMoveEvent : public Event
{
private:
	float x, y;
public:
	MouseMoveEvent(float x, float y) : x(x), y(x) {}

	float GetX() { return x; }
	float GetY() { return y; }

	std::string ToString()
	{
		std::stringstream ss;
		ss << "MouseMoveEvent: " << x << ", " << y << std::endl;
		return ss.str();
	}

	EVENT_CLASS_TYPE(MouseMove);
	EVENT_CLASS_CATEGORY(MouseEventCategory | InputEventCategory);

};

class MouseScrollEvent : public Event
{
private:
	float xOffset, yOffset;
public:
	float GetXOffset() const { return xOffset; }
	float GetYOffset() const { return yOffset; }
	MouseScrollEvent(float xOffset, float yOffset) : xOffset(xOffset), yOffset(yOffset) {}

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "MouseScrollEvent: " << xOffset << ", " << yOffset << std::endl;
		return ss.str();
	}

	EVENT_CLASS_TYPE(MouseScroll);
	EVENT_CLASS_CATEGORY(MouseEventCategory | InputEventCategory);
};

class MouseButtonEvent : public Event
{
protected:
	int button;
	MouseButtonEvent(int button) : button(button) {}
private:
	int GetMouseButton() const { return button; }
};

class MouseButtonPressEvent : public MouseButtonEvent
{
public:
	MouseButtonPressEvent(int button) : MouseButtonEvent(button) {}

	std::string ToString() const override
	{ 
		std::stringstream ss;
		ss << "MouseButtonPress: " << button << std::endl;
		return ss.str();
	}

	EVENT_CLASS_TYPE(MousePress);
	EVENT_CLASS_CATEGORY(MouseEventCategory | InputEventCategory);
};

class MouseButtonReleaseEvent : public MouseButtonEvent
{
public:
	MouseButtonReleaseEvent(int button) : MouseButtonEvent(button) {}
	
	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "MouseButtonPress: " << button << std::endl;
		return ss.str();
	}

	EVENT_CLASS_TYPE(MouseRelease);
	EVENT_CLASS_CATEGORY(MouseEventCategory | InputEventCategory);
};

#endif
