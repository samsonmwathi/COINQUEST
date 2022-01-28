#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <GL/GLU.h>
#include "stb_image.h"


class GameWindow
{
private:

	bool _running;
	GLfloat _height;
	GLfloat _width;
	GLuint _vertexBufferID;
	GLuint _textureBufferID;

	GLuint loadAndBufferImage(const char* filename);

public:

	void setRunning(bool newRunning);
	bool getRunning();

	GameWindow(bool running);

	void render(GLFWwindow* window);
	void update();
};

