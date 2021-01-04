#ifndef MY_OPEN_GL_DEBUGER
#define MY_OPEN_GL_DEBUGER

#include "pch.h"



// OPEN GL ERRORS ARE NOT EASY TO DEBUG
// HANDLE THEM WITH ASSERTIONS
#ifdef _DEBUG
#ifdef _MSC_VER
    #define ASSERT(x) if(!(x)) __debugbreak()
    #define ASSERT(x)
    
#define ASSESS_LINE ASSERT(noBugReport())
#define CLEAR_ALL_ERRORS ClearAllErrors()
#else 
#define ASSESS_LINE
#define ASSERT(x)
#define CLEAR_ALL_ERRORS 
#endif // ASSERTIONS
#endif



#ifdef _WIN32
const unsigned int    displayWidth = GetSystemMetrics(SM_CXSCREEN);
const unsigned int    displayHeight = GetSystemMetrics(SM_CYSCREEN);
#elif defined __APPLE__
#import <CoreGraphics/CGDirectDisplay.h>
unsigned int importDisplayWidth();
unsigned int importDisplayHeight();
const unsigned int    displayWidth =  importDisplayWidth();
const unsigned int    displayHeight = importDisplayHeight();
#else
#error Not Yet Supportedd
#endif
const float aspectRatio = displayWidth / displayHeight;

bool noBugReport();
int initializeImGui(GLFWwindow** window);
void terminateImGui();

void ClearAllErrors();
#endif
