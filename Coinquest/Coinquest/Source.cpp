#include <stdio.h>
#include<string.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <cstring>
#include "SFML-2.5.1/include/SFML/Graphics.hpp"
#include "SFML-2.5.1/include/SFML/Config.hpp"
#include "SFML-2.5.1/include/SFML/GpuPreference.hpp"
#include "SFML-2.5.1/include/SFML/OpenGL.hpp"
#include "SFML-2.5.1/include/SFML/Window.hpp"
#include "SFML-2.5.1/include/SFML/System.hpp"
#include "SFML-2.5.1/include/SFML/Main.hpp"

/*
//compiles the shaders
static unsigned int CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*) alloca (length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to Compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "shader!" <<std::endl;
            std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }
    return id;
}
//creates a shader
static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}
//function fo drawing a green square at the bottom of the screen
void drawGround(float left, float right, float top, float bottom)
{
       
    float positions[8] = {
        left,  bottom,
        right, bottom,
        right, top,
        left,  top
    };

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    std::string vertexShader =
        "#version 330 core\n"
        "\n"
        "layout(location=0) in vec4 Position;\n"
        "\n"
        "void main()\n"
        "{\n"
        "   glposition = position;\n"
        "}\n";
    
    std::string fragmentShader =
        "#version 330 core\n"
        "\n"
        "layout(location=0) out vec4 colour;\n"
        "\n"
        "void main()\n"
        "{\n"
        "   colour = vec4(0.3, 0.54, 0.5, 1.0);\n"
        "}\n";

    unsigned int shader = CreateShader(vertexShader, fragmentShader);
    glUseProgram(shader);
}

//function for character movement with arrow keys

//The coin;


int main (void)
{
    GLFWwindow* window;

    //initialize Library
    if (!glfwInit())
        return -1;

    //Create a winodwed mode window and its OpenGl context

    window = glfwCreateWindow(640, 480, "Coinquest", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return - 1;
    }

    //Make the Window's context current
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
        std::cout << "Error!" << std::endl;
    //get openGl version
    //std::cout << glGetString(GL_VERSION) << std::endl;
    
  
    //calculations for drawing to the screen
    int screenwidth = 640;
    int screenheight = 480;

    //the size of a ground box used to calculate the coordiantes of the square
    int boxwidth = 50;
    int boxheight = 50;
    int boxleft = -1.07813 * screenwidth;
    int boxbottom = -1 * screenheight;

    // calculate screen space coordinates
    //we use coords to create the square
    float left = (float)boxleft / screenwidth;
    float right = left + (float)boxwidth / screenwidth;
    float bottom = (float)boxbottom / screenheight;
    float top = bottom + (float)boxheight / screenheight;
    
    //loop the squares to make the ground
    while (left < screenwidth) {
       
        drawGround(left, right, top, bottom);
        left++;
        
    }


    //Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
        //Render here
        glClearColor(0.5294f, 0.8078f, 0.9216f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_POLYGON, 0, 4);
        
        //swap front and back buffers
        glfwSwapBuffers(window);

        //Poll for and process events
        glfwPollEvents();
    }

    

   // glDeleteProgram(shader);
}
*/
//Specify window dimensions
sf::Vector2f viewSize(1024, 768);
sf::VideoMode vm(viewSize.x, viewSize.y);

//create window
sf::RenderWindow window(vm, "Coinquest", sf::Style::Default);


//Adding sprites(images with transparent background)
sf::Texture coinTexture;
sf::Sprite coinSprite;

sf::Texture cactusTexture;
sf::Sprite cactusSprite;

sf::Texture groundTexture;
sf::Sprite groundSprite;



void draw() {
    window.draw(groundSprite);
    window.draw(coinSprite);
    window.draw(cactusSprite);
}
void init() {
    //Load the textures
    coinTexture.loadFromFile("Game_Assets/coin.png");
    cactusTexture.loadFromFile("Game_Assets/cactus.png");
    groundTexture.loadFromFile("Game_Assets/ground.png");
    //Set and attach textures to sprites
    coinSprite.setTexture(coinTexture);
    cactusSprite.setTexture(cactusTexture);
    groundSprite.setTexture(groundTexture);

    //set positions of sprites
    groundSprite.setPosition(sf::Vector2f(viewSize.x / 3,viewSize.y / 3));
    groundSprite.setOrigin(groundTexture.getSize().x / 2, groundTexture.getSize().y / 2);
}
int main() {
    while (window.isOpen()) {
        // Handle Keyboard Events
        // Update Game Objects in the scene
        window.clear(sf::Color::Black);
        draw();
        // Render Game Objects
        window.display();
    }
    return 0;
}