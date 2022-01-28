#include <stdio.h>
#include<string.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <cstring>
#include <SFML/Graphics.hpp>
#include "Menu.h"


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

//Background
    
//function for character movement with arrow keys

//The coin;


int main (void)
{
    sf::Texture texture;
    if (!texture.loadFromFile("Coinquest.png")) {
        cout << "Unable to Load";
    }
    sf::Sprite sprite(texture);
    RenderWindow Play;
    RenderWindow OPTIONS;
    RenderWindow EXIT;
    //Make Start Menu window and close it before game starts
    RenderWindow MENU(VideoMode(960, 720), "Start Menu", Style::Default);
    
    StartMenu StartMenu(960, 720);

    while (MENU.isOpen()) {
        MENU.draw(sprite);
        Event event;
        while (MENU.pollEvent(event)) {
            if (event.type == Event::Closed) {
                MENU.close();

            }
            if (event.type == Event::KeyReleased) {
                if (event.key.code == Keyboard::Up) {
                    StartMenu.MoveUp();
                    break;
                }
                if (event.key.code == Keyboard::Down) {
                    StartMenu.MoveDown();
                    break;
                }
                if (event.key.code == Keyboard::Return) {
                    RenderWindow Play(VideoMode(960, 720), "CoinQuest");
                    RenderWindow OPTIONS(VideoMode(960, 720), "Options");
                    RenderWindow EXIT(VideoMode(960, 720), "EXIT");
                }
                int x = StartMenu.MenuPressed();
                if (x == 0) {
                    while (Play.isOpen()) {
                        Event aevent;
                        while (Play.pollEvent(aevent)) {
                            if (aevent.type == Event::Closed) {
                                Play.close();
                            }
                            if (aevent.type == Event::KeyPressed) {

                                if (aevent.key.code == Keyboard::Escape) {
                                    Play.close();
                                }
                            }
                        }
                        OPTIONS.close();
                        Play.clear();
                        Play.display();
                    }
                }
                if (x == 1) {
                    while (OPTIONS.isOpen()) {
                        Event aevent;
                        while (OPTIONS.pollEvent(aevent)) {
                            if (aevent.type == Event::Closed) {
                                OPTIONS.close();
                            }
                            if (aevent.type == Event::KeyPressed) {

                                if (aevent.key.code == Keyboard::Escape) {
                                    OPTIONS.close();
                                }
                            }
                        }
                        Play.close();
                        OPTIONS.clear();
                        OPTIONS.display();
                    }
                }

                if (x == 2) {
                    MENU.close();
                    break;
                }
            }
        }
    }
    MENU.clear();
    StartMenu.draw(MENU);
    MENU.display();
   
}