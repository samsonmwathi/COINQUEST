#include "GameWindow.h"
#include <GL/GLU.h>

typedef struct {

	GLfloat positionCoordinates[3];
	GLfloat textureCoordinates[2];
}VertexData;

#define Square_Size 100
VertexData vertices[]{
	{{0.0f, 0.0f, 0.0f},				{0.0f,0.0f}},
	{{Square_Size, 0.0f, 0.0f},			{1.0f,0.0f}},
	{{Square_Size, Square_Size, 0.0f},	{1.0f,1.0f}},
	{{0.0f, Square_Size, 0.0f},			{0.0f,1.0f}}
};

void GameWindow::setRunning (bool newRunning)
{
	_running = newRunning;
}

bool GameWindow::getRunning()
{
	bool run = _running;
	return run;
}

GLuint GameWindow::loadAndBufferImage(const char * filename)
{
	int width, height, bpp;
	GLFWimage imageData;

	unsigned char* m_localbuffer=stbi_load(filename, &width, &height, &bpp,4);

	GLuint textureBufferID;
	glGenTextures(1, &textureBufferID);
	glBindTexture(GL_TEXTURE_2D, textureBufferID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width,height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_localbuffer);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	stbi_image_free(&imageData);
	
	return 0;

}

GameWindow::GameWindow(bool running):_running(running),_height(800),_width(800*16/9),_vertexBufferID(0)
{
	//set backgroung colour
	glClearColor(0.5294f, 0.8078f, 0.9216f, 1.0f);
	glViewport(0.0f, 0.0f, _width, _height);

	//glEnable(GL_TEXTURE_2D);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	////transform our coordinate system to start from 0,0 on bottom left corner to end at screen (width, height)
	glMatrixMode(GL_PROJECTION);
	glOrthof(0.0f, (float)_width,0.0f, (float)_height, 0.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);

	//Generate and bind buffers
	glGenBuffers(1, &_vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer (3, GL_FLOAT, sizeof(VertexData),(GLvoid *) offsetof(VertexData,positionCoordinates));

	/*glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, sizeof(VertexData), (GLvoid*)offsetof(VertexData, textureCoordinates));*/

	/*_textureBufferID = loadAndBufferImage("ground image");*/
}

void GameWindow::render(GLFWwindow* window)
{
	glClearColor(0.5294f, 0.8078f, 0.9216f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0f, 0.0f, 0.5f);
	glDrawArrays(GL_QUADS, 0, 4);
	
	glfwSwapBuffers(window);
}
void GameWindow::update()
{
	
}
