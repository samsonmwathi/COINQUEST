#pragma once
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include <iostream>


#define ASSERT(x) if (!(x)) __debugbreak();
#define  GLCall(x) GLClearError();\
x;\
ASSERT(GLLogCall (#x,__FILE__,__FILE__))

void GLCLearError();
bool GLLogCall(const char* function, const char* fiel, int line);