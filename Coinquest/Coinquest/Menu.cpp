#include <Menu.h>

StartMenu::Menu(float width, float height) {
	if (!font.loadFromFile("Fonts not Available")) {
		cout << "No font here";
	}

	//Play
	startMenu[0].setFont(font);
	startMenu[0].setFillColor(Color::White);
	startMenu[0].setString("Play");
	startMenu[0].setCharactersSize(70);
	startMenu[0].setPosition(400, 200);

	//Options
	startMenu[1].setFont(font);
	startMenu[1].setFillColor(Color::White);
	startMenu[1].setString("Options");
	startMenu[1].setCharactersSize(70);
	startMenu[1].setPosition(400, 300);

	//Exit
	startMenu[2].setFont(font);
	startMenu[2].setFillColor(Color::White);
	startMenu[2].setString("EXIT");
	startMenu[2].setCharactersSize(70);
	startMenu[2].setPosition(400, 400);

	startMenuSelected = -1;
}
StartMenu::Menu() {

}
//Draw MainMenu
void Menu::draw(RenderWindow& window) {
	for (int i = 0; i < Max_menu; i++) {
		window.draw(Menu[i]);
	}
}

//Move Up 
void StartMenu::MoveUp() {
	if (startMenuSelected - 1 >= 0) {
		Menu[startMenuSelected].setFillColor(Color::white);

		startMenuSelected--;
		if (startMenuSelected == -1) {
			startMenuSelected = 2;

		}
		Menu[startMenuSelected].setFillColor(Color::Blue);

	}
}

//Move Down
void StartMenu::MoveDown() {
	if (startMenuSelected + 1 <= Max_menu) {
		Menu[startMenuSelected].setFillColor(Color::white);

		startMenuSelected++;
		if (startMenuSelected == 4) {
			startMenuSelected = 0;

		}
		Menu[startMenuSelected].setFillColor(Color::Blue);

	}
}