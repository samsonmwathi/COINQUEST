#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

//Window Dimensions 
const GLint  WIDTH = 800, HEIGHT= 600;


int main() {
	//initialize GLFW
	if (!glfwInit())
	{
		printf("GLFW initialization failed!");
		glfwTerminate();
		return 1;
	}
	//set GLFW window properties
	//opgl version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//COREPROFILE == NO BACKWARDS COMPATIBILITY
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//Allow forward compatibility
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* mainwindow = glfwCreateWindow(WIDTH, HEIGHT, "COINQUEST", NULL, NULL);
	if(!mainwindow) {
		printf("Main Window creation Failed");
		glfwTerminate();
		return 1;
	}

	//Get buffer size information(view port size)
	int bufferWidth, bufferHeight;
	glfwGetFramebufferSize(mainwindow, &bufferWidth, &bufferHeight);

	//set context for GLEW to use
	glfwMakeContextCurrent(mainwindow);

	//Allow Modern Extension Values
	glewExperimental = GL_TRUE;

	if (glewInit()!=GLEW_OK) {
		printf("GLEW initializatin failed!");
		glfwDestroyWindow(mainwindow);
		glfwTerminate();
		return 1;
	}
	//setup viewport size
	glViewport(0, 0, bufferWidth, bufferHeight);
	//loop until window closes
	while (!glfwWindowShouldClose(mainwindow)) {
		//Get and handle user inputs
		glfwPollEvents();

		//clear the window
		glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(mainwindow);
	}

	return 0;
}