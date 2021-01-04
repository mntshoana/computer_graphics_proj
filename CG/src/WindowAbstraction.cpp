#include "WindowAbstraction.h"

static bool GLFWIsInitialized = false;


MicrosoftWindow::MicrosoftWindow(const WindowProperties& settings)
{
	Initialize(settings);
}

MicrosoftWindow::~MicrosoftWindow()
{
	Shutdown();
}

void MicrosoftWindow::OnUpdate()
{
	// Poll for and process events
	glfwPollEvents();

	// Swap front and back buffers 
	glfwSwapBuffers(window);
}

void MicrosoftWindow::SetVSync(bool enabled)
{
	if (enabled)
		glfwSwapInterval(1);
	else
		glfwSwapInterval(0);

	properties.vSync = enabled;
}

bool MicrosoftWindow::isVSync() const
{
	return properties.vSync;
}

inline bool MicrosoftWindow::NotClosed()
{
	if (!glfwWindowShouldClose(window))
		return true;
	else return false;
}

void MicrosoftWindow::Initialize(const WindowProperties& settings)
{
	properties.width = settings.width;
	properties.height = settings.height;
	properties.title = settings.title;

	std::cerr << "Creating Window: " << properties.title << ": width " << properties.width << " x height " << properties.height << std::endl;

	if (!GLFWIsInitialized)
	{
		// Initialize the library
		int success = glfwInit();
		ASSERT(success);

		// done
		glfwSetErrorCallback([] (int error, const char* description)
			{
				std::cerr << "GLFW Error: " << description << std::endl;
			});
		GLFWIsInitialized = true;

	}
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Create a windowed mode window and its OpenGL context 
	window = glfwCreateWindow(properties.width, properties.height, properties.title.c_str(), NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		ASSERT(-1);
	}

	// Make the window's context current 
	glfwMakeContextCurrent(window);

	//glfwGetWindowUserPointer and glfwSetWindowUserPointer can be useful here
	glfwSetWindowUserPointer(window, &properties); // pass the current window through glfw
	glfwSwapInterval(1);

	// Initialize the GLEW library
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		// Handle error
		glfwTerminate();
		ASSERT(-1);
	}

	SetVSync(true);


	initializeImGui(&window); //ImGui READY

	///////////////////////////////////////////
	// SET UP CALLBACK FUNTIONS
	//

	//Set up GLFW Resize Callback
	glfwSetWindowSizeCallback(window, [](GLFWwindow* w, int width, int height)
		{
			//glfwGetWindowUserPointer and glfwSetWindowUserPointer can be useful here
			WindowProperties& currentWindow = *(WindowProperties*)glfwGetWindowUserPointer(w);

			currentWindow.width = width;
			currentWindow.height = height;

			WindowResizedEvent e(width, height);
	
			currentWindow.EventCallback(e);
		});
	
	//Set up GLFW Close Callback
	glfwSetWindowCloseCallback(window, [](GLFWwindow* w)
		{
			// glfwGetWindowUserPointer and glfwSetWindowUserPointer can be useful here
			WindowProperties& currentWindow = *(WindowProperties*)glfwGetWindowUserPointer(w);

			WindowCloseEvent e();
			//currentWindow.EventCallback(e);
		});

	//Set up GLFW Key Callback
	glfwSetKeyCallback(window, [](GLFWwindow* w, int key, int scancode, int action, int mods)
		{
			//glfwGetWindowUserPointer and glfwSetWindowUserPointer can be useful here
			WindowProperties& currentWindow = *(WindowProperties*)glfwGetWindowUserPointer(w);

			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent e(key, 0);
					currentWindow.EventCallback(e);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleaseEvent e(key);
					currentWindow.EventCallback(e);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent e(key, 1); // To complicated to extract repeat count right now
					currentWindow.EventCallback(e);
					break;
				}
			}
		});

	//Set up GLFW Mouse Button Callback
	glfwSetMouseButtonCallback(window, [](GLFWwindow* w, int button, int action, int mods)
		{
			//glfwGetWindowUserPointer and glfwSetWindowUserPointer can be useful here
			WindowProperties& currentWindow = *(WindowProperties*)glfwGetWindowUserPointer(w);

			switch (action)
			{
			case GLFW_PRESS:
			{
				MouseButtonPressEvent e(button);
				currentWindow.EventCallback(e);
				break;
			}
			case GLFW_RELEASE:
			{
				MouseButtonReleaseEvent e(button);
				currentWindow.EventCallback(e);
				break;
			}
			}
		});

	//Set up GLFW Mouse Scroll Callback
	glfwSetScrollCallback(window, [](GLFWwindow* w, double xOffset, double yOffset)
		{
			//glfwGetWindowUserPointer and glfwSetWindowUserPointer can be useful here
			WindowProperties& currentWindow = *(WindowProperties*)glfwGetWindowUserPointer(w);

			MouseScrollEvent e(static_cast<float>(xOffset), static_cast<float>(yOffset));
			currentWindow.EventCallback(e);
		});

	//Set up GLFW Cursor Position Callback
	glfwSetCursorPosCallback(window, [](GLFWwindow* w, double xPos, double yPos)
		{
			//glfwGetWindowUserPointer and glfwSetWindowUserPointer can be useful here
			WindowProperties& currentWindow = *(WindowProperties*)glfwGetWindowUserPointer(w);

			MouseMoveEvent e(xPos, yPos);
			currentWindow.EventCallback(e);	

		});
}


void MicrosoftWindow::Shutdown()
{
	terminateImGui();

	glfwTerminate();
}

