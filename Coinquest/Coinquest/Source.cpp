#include <stdio.h>
#include<string.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

//Window Dimensions 
const GLint  WIDTH = 800, HEIGHT= 600;
GLuint VAO, VBO, shader;

//Vertex Shader

static const char* vShader = "                                        \n\
#version 330                                                          \n\
                                                                      \n\
layout(location = 0) in vec3 pos;                                     \n\
                                                                      \n\
void main()                                                           \n\
{                                                                     \n\
	gl_postion = vec4(0.4 * pos.x, 0.4 * pos.y, pos.z, 1.0);          \n\
}";

//FragmentShader

static const char* fShader = "                                       \n\
#version 330                                                         \n\
                                                                     \n\
out vec4 colour;                                                     \n\
                                                                     \n\
void main()                                                          \n\
{                                                                    \n\
	colour = vec4(1.0, 0.0, 0.0, 1.0);                               \n\
}";


void addShader(GLuint theProgram, const char* shaderCode, GLenum shaderType) {
	GLuint theShader = glCreateShader(shaderType);
	const GLchar* theCode[1];
	theCode[0] = shaderCode;
	
	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);

	glShaderSource(theShader, 1, theCode,codeLength);
	glCompileShader(theShader);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result) {

		glGetProgramInfoLog(theShader, sizeof(eLog), NULL, eLog);
		printf("error compiling the %d shader, %s\n",shaderType, eLog);
		return;
	}
	glAttachShader(theProgram, theShader);

	return;
}

void compileShaders() {
	shader = glCreateProgram();
	if (!shader) {
		printf("Error Creating shader program!\n");
		return;
	}

	addShader(shader, vShader, GL_VERTEX_SHADER);
	addShader(shader, fShader, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glLinkProgram(shader);
	glGetProgramiv(shader, GL_LINK_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(shader, sizeof(eLog),NULL, eLog);
		printf("error linking program,'%s'\n", eLog);
		return;
	}

	glValidateProgram(shader);
	glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("error validating program,'%s'\n", eLog);
		return;
	}
}

void makeSquare() {
	GLfloat vertices[]{
		0.0f,1.0f,0.0f,
		//1.0f,1.0f,0.0f,
		-1.0f,-1.0f,0.0f,
		1.0f,-1.0f,0.0f
	};
	glGenVertexArrays(1,&VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

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
	makeSquare();
	compileShaders();

	//loop until window closes
	while (!glfwWindowShouldClose(mainwindow)) {
		//Get and handle user inputs
		glfwPollEvents();


		//clear the window
		glClearColor(0.0f, 0.5f, 1.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shader);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
		glUseProgram(0);
		glfwSwapBuffers(mainwindow);
	}

	return 0;
}