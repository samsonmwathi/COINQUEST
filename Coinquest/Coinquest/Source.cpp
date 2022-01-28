#include <stdio.h>
#include <string.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <cstring>
#include <SFML\Graphics.hpp>
#include <fstream>
#include <string>
#include <sstream>
#include "Hero.h"
#include "Enemy.h"
#include "Rocket.h"
#include <vector>


//To read our shaders form the res folderand shader files we use:
//To return both our vertex and fragment shader codes
struct ShaderProgramSource {
    std::string VertexSource;
    std::string FragmentSource;
};
//To parse our shaders from the shader files 
static ShaderProgramSource ParseShader(const std::string& filepath)
{
    //open a file stream to the shader files
    std::ifstream stream(filepath);
    //set the different shader types to a specific value

    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };
    //init lines in the shader file as strings
    std::string line;
    //use a string stream to read the shader
    //It will hold our shader code
    std::stringstream ss[2];

    //initialize our shaderype 
    ShaderType type = ShaderType::NONE;
    //read the file while its open
    while (getline(stream, line))
    {
        //check the shader type from our shader doc
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
            {
                //set mode to vertex shader
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos)
            {
                //set mode to fragment shader
                type = ShaderType::FRAGMENT;
            }
        }
        else
        {
            //push our the data into our string stream 
            //using type as an index to our ss array
            ss[(int)type] << line << '\n';
        }
    }
    //return both the vertex and fragment shaders respectively
    return { ss[0].str(), ss[1].str() };
}

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
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to Compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "shader!" << std::endl;
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

    ShaderProgramSource source = ParseShader("res/shaders/Ground.shader");
    //uncomment to output shader data
    /*std::cout << "VERTEX" << std::endl;
    std::cout << source.VertexSource << std::endl;
    std::cout << "FRAGMENT" << std::endl;
    std::cout << source.FragmentSource << std::endl;*/

    unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
    glUseProgram(shader);

    glDeleteProgram(shader);

}

//function for character movement with arrow keys

//The coin;


//int main (void)
//{
//    GLFWwindow* window;
//
//    //initialize Library
//    if (!glfwInit())
//        return -1;
//
//    //Create a winodwed mode window and its OpenGl context
//
//    window = glfwCreateWindow(640, 480, "Coinquest", NULL, NULL);
//    if (!window)
//    {
//        glfwTerminate();
//        return -1;
//    }
//
//    //Make the Window's context current
//    glfwMakeContextCurrent(window);
//
//    if (glewInit() != GLEW_OK)
//        std::cout << "Error!" << std::endl;
//    //get openGl version
//    //std::cout << glGetString(GL_VERSION) << std::endl;
//
//
//    //calculations for drawing to the screen
//    int screenwidth = 640;
//    int screenheight = 480;
//
//    //the size of a ground box used to calculate the coordiantes of the square
//    int boxwidth = 50;
//    int boxheight = 50;
//    int boxleft = -2.07813 * screenwidth;
//    int boxbottom = -1 * screenheight;
//
//    // calculate screen space coordinates
//    //we use coords to create the square
//    float left = boxleft / screenwidth;
//    float right = left + (float)boxwidth / screenwidth;
//    float bottom = (float)boxbottom / screenheight;
//    float top = bottom + (float)boxheight / screenheight;
//
//    //loop the squares to make the ground
//    while (left < screenwidth) {
//
//        drawGround(left, right, top, bottom);
//        left++;
//    }
//
//
//    drawGround(left, right, top, bottom);
//
//
//    //Loop until the user closes the window
//    while (!glfwWindowShouldClose(window))
//    {
//
//        /*Render here*/
//        glClearColor(0.5294f, 0.8078f, 0.9216f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        glDrawArrays(GL_POLYGON, 0, 4);
//        
//        //swap front and back buffers
//        glfwSwapBuffers(window);
//
//        //Poll for and process events
//        glfwPollEvents();
//    }
//
//    
//
//   // glDeleteProgram(shader);
//}


sf::Vector2f viewSize(1024, 768);
sf::VideoMode vm(viewSize.x, viewSize.y);
sf::RenderWindow window(vm, "Hello SFML Game !!!", sf::Style::Default);

void spawnEnemy();
void shoot();
bool checkCollision(sf::Sprite sprite1, sf::Sprite sprite2);

sf::Vector2f playerPosition;
bool playerMoving = false;
sf::Texture skyTexture;
sf::Sprite skySprite;
sf::Texture bgTexture;
sf::Sprite bgSprite;

