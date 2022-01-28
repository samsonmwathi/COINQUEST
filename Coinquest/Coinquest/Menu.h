#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
  
using namespace std;
using namespace sf;

#define Max_menu 4;
class StartMenu
{

public:
	StartMenu(float width, float height);

	void draw(RenderWindow window);
	void MoveUp();
	void MoveDown();

	int MenuPressed() {
		return	MenuSelected;
	}
	~StartMenu();

private:
	int MenuSelected;
	Font font;
	Text startMenu[Max_menu];
};

