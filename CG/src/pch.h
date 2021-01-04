#ifndef PRECOMPILED_HEADER_CONSTANT
#define PRECOMPILED_HEADER_CONSTANT

#include <iostream>
#include <fstream>
#include <memory>

#include <vector>
#include <unordered_map>

#include <string>
#include <sstream>
#include <functional>


#if defined WIN32 || defined _WIN32
#define GLEW_STATIC // GLEW Library - OPEN GL functions -> requires prepropessor definition GLEW_STATIC to indicate static linking on windows
#include <Windows.h>
#endif

#include <GL/glew.h>  // GLEW
#ifdef _WIN32
#iclude <GL/Gl.h>
#elif defined __APPLE__
#include <OpenGL/OpenGL.h>
#endif
#include <GLFW/glfw3.h> // GLFW - manage multiplatform OpenGL window contexts

// We will be using ImGui to manage the application as it runs
#include "IMGUI/imgui.h"
#include "IMGUI/imgui_impl_glfw.h"
#include "IMGUI/imgui_impl_opengl3.h"

//GLM
#include "glm/glm.hpp"
#include <glm/ext.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>

// custom macros
#define BIND_EVENT(x) std::bind(&x, this, std::placeholders::_1)
#endif