//Hero instantiation
sf::Texture skyTexture;
sf::Sprite skySprite;
sf::Texture bgTexture;
sf::Sprite bgSprite;
Hero hero;

//Enemy Variable
std::vector<Enemy*> enemies;
std::vector<Rocket*> rockets;
float currentTime;
float prevTime = 0.0f;

void init() {
    skyTexture.loadFromFile("Assets/graphics/sky.png");
    skySprite.setTexture(skyTexture);
    bgTexture.loadFromFile("Assets/graphics/bg.png");
    bgSprite.setTexture(bgTexture);

    // Load bg Texture
    bgTexture.loadFromFile("Assets/graphics/bg.png");
    // Create Sprite and Attach a Texture
    bgSprite.setTexture(bgTexture);
    hero.init("Assets/graphics/hero.png", sf::Vector2f(viewSize.x *
        0.25f, viewSize.y * 0.5f), 200);
    srand((int)time(0));
}
void spawnEnemy() {
    int randLoc = rand() % 3;
    sf::Vector2f enemyPos;
    float speed;
    switch (randLoc) {
    case 0: enemyPos = sf::Vector2f(viewSize.x, viewSize.y * 0.75f);
        speed = -400; break;
    case 1: enemyPos = sf::Vector2f(viewSize.x, viewSize.y * 0.60f);
        speed = -550; break;
    case 2: enemyPos = sf::Vector2f(viewSize.x, viewSize.y * 0.40f);
        speed = -650; break;
    default: printf("incorrect y value \n"); return;
    }
    Enemy* enemy = new Enemy();
    enemy->init("Assets/graphics/enemy.png", enemyPos, speed);
    enemies.push_back(enemy);
}

void shoot() {
    Rocket* rocket = new Rocket();
    rocket->init("Assets/graphics/rocket.png",
        hero.getSprite().getPosition(),
        400.0f);
    rockets.push_back(rocket);
}
bool checkCollision(sf::Sprite sprite1, sf::Sprite sprite2) {
    sf::FloatRect shape1 = sprite1.getGlobalBounds();
    sf::FloatRect shape2 = sprite2.getGlobalBounds();
    if (shape1.intersects(shape2)) {
        return true;
    }
    else {
        return false;
    }
}

void updateInput() {
    sf::Event event;
    // while there are pending events...
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Up) {
                hero.jump(750.0f);
            }
            if (event.key.code == sf::Keyboard::Down) {
                shoot();
            }
        }
        if (event.key.code == sf::Keyboard::Escape || event.type ==
            sf::Event::Closed)
            window.close();
    }
}
void update(float dt) {
    hero.update(dt);
    currentTime += dt;
    // Spawn Enemies
    if (currentTime >= prevTime + 1.125f) {
        spawnEnemy();
        prevTime = currentTime;
        // Update Enemies
        for (int i = 0; i < enemies.size(); i++) {
            Enemy* enemy = enemies[i];
            enemy->update(dt);
            if (enemy->getSprite().getPosition().x < 0) {
                enemies.erase(enemies.begin() + i);
                delete(enemy);
            }
        };
        // Update rockets
        for (int i = 0; i < rockets.size(); i++) {
            Rocket* rocket = rockets[i];
            rocket->update(dt);
            if (rocket->getSprite().getPosition().x > viewSize.x) {
                rockets.erase(rockets.begin() + i);
                delete(rocket);
            }
        }
        // Check collision between Rocket and Enemies
        for (int i = 0; i < rockets.size(); i++) {
            for (int j = 0; j < enemies.size(); j++) {
                Rocket* rocket = rockets[i];
                Enemy* enemy = enemies[j];
                if (checkCollision(rocket->getSprite(), enemy->getSprite())) {
                    rockets.erase(rockets.begin() + i);
                    enemies.erase(enemies.begin() + j);
                    delete(rocket);
                    delete(enemy);
                    printf(" rocket intersects enemy \n");
                }
            }
        }
    }
}

void draw() {
    window.draw(skySprite);
    window.draw(bgSprite);
    window.draw(hero.getSprite());
    for (Enemy* enemy : enemies) {
        window.draw(enemy->getSprite());
    }
    for (Rocket* rocket : rockets) {
        window.draw(rocket->getSprite());
    }
}
int main() {
    sf::Clock clock;
    window.setFramerateLimit(60);
    init();
    while (window.isOpen()) {
        updateInput();
        sf::Time dt = clock.restart();
        update(dt.asSeconds());
        window.clear(sf::Color::Red);
        draw();
        window.display();
    }
    return 0;
}

