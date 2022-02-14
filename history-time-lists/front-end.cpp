
#include "back-end.h"
#include "front-end.h"

#include"SFML/Graphics.hpp"
#include<iostream>
using namespace std;
using namespace sf;

// Define keys:
#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

class Textbox {
public:
	Textbox(int size, sf::Color color, bool sel) {
		textbox.setCharacterSize(size);
		textbox.setFillColor(color);
		isSelected = sel;

		if (isSelected)
			textbox.setString("_");
		else
			textbox.setString("");
	}


	// Make sure font is passed by reference:
	void setFont(sf::Font& fonts) {
		textbox.setFont(fonts);
	}

	void setPosition(sf::Vector2f point) {
		textbox.setPosition(point);
	}

	// Set char limits:
	void setLimit(bool ToF) {
		hasLimit = ToF;
	}

	void setLimit(bool ToF, int lim) {
		hasLimit = ToF;
		limit = lim - 1;
	}

	// Change selected state:
	void setSelected(bool sel) {
		isSelected = sel;

		// If not selected, remove the '_' at the end:
		if (!sel) {
			std::string t = text.str();
			std::string newT = "";
			for (int i = 0; i < t.length(); i++) {
				newT += t[i];
			}
			textbox.setString(newT);
		}
	}

	std::string getText() {
		return text.str();
	}

	std::string deleteAll() {

		text.str("_");
		textbox.setString(text.str());
		return text.str();
	}

	void drawTo(sf::RenderWindow& window) {
		window.draw(textbox);
	}

	// Function for event loop:
	void typedOn(sf::Event input) {
		if (isSelected) {
			int charTyped = input.text.unicode;

			// Only allow normal inputs:
			if (charTyped < 128) {
				if (hasLimit) {
					// If there's a limit, don't go over it:
					if (text.str().length() <= limit) {
						inputLogic(charTyped);
					}
					// But allow for char deletions:
					else if (text.str().length() > limit && charTyped == DELETE_KEY) {
						deleteLastChar();
					}
				}
				// If no limit exists, just run the function:
				else {
					inputLogic(charTyped);
				}
			}
		}
	}

private:
	sf::Text textbox;

	std::ostringstream text;
	bool isSelected = false;
	bool hasLimit = false;
	int limit = 0;

	// Delete the last character of the text:
	void deleteLastChar() {
		std::string t = text.str();
		std::string newT = "";
		for (int i = 0; i < t.length() - 1; i++) {
			newT += t[i];
		}
		text.str("");
		text << newT;
		textbox.setString(text.str() + "_");
	}

	// Get user input:
	void inputLogic(int charTyped) {
		// If the key pressed isn't delete, or the two selection keys, then append the text with the char:
		if (charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY) {
			text << static_cast<char>(charTyped);
		}
		// If the key is delete, then delete the char:
		else if (charTyped == DELETE_KEY) {
			if (text.str().length() > 0) {
				deleteLastChar();
			}
		}

		// Set the textbox text:
		textbox.setString(text.str() + "_");
	}
};


class Button {
public:
	Button(std::string btnText, sf::Vector2f buttonSize, int charSize, sf::Color bgColor, sf::Color textColor) {
		button.setSize(buttonSize);
		button.setFillColor(bgColor);

		// Get these for later use:
		btnWidth = buttonSize.x;
		btnHeight = buttonSize.y;

		text.setString(btnText);
		text.setCharacterSize(charSize);
		text.setFillColor(textColor);
	}

	// Pass font by reference:
	void setFont(sf::Font& fonts) {
		text.setFont(fonts);
	}

	void hoverColorYes() {
		text.setFillColor(sf::Color::White);
	}
	void hoverColorNo() {
		text.setFillColor(sf::Color::Black);
	}

	void setTextColor(sf::Color color) {
		text.setFillColor(color);
	}

	void setPosition(sf::Vector2f point) {
		button.setPosition(point);

		// Center text on button:
		float xPos = (point.x + btnWidth / 2) - (text.getLocalBounds().width / 2);
		float yPos = (point.y + btnHeight / 2.2) - (text.getLocalBounds().height / 2);
		text.setPosition(xPos, yPos);
	}

	void drawTo(sf::RenderWindow& window) {
		window.draw(button);
		window.draw(text);
	}

	// Check if the mouse is within the bounds of the button:
	bool isMouseOver(sf::RenderWindow& window) {
		int mouseX = sf::Mouse::getPosition(window).x;
		int mouseY = sf::Mouse::getPosition(window).y;

		int btnPosX = button.getPosition().x;
		int btnPosY = button.getPosition().y;

		int btnxPosWidth = button.getPosition().x + btnWidth;
		int btnyPosHeight = button.getPosition().y + btnHeight;

		if (mouseX < btnxPosWidth && mouseX > btnPosX && mouseY < btnyPosHeight && mouseY > btnPosY) {
			return true;
		}
		return false;
	}
private:
	sf::RectangleShape button;
	sf::Text text;

	int btnWidth;
	int btnHeight;
};

RenderWindow window(VideoMode(1000, 800), "Helpopedia", Style::Close);

void backToMenu(int* ptr1, Event event, Text* textOne)
{
	if (Mouse::getPosition(window).x > 0 && Mouse::getPosition(window).x < (*textOne).getCharacterSize() * 2.25 && Mouse::getPosition(window).y>770 && Mouse::getPosition(window).y < 800)
	{
		(*textOne).setFillColor(Color::White);
		if (event.type == Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == Mouse::Left)
			{
				*ptr1 = 0;
			}
		}
	}
	else
	{
		(*textOne).setFillColor(Color::Black);
	}
}

void backToMenuFromCreate(int* ptr1, Event event, Text* textOne, Text* textTwo)
{
	if ((Mouse::getPosition(window).x > 30 &&
		Mouse::getPosition(window).x < 100 &&
		Mouse::getPosition(window).y>window.getSize().y - 50 &&
		Mouse::getPosition(window).y < window.getSize().y - 20))
	{
		(*textOne).setFillColor(Color::White);
		if (event.type == Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == Mouse::Left)
			{
				*ptr1 = 0;
				(*textTwo).setString("Choose one:");
			}
		}
	}
	else
	{
		(*textOne).setFillColor(Color::Black);
	}
}

void finishToMenuFromCreate(int* ptr1, Event event, Text* textTwo)
{
	if ((Mouse::getPosition(window).x > 875 &&
		Mouse::getPosition(window).x < 965 &&
		Mouse::getPosition(window).y>window.getSize().y - 50 &&
		Mouse::getPosition(window).y < window.getSize().y - 20))
	{
		if (event.type == Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == Mouse::Left)
			{
				*ptr1 = 0;
				(*textTwo).setString("Choose one:");
			}
		}
	}
}

void dropDown(RectangleShape* rectangle, int minY, int maxY)
{
	if (Mouse::getPosition(window).x > 50 && Mouse::getPosition(window).x < window.getSize().x - 50 &&
		Mouse::getPosition(window).y>minY && Mouse::getPosition(window).y < maxY)
	{
		(*rectangle).setFillColor(Color::Color(213, 169, 134));
	}
	else
	{
		(*rectangle).setFillColor(Color::Color(207, 159, 119));
	}
}

void currentLocation(int* ptr, int n, Event event, Text* textOne)
{
	(*textOne).setFillColor(Color::White);
	if (event.type == Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == Mouse::Left)
		{
			*ptr = n;
		}
	}
}

void currentLocationDropDown(int* ptr, int n, Event event)
{
	if (event.type == Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == Mouse::Left)
		{
			*ptr = n;
		}
	}

}

void textPosition(int* location, Event event, Text* text, int n, int minY, int maxY)
{
	if (Mouse::getPosition(window).x > window.getSize().x / 2 - (*text).getCharacterSize() * 1.25 &&
		Mouse::getPosition(window).x < window.getSize().x / 2 + (*text).getCharacterSize() * 1.75 &&
		Mouse::getPosition(window).y > minY && Mouse::getPosition(window).y < maxY)
	{
		currentLocation(location, n, event, text);
	}
	else
	{
		(*text).setFillColor(Color::Black);
	}
}

void setRectangleEventsTab(RectangleShape* rectangle, int posX, int posY)
{
	(*rectangle).setFillColor(Color::Black);
	(*rectangle).setPosition(posX, posY);
}

void setRectangleDropDown(RectangleShape* rectangle, int posY)
{
	(*rectangle).setFillColor(Color::Color(188, 145, 118));
	(*rectangle).setPosition(window.getSize().x - 310, posY);
}

void setMenuText(const string str, Text* text, int minusX, int posY)
{
	(*text).setString(str);
	(*text).setCharacterSize(40);
	(*text).setPosition(window.getSize().x / 2 - minusX, posY);
	(*text).setFillColor(Color::Black);
}

void setDropDownMenuText(Text* text, int posY)
{
	(*text).setCharacterSize(20);
	(*text).setPosition(window.getSize().x - 200, posY);
	(*text).setFillColor(Color::White);
}

void setRectangleCreateMainOne(RectangleShape* rectangle, int plusLeft, int mulRight)
{
	(*rectangle).setFillColor(Color::Color(188, 145, 118));
	(*rectangle).setPosition(35, plusLeft + (window.getSize().y / 8) * mulRight);
}

void addFromOrBack(RectangleShape* rectangle, int posY) // ogradka
{
	//(*rectangle).setFillColor(Color::Color(186, 166, 127));
	(*rectangle).setPosition(50, posY);
}

void addFromOrBackTwo(RectangleShape* rectangle, int posY) // vutre
{
	(*rectangle).setFillColor(Color::Color(249, 239, 239));
	(*rectangle).setPosition(55, posY);
}
void drowFrontBackOrEditTab(RectangleShape rectangle1, RectangleShape rectangle2, RectangleShape rectangle3, RectangleShape rectangle4, RectangleShape rectangle5, RectangleShape rectangle6, RectangleShape rectangle7,
	RectangleShape rectangle8, RectangleShape rectangle9, RectangleShape rectangle10, RectangleShape rectangle11, RectangleShape rectangle12, RectangleShape rectangle13, RectangleShape rectangle14, RectangleShape rectangle15, RectangleShape rectangle16)
{
	window.draw(rectangle1);
	window.draw(rectangle2);
	window.draw(rectangle3);
	window.draw(rectangle4);
	window.draw(rectangle5);
	window.draw(rectangle6);
	window.draw(rectangle14);
	window.draw(rectangle15);

	window.draw(rectangle7);
	window.draw(rectangle8);
	window.draw(rectangle9);
	window.draw(rectangle10);
	window.draw(rectangle11);
	window.draw(rectangle12);
	window.draw(rectangle13);
	window.draw(rectangle16);
}

void textFrontBackOrEditTab(Text* text, int posY)
{
	(*text).setCharacterSize(25);
	(*text).setPosition(50, posY);
	(*text).setFillColor(Color::Black);
}

void deleteAllButton(Event event, int* ptr)
{
	if (event.type == Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == Mouse::Left)
		{
			*ptr = 0;
		}
	}
}

void setUpMenu() {

	Font f1;
	if (!f1.loadFromFile("Pacifico-Regular.ttf"))
		std::cout << "Font not found!\n";

	Font f2;
	if (!f2.loadFromFile("DroidSansMono.ttf"))
		std::cout << "Font not found!\n";

	Textbox textBox1(20, sf::Color::Black, true);
	textBox1.setPosition({ 60, 70 });
	textBox1.setLimit(true, 40);
	textBox1.setFont(f2);

	Textbox textBox2(20, sf::Color::Black, true);
	textBox2.setPosition({ 60, 170 });
	textBox2.setLimit(true, 4);
	textBox2.setFont(f2);

	Textbox textBox3(20, sf::Color::Black, true);
	textBox3.setPosition({ 60, 270 });
	textBox3.setLimit(true, 40);
	textBox3.setFont(f2);

	Textbox textBox4(20, sf::Color::Black, true);
	textBox4.setPosition({ 60, 370 });
	textBox4.setLimit(true, 40);
	textBox4.setFont(f2);

	Textbox textBox5(20, sf::Color::Black, true);
	textBox5.setPosition({ 60, 470 });
	textBox5.setLimit(true, 40);
	textBox5.setFont(f2);

	Textbox textBox6(20, sf::Color::Black, true);
	textBox6.setPosition({ 60, 570 });
	textBox6.setLimit(true, 40);
	textBox6.setFont(f2);

	Textbox textBox7(20, sf::Color::Black, true);
	textBox7.setPosition({ 60, 670 });
	textBox7.setLimit(true, 40);
	textBox7.setFont(f2);

	Textbox textBox8(20, sf::Color::Black, true);
	textBox8.setPosition({ 600, 70 });
	textBox8.setLimit(true, 30);
	textBox8.setFont(f2);

	Textbox textBox81(20, sf::Color::Black, true);
	textBox81.setPosition({ 600, 70 + 64 * 1 });
	textBox81.setLimit(true, 30);
	textBox81.setFont(f2);

	Textbox textBox82(20, sf::Color::Black, true);
	textBox82.setPosition({ 600, 70 + 64 * 2 });
	textBox82.setLimit(true, 30);
	textBox82.setFont(f2);

	Textbox textBox83(20, sf::Color::Black, true);
	textBox83.setPosition({ 600, 70 + 64 * 3 });
	textBox83.setLimit(true, 30);
	textBox83.setFont(f2);

	Textbox textBox84(20, sf::Color::Black, true);
	textBox84.setPosition({ 600, 70 + 64 * 4 });
	textBox84.setLimit(true, 30);
	textBox84.setFont(f2);

	Textbox textBox85(20, sf::Color::Black, true);
	textBox85.setPosition({ 600, 70 + 64 * 5 });
	textBox85.setLimit(true, 30);
	textBox85.setFont(f2);

	Textbox textBox86(20, sf::Color::Black, true);
	textBox86.setPosition({ 600, 70 + 64 * 6 });
	textBox86.setLimit(true, 30);
	textBox86.setFont(f2);

	Textbox textBox87(20, sf::Color::Black, true);
	textBox87.setPosition({ 600, 70 + 64 * 7 });
	textBox87.setLimit(true, 30);
	textBox87.setFont(f2);

	Textbox textBox88(20, sf::Color::Black, true);
	textBox88.setPosition({ 600, 70 + 64 * 8 });
	textBox88.setLimit(true, 30);
	textBox88.setFont(f2);

	Textbox textBox89(20, sf::Color::Black, true);
	textBox89.setPosition({ 600, 70 + 64 * 9 });
	textBox89.setLimit(true, 30);
	textBox89.setFont(f2);

	int moreText = 0;
	int infoChoice = 1;
	string allText;

	Textbox textBox9(20, sf::Color::Black, true);
	textBox9.setPosition({ 530, 375 });
	textBox9.setLimit(true, 3);
	textBox9.setFont(f2);

	Textbox textBox10(20, sf::Color::Black, true);
	textBox10.setPosition({ 300, 170 });
	textBox10.setLimit(true, 3);
	textBox10.setFont(f2);



	Textbox textBoxGame1(20, sf::Color::Black, true);
	textBoxGame1.setPosition({ 715,175 });
	textBoxGame1.setLimit(true, 4);
	textBoxGame1.setFont(f2);
	bool canWriteGame1 = false;

	Textbox textBoxGame2(20, sf::Color::Black, true);
	textBoxGame2.setPosition({ 715, 280 });
	textBoxGame2.setLimit(true, 4);
	textBoxGame2.setFont(f2);
	bool canWriteGame2 = false;

	Textbox textBoxGame3(20, sf::Color::Black, true);
	textBoxGame3.setPosition({ 715, 385 });
	textBoxGame3.setLimit(true, 4);
	textBoxGame3.setFont(f2);
	bool canWriteGame3 = false;

	Textbox textBoxGame4(20, sf::Color::Black, true);
	textBoxGame4.setPosition({ 715,490 });
	textBoxGame4.setLimit(true, 4);
	textBoxGame4.setFont(f2);
	bool canWriteGame4 = false;

	Textbox textBoxGame5(20, sf::Color::Black, true);
	textBoxGame5.setPosition({ 715, 595 });
	textBoxGame5.setLimit(true, 4);
	textBoxGame5.setFont(f2);
	bool canWriteGame5 = false;

	Textbox textBoxGame6(20, sf::Color::Black, true);
	textBoxGame6.setPosition({ 715, 700 });
	textBoxGame6.setLimit(true, 4);
	textBoxGame6.setFont(f2);
	bool canWriteGame6 = false;

	/*rectanglePlayBox4.setFillColor(Color::Black);
rectanglePlayBox4.setPosition(210 + window.getSize().x / 2, 170);

rectanglePlayBox41.setFillColor(Color::White);
rectanglePlayBox41.setPosition(215 + window.getSize().x / 2, 175);

rectanglePlayBox5.setFillColor(Color::Black);
rectanglePlayBox5.setPosition(210 + window.getSize().x / 2, 275);

rectanglePlayBox51.setFillColor(Color::White);
rectanglePlayBox51.setPosition(215 + window.getSize().x / 2, 280);

rectanglePlayBox6.setFillColor(Color::Black);
rectanglePlayBox6.setPosition(210 + window.getSize().x / 2, 380);

rectanglePlayBox61.setFillColor(Color::White);
rectanglePlayBox61.setPosition(215 + window.getSize().x / 2, 385);*/

	int whoIsChoiced = 0;
	int howManyEventsHave = 0;
	int EventsHave = -1;
	int rectangles = 0;
	string titleAndYear[100];
	string allInfo[100];
	string allInfo2[100];
	string allInfo3[100];
	string allInfo4[100];
	int dHelp = 1;
	int D = -1;
	int choiceYesNo = -1;
	int choicePos = -1;
	string autoSave;
	int pos = 0;
	int counterP = 0;

	Button btn1("Finish", { 80, 40 }, 30, sf::Color::Transparent, sf::Color::Black);
	btn1.setFont(f1);
	btn1.setPosition({ 880, 740 });

	Button btn2("Check", { 80, 40 }, 30, sf::Color::Transparent, sf::Color::Black);
	btn2.setFont(f1);
	btn2.setPosition({ 820, 710 });

	int location = 0, locCreate = 0;

	Texture tex1, tex2, tex3, tex4, tex5, tex6, tex7, tex8, tex9, texH, texS, texG, texM, tex10, tex11;
	Text textFE, textBE, textST, textQA, textH, textS, textG, textM, textGame1, textGame2, textCodeOfGray, textHowToPlay, textCheck, textRandom, textHint, textPlay;
	Sprite s1(tex1), s2(tex2), s3(tex3), s4(tex4), s5(tex5), s6(tex6), s7(tex7), s8(tex8), s9(tex9), sH(texH), sS(texS), sG(texG), sM(texM), s10(tex10), s11(tex11);

	textPlay.setString("Play");
	textPlay.setFont(f1);
	textPlay.setCharacterSize(30);
	textPlay.setPosition(window.getSize().x - 70, 760);
	textPlay.setFillColor(Color::Black);

	textGame1.setString("How to play a game");
	textGame1.setFont(f1);
	textGame1.setCharacterSize(30);
	textGame1.setPosition(window.getSize().x / 2 - 120, 80);
	textGame1.setFillColor(Color::Color(210, 210, 210, 255));

	textGame2.setString("Code of gray");
	textGame2.setFont(f1);
	textGame2.setCharacterSize(30);
	textGame2.setPosition(window.getSize().x / 2 - 90, window.getSize().y / 2 + 30);
	textGame2.setFillColor(Color::Color(210, 210, 210, 255));

	textHowToPlay.setString("qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq\nqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq\nqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq\nqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq\nqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq\nqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq");
	textHowToPlay.setFont(f1);
	textHowToPlay.setCharacterSize(20);
	textHowToPlay.setPosition(245, 160);
	textHowToPlay.setFillColor(Color::Black);

	textCodeOfGray.setString("qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq\nqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq\nqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq\nqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq\nqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq\nqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq");
	textCodeOfGray.setFont(f1);
	textCodeOfGray.setCharacterSize(20);
	textCodeOfGray.setPosition(245, 510);
	textCodeOfGray.setFillColor(Color::Black);

	textCheck.setString("Check");
	textCheck.setFont(f1);
	textCheck.setCharacterSize(30);
	textCheck.setPosition(window.getSize().x - 180, window.getSize().y - 90);
	textCheck.setFillColor(Color::Black);

	textRandom.setString("Random");
	textRandom.setFont(f1);
	textRandom.setCharacterSize(30);
	textRandom.setPosition(100, window.getSize().y - 90);
	textRandom.setFillColor(Color::Black);

	textHint.setString("Hint:");
	textHint.setFont(f1);
	textHint.setCharacterSize(30);
	textHint.setPosition(window.getSize().x / 2 + 180, 50);
	textHint.setFillColor(Color::Black);

	textFE.setString("Front-end");
	textFE.setFont(f1);
	textFE.setCharacterSize(20);
	textFE.setPosition(130, window.getSize().y / 2 - 50);
	textFE.setFillColor(Color::Black);

	textBE.setString("Back-end");
	textBE.setFont(f1);
	textBE.setCharacterSize(20);
	textBE.setPosition(350, window.getSize().y / 2 - 50);
	textBE.setFillColor(Color::Black);

	textQA.setString("QA");
	textQA.setFont(f1);
	textQA.setCharacterSize(20);
	textQA.setPosition(595, window.getSize().y / 2 - 50);
	textQA.setFillColor(Color::Black);

	textST.setString("Scrum-trainer");
	textST.setFont(f1);
	textST.setCharacterSize(20);
	textST.setPosition(765, window.getSize().y / 2 - 50);
	textST.setFillColor(Color::Black);

	textH.setString("Hristiyan Kimryanov");
	textH.setFont(f1);
	textH.setCharacterSize(20);
	textH.setPosition(80, window.getSize().y / 2 - 100);
	textH.setFillColor(Color::Black);

	textS.setString("Stas Uzunov");
	textS.setFont(f1);
	textS.setCharacterSize(20);
	textS.setPosition(340, window.getSize().y / 2 - 100);
	textS.setFillColor(Color::Black);

	textG.setString("George Mateev");
	textG.setFont(f1);
	textG.setCharacterSize(20);
	textG.setPosition(538, window.getSize().y / 2 - 100);
	textG.setFillColor(Color::Black);

	textM.setString("Mertin Dikmeshefket");
	textM.setFont(f1);
	textM.setCharacterSize(20);
	textM.setPosition(730, window.getSize().y / 2 - 100);
	textM.setFillColor(Color::Black);

	texH.loadFromFile("../images/Hristiyan.jpg");
	texS.loadFromFile("../images/Stas.jpg");
	texG.loadFromFile("../images/George.jpg");
	texM.loadFromFile("../images/Mertin.jpg");


	sH.setTextureRect(IntRect(0, 0, 200, 200));
	sS.setTextureRect(IntRect(0, 0, 200, 200));
	sG.setTextureRect(IntRect(0, 0, 200, 200));
	sM.setTextureRect(IntRect(0, 0, 200, 200));


	sH.setPosition(75, 75);
	sS.setPosition(293, 75);
	sG.setPosition(511, 75);
	sM.setPosition(729, 75);

	Text text1, text2, text3, text4, text5, text, text6, text7, text8, text9, text10, text11, text12, text13, text14, text15, text16,
		text17, text18, text19, text20, text21, text22, text23, text24, text100;

	text1.setFont(f1);
	setMenuText("Events", &text1, 50, 500);

	text2.setFont(f1);
	setMenuText("Create", &text2, 50, 550);

	text3.setFont(f1);
	setMenuText("Game", &text3, 50, 600);

	text4.setFont(f1);
	setMenuText("About us", &text4, 50, 660);

	text5.setFont(f1);
	setMenuText("Quit", &text5, 50, 710);

	text6.setString("Back");
	text6.setFont(f1);
	text6.setCharacterSize(30);
	text6.setPosition(0, 770);
	text6.setFillColor(Color::Color(210, 210, 210, 255));

	text8.setString("Add at the ending");
	text8.setFont(f1);
	setDropDownMenuText(&text8, 75);
	text8.setPosition(window.getSize().x - 230, 75);

	text9.setString("Add at the beginning");
	text9.setFont(f1);
	setDropDownMenuText(&text9, 115);
	text9.setPosition(window.getSize().x - 240, 115);

	text11.setString("Add at position");
	text11.setFont(f1);
	setDropDownMenuText(&text11, 155);
	text11.setPosition(window.getSize().x - 223, 155);

	text12.setString("Edit");
	text12.setFont(f1);
	setDropDownMenuText(&text12, 195);
	text12.setPosition(window.getSize().x - 190, 195);

	text13.setString("Delete");
	text13.setFont(f1);
	setDropDownMenuText(&text13, 235);
	text13.setPosition(window.getSize().x - 195, 235);

	text14.setString("Delete all");
	text14.setFont(f1);
	setDropDownMenuText(&text14, 275);
	text14.setPosition(window.getSize().x - 205, 275);

	text15.setString("Save");
	text15.setFont(f1);
	setDropDownMenuText(&text15, 315);
	text15.setPosition(window.getSize().x - 190, 315);

	text16.setString("Auto save");
	text16.setFont(f1);
	setDropDownMenuText(&text16, 355);
	text16.setPosition(window.getSize().x - 205, 355);

	text10.setString("Choose one:");
	text10.setFont(f1);
	setDropDownMenuText(&text10, 30);
	text10.setPosition(window.getSize().x - 210, 30);

	text17.setString("Title:");
	text17.setFont(f1);
	textFrontBackOrEditTab(&text17, 30);

	text100.setString("Position:");
	text100.setFont(f1);
	text100.setFont(f1);
	text100.setCharacterSize(25);
	text100.setPosition(300, 125);
	text100.setFillColor(Color::Black);

	text18.setString("Year:");
	text18.setFont(f1);
	textFrontBackOrEditTab(&text18, 125);

	text19.setString("Participants:");
	text19.setFont(f1);
	textFrontBackOrEditTab(&text19, 225);

	text20.setString("Era:");
	text20.setFont(f1);
	textFrontBackOrEditTab(&text20, 330);

	text21.setString("Location:");
	text21.setFont(f1);
	textFrontBackOrEditTab(&text21, 430);

	text22.setString("Reason:");
	text22.setFont(f1);
	textFrontBackOrEditTab(&text22, 530);

	text23.setString("Result:");
	text23.setFont(f1);
	textFrontBackOrEditTab(&text23, 630);

	text24.setString("Description:");
	text24.setFont(f1);
	text24.setCharacterSize(25);
	text24.setPosition(window.getSize().x / 2 + 80, 25);
	text24.setFillColor(Color::Black);

	tex1.loadFromFile("../images/Logo.png");
	tex2.loadFromFile("../images/Menu.png");

	tex3.loadFromFile("../images/Lupa.png");

	//tex4.loadFromFile("../images/arrowRight.png");
	//tex5.loadFromFile("../images/arrowRight.png");

	//tex6.loadFromFile("../images/arrowLeft.png");
	//tex7.loadFromFile("../images/arrowLeft.png");

	tex8.loadFromFile("../images/upArrow.png");
	tex9.loadFromFile("../images/downArrow.png");


	tex10.loadFromFile("../images/upArrow2.png");//impo
	tex11.loadFromFile("../images/downArrow2.png");//impo

	int fu1 = 65, n1 = 0, locGame = 0;
	RectangleShape rectangle(Vector2f(900, 450)), /*rectangle1(Vector2f((window.getSize().x / 2 - 80) / 2, (window.getSize().y / 2 - 40) / 3 - 5))*/
		rectangle2(Vector2f(200, 250)), rectangle3(Vector2f(200, 250)),
		rectangle4(Vector2f(140, 250)), rectangle5(Vector2f(window.getSize().x - 350, window.getSize().y - 50)),
		rectangle7(Vector2f(window.getSize().x - 700, 40)), rectangle8(Vector2f(window.getSize().x - 700, 40)), rectangle9(Vector2f(window.getSize().x - 700, 40)),
		rectangle22(Vector2f(window.getSize().x - 700, 40)), rectangle23(Vector2f(window.getSize().x - 700, 40)), rectangle24(Vector2f(window.getSize().x - 700, 40)),
		rectangle25(Vector2f(window.getSize().x - 700, 40)), rectangle26(Vector2f(window.getSize().x - 700, 40)), rectangle27(Vector2f(window.getSize().x - 700, 40)),

		rectangle10(Vector2f(window.getSize().x - 360, window.getSize().y - 60)), rectangle11(Vector2f(window.getSize().x - 390, window.getSize().y / 8)),
		rectangle12(Vector2f(window.getSize().x - 390, window.getSize().y / 8)), rectangle13(Vector2f(window.getSize().x - 390, window.getSize().y / 8)),
		rectangle14(Vector2f(window.getSize().x - 390, window.getSize().y / 8)), rectangle15(Vector2f(window.getSize().x - 390, window.getSize().y / 8)),
		rectangle16(Vector2f(window.getSize().x - 390, window.getSize().y / 8)), rectangle17(Vector2f(window.getSize().x - 390, window.getSize().y / 8)),

		rectangle18(Vector2f(window.getSize().x - 390, window.getSize().y / 8)), rectangle19(Vector2f(window.getSize().x - 390, window.getSize().y / 8)),
		rectangle20(Vector2f(window.getSize().x - 390, window.getSize().y / 8)), rectangle21(Vector2f(window.getSize().x - 390, window.getSize().y / 8)),

		//Cray rectangles Create 
		rectangle28(Vector2f(window.getSize().x / 2, 40)), rectangle29(Vector2f(window.getSize().x / 2, 40)),
		rectangle30(Vector2f(window.getSize().x / 2, 40)), rectangle31(Vector2f(window.getSize().x / 2, 40)),
		rectangle32(Vector2f(window.getSize().x / 2, 40)), rectangle33(Vector2f(window.getSize().x / 2, 40)),
		rectangle41(Vector2f(window.getSize().x / 2 - 110, window.getSize().y - 160)),

		//White rectangles Create 
		rectangle34(Vector2f(window.getSize().x / 2 - 10, 30)), rectangle35(Vector2f(window.getSize().x / 2 - 10, 30)),
		rectangle36(Vector2f(window.getSize().x / 2 - 10, 30)), rectangle37(Vector2f(window.getSize().x / 2 - 10, 30)),
		rectangle38(Vector2f(window.getSize().x / 2 - 10, 30)), rectangle39(Vector2f(window.getSize().x / 2 - 10, 30)),
		rectangle40(Vector2f(window.getSize().x / 2 - 120, window.getSize().y - 170));
	RectangleShape rectangle42(Vector2f(window.getSize().x / 2, 40)), rectangle43(Vector2f(window.getSize().x / 2 - 10, 30)),

		rectangleMoreInfo(Vector2f((window.getSize().x - 100) / 3, window.getSize().y / 2 - 15)),
		rectangleMoreInf(Vector2f((window.getSize().x - 130) / 3, window.getSize().y / 2 - 25)),

		//Gray rectangles Events
		rectangle44(Vector2f(window.getSize().x / 2 + 150, window.getSize().y / 2 + 50)),
		rectangle45(Vector2f((window.getSize().x - 210) / 2, window.getSize().y / 2 - 160)),
		rectangle46(Vector2f(window.getSize().x / 2, window.getSize().y / 2 - 160)),
		rectangle47(Vector2f(window.getSize().x / 2 - 270, window.getSize().y / 2 - 30)),
		rectangle53(Vector2f(window.getSize().x / 2 + 130, window.getSize().y / 14)),

		//White rectangles Events 
		rectangle48(Vector2f(window.getSize().x / 2 + 140, window.getSize().y / 2 - 30)),
		rectangle49(Vector2f((window.getSize().x - 230) / 2, window.getSize().y / 2 - 170)),
		rectangle50(Vector2f(window.getSize().x / 2 - 30, window.getSize().y / 2 - 170)),//Yes
		rectangle51(Vector2f((window.getSize().x / 2 - 60) / 2, window.getSize().y / 2 - 40)),
		rectangle52(Vector2f(window.getSize().x / 2 + 140, window.getSize().y / 12)),//Ne


		recrtangleSearch1(Vector2f(window.getSize().x / 2 - 270, window.getSize().y / 13.5)),
		recrtangleSearch2(Vector2f((window.getSize().x / 2 - 60) / 2, window.getSize().y / 16.5)),
		rectangle54(Vector2f(window.getSize().x / 2 - 465, window.getSize().y / 2 - 170)),
		rectangle55(Vector2f(window.getSize().x / 2 - 470, window.getSize().y / 2 - 170)),
		rectangleScroll, rectangleScroll1,

		// choice yes or no
		rectangleDDASSA(Vector2f(window.getSize().x / 3 + 100, window.getSize().y / 4)),
		rectangleDDASSAMini1(Vector2f(window.getSize().x / 10, window.getSize().y / 20)),
		rectangleDDASSAMini2(Vector2f(window.getSize().x / 10, window.getSize().y / 20)),
		rectangleDDASSA1(Vector2f(window.getSize().x / 3 + 90, window.getSize().y / 4 - 10)),

		recrtangleAboutUsH1(Vector2f(window.getSize().x / 10, window.getSize().y / 40)),
		recrtangleAboutUsH2(Vector2f(200, window.getSize().y / 40)),
		recrtangleAboutUsS1(Vector2f(window.getSize().x / 10, window.getSize().y / 40)),
		recrtangleAboutUsS2(Vector2f(window.getSize().x / 10 + 60, window.getSize().y / 40)),
		recrtangleAboutUsG1(Vector2f(window.getSize().x / 10, window.getSize().y / 40)),
		recrtangleAboutUsG2(Vector2f(window.getSize().x / 10 + 60, window.getSize().y / 40)),
		recrtangleAboutUsM1(Vector2f(window.getSize().x / 10 + 40, window.getSize().y / 40)),
		recrtangleAboutUsM2(Vector2f(200, window.getSize().y / 40)), rectangleMiddle1(Vector2f(250, 50)), rectangleMiddle2(Vector2f(240, 40)),
		recrtangleAboutUs1(Vector2f(window.getSize().x - 100, window.getSize().y / 2 - 30)),
		recrtangleAboutUs2(Vector2f(window.getSize().x - 110, window.getSize().y / 2 - 40)),
		recrtangleAboutUs3(Vector2f(window.getSize().x - 260, window.getSize().y / 4 - 40)),
		recrtangleAboutUs4(Vector2f(window.getSize().x - 270, window.getSize().y / 4 - 50)),
		recrtangleAboutUs5(Vector2f(210, 210)),
		recrtangleAboutUs6(Vector2f(210, 210)),
		recrtangleAboutUs7(Vector2f(210, 210)),
		recrtangleAboutUs8(Vector2f(210, 210)),
		rectangleEvent1(Vector2f(450, 45)),
		rectangleEvent2(Vector2f(450, 45)),
		rectangleEvent3(Vector2f(450, 45)),
		rectangleEvent4(Vector2f(450, 45)),
		recrtangleGame1(Vector2f(window.getSize().x - 400, window.getSize().y - 100)),
		recrtangleGame2(Vector2f(window.getSize().x - 410, (window.getSize().y - 120) / 2)),
		recrtangleGame3(Vector2f(window.getSize().x - 410, (window.getSize().y - 120) / 2)),
		recrtangleGame4(Vector2f(window.getSize().x - 420, (window.getSize().y - 130) / 2 - 85)),
		recrtangleGame5(Vector2f(window.getSize().x - 420, (window.getSize().y - 130) / 2 - 85)),
		rectanglePlay1(Vector2f(window.getSize().x - 200, window.getSize().y - 200)), rectanglePlay2(Vector2f(window.getSize().x - 210, window.getSize().y - 210)),
		rectangleCheck1(Vector2f(400, 200)), rectangleCheck2(Vector2f(390, 190)),
		rectangleHint1(Vector2f(120, 50)), rectangleHint2(Vector2f(110, 40)),

		rectanglePlayBox1(Vector2f(window.getSize().x / 2 - 10, 50)), rectanglePlayBox11(Vector2f(window.getSize().x / 2 - 20, 40)),
		rectanglePlayBox2(Vector2f(window.getSize().x / 2 - 10, 50)), rectanglePlayBox21(Vector2f(window.getSize().x / 2 - 20, 40)),
		rectanglePlayBox3(Vector2f(window.getSize().x / 2 - 10, 50)), rectanglePlayBox31(Vector2f(window.getSize().x / 2 - 20, 40)),

		rectanglePlayBox9(Vector2f(window.getSize().x / 2 - 10, 50)), rectanglePlayBox91(Vector2f(window.getSize().x / 2 - 20, 40)),
		rectanglePlayBox10(Vector2f(window.getSize().x / 2 - 10, 50)), rectanglePlayBox101(Vector2f(window.getSize().x / 2 - 20, 40)),

		rectanglePlayBox4(Vector2f(120, 50)), rectanglePlayBox41(Vector2f(110, 40)),
		rectanglePlayBox5(Vector2f(120, 50)), rectanglePlayBox51(Vector2f(110, 40)),
		rectanglePlayBox6(Vector2f(120, 50)), rectanglePlayBox61(Vector2f(110, 40)),
		rectanglePlayBox7(Vector2f(120, 50)), rectanglePlayBox71(Vector2f(110, 40)),
		rectanglePlayBox8(Vector2f(120, 50)), rectanglePlayBox81(Vector2f(110, 40));
	rectangleScroll1.setFillColor(Color(207, 159, 119));
	rectanglePlayBox1.setFillColor(Color::Black);
	rectanglePlayBox1.setPosition(120, 170);

	rectanglePlayBox11.setFillColor(Color::White);
	rectanglePlayBox11.setPosition(125, 175);

	rectanglePlayBox2.setFillColor(Color::Black);
	rectanglePlayBox2.setPosition(120, 275);

	rectanglePlayBox21.setFillColor(Color::White);
	rectanglePlayBox21.setPosition(125, 280);

	rectanglePlayBox3.setFillColor(Color::Black);
	rectanglePlayBox3.setPosition(120, 380);

	rectanglePlayBox31.setFillColor(Color::White);
	rectanglePlayBox31.setPosition(125, 385);



	rectanglePlayBox9.setFillColor(Color::Black);
	rectanglePlayBox9.setPosition(120, 485);

	rectanglePlayBox91.setFillColor(Color::White);
	rectanglePlayBox91.setPosition(125, 490);

	rectanglePlayBox10.setFillColor(Color::Black);
	rectanglePlayBox10.setPosition(120, 590);

	rectanglePlayBox101.setFillColor(Color::White);
	rectanglePlayBox101.setPosition(125, 595);

	rectanglePlayBox4.setFillColor(Color::Black);
	rectanglePlayBox4.setPosition(210 + window.getSize().x / 2, 170);

	rectanglePlayBox41.setFillColor(Color::White);
	rectanglePlayBox41.setPosition(215 + window.getSize().x / 2, 175);

	rectanglePlayBox5.setFillColor(Color::Black);
	rectanglePlayBox5.setPosition(210 + window.getSize().x / 2, 275);

	rectanglePlayBox51.setFillColor(Color::White);
	rectanglePlayBox51.setPosition(215 + window.getSize().x / 2, 280);

	rectanglePlayBox6.setFillColor(Color::Black);
	rectanglePlayBox6.setPosition(210 + window.getSize().x / 2, 380);

	rectanglePlayBox61.setFillColor(Color::White);
	rectanglePlayBox61.setPosition(215 + window.getSize().x / 2, 385);

	rectanglePlayBox7.setFillColor(Color::Black);
	rectanglePlayBox7.setPosition(210 + window.getSize().x / 2, 490);

	rectanglePlayBox71.setFillColor(Color::White);
	rectanglePlayBox71.setPosition(215 + window.getSize().x / 2, 495);

	rectanglePlayBox8.setFillColor(Color::Black);
	rectanglePlayBox8.setPosition(210 + window.getSize().x / 2, 595);

	rectanglePlayBox81.setFillColor(Color::White);
	rectanglePlayBox81.setPosition(215 + window.getSize().x / 2, 600);

	rectangleHint1.setFillColor(Color::Black);
	rectangleHint1.setPosition(window.getSize().x - 220, 40);

	rectangleHint2.setFillColor(Color::White);
	rectangleHint2.setPosition(window.getSize().x - 215, 45);

	rectangleCheck1.setFillColor(Color::Black);
	rectangleCheck1.setPosition(window.getSize().x / 2 - 200, window.getSize().y / 2 - 100);

	rectangleCheck2.setFillColor(Color::White);
	rectangleCheck2.setPosition(window.getSize().x / 2 - 195, window.getSize().y / 2 - 95);

	rectanglePlay1.setFillColor(Color::Red);
	rectanglePlay1.setPosition(100, 100);

	rectanglePlay2.setFillColor(Color::Blue);
	rectanglePlay2.setPosition(105, 105);

	recrtangleGame1.setFillColor(Color::Red);
	recrtangleGame1.setPosition(200, 50);

	recrtangleGame2.setFillColor(Color::Blue);
	recrtangleGame2.setPosition(205, 55);

	recrtangleGame3.setFillColor(Color::Blue);
	recrtangleGame3.setPosition(205, (window.getSize().y - 120) / 2 + 65);

	recrtangleGame4.setFillColor(Color::White);
	recrtangleGame4.setPosition(210, 140);

	recrtangleGame5.setFillColor(Color::White);
	recrtangleGame5.setPosition(210, 490);


	recrtangleAboutUs1.setFillColor(Color(225, 172, 119));
	recrtangleAboutUs1.setPosition(50, 50);

	recrtangleAboutUs2.setFillColor(Color(249, 239, 239));
	recrtangleAboutUs2.setPosition(55, 55);

	recrtangleAboutUs3.setFillColor(Color(225, 172, 119));
	recrtangleAboutUs3.setPosition(130, window.getSize().y - window.getSize().y / 4 - 20);

	recrtangleAboutUs4.setFillColor(Color(249, 239, 239));
	recrtangleAboutUs4.setPosition(135, window.getSize().y - window.getSize().y / 4 - 15);

	recrtangleAboutUs5.setFillColor(Color(225, 172, 119));
	recrtangleAboutUs5.setPosition(70, 70);

	recrtangleAboutUs6.setFillColor(Color(225, 172, 119));
	recrtangleAboutUs6.setPosition(288, 70);

	recrtangleAboutUs7.setFillColor(Color(225, 172, 119));
	recrtangleAboutUs7.setPosition(506, 70);

	recrtangleAboutUs8.setFillColor(Color(225, 172, 119));
	recrtangleAboutUs8.setPosition(724, 70);

	recrtangleAboutUsH1.setFillColor(Color::Color(249, 239, 239));
	recrtangleAboutUsH1.setPosition(175 - recrtangleAboutUsH1.getSize().x / 2, window.getSize().y / 2 - 50);

	recrtangleAboutUsS1.setFillColor(Color::Color(249, 239, 239));
	recrtangleAboutUsS1.setPosition(393 - recrtangleAboutUsS1.getSize().x / 2, window.getSize().y / 2 - 50);

	recrtangleAboutUsG1.setFillColor(Color::Color(249, 239, 239));
	recrtangleAboutUsG1.setPosition(611 - recrtangleAboutUsG1.getSize().x / 2, window.getSize().y / 2 - 50);

	recrtangleAboutUsM1.setFillColor(Color::Color(249, 239, 239));
	recrtangleAboutUsM1.setPosition(829 - recrtangleAboutUsM1.getSize().x / 2, window.getSize().y / 2 - 50);

	recrtangleAboutUsH2.setFillColor(Color::Color(249, 239, 239));
	recrtangleAboutUsH2.setPosition(175 - recrtangleAboutUsH2.getSize().x / 2, window.getSize().y / 2 - 100);

	recrtangleAboutUsS2.setFillColor(Color::Color(249, 239, 239));
	recrtangleAboutUsS2.setPosition(393 - recrtangleAboutUsS2.getSize().x / 2, window.getSize().y / 2 - 100);

	recrtangleAboutUsG2.setFillColor(Color::Color(249, 239, 239));
	recrtangleAboutUsG2.setPosition(611 - recrtangleAboutUsG2.getSize().x / 2, window.getSize().y / 2 - 100);

	recrtangleAboutUsM2.setFillColor(Color::Color(249, 239, 239));
	recrtangleAboutUsM2.setPosition(829 - recrtangleAboutUsM2.getSize().x / 2, window.getSize().y / 2 - 100);


	rectangleMiddle1.setFillColor(Color(225, 172, 119));
	rectangleMiddle1.setPosition(window.getSize().x / 2 - 125, window.getSize().y / 2 + 120);

	rectangleMiddle2.setFillColor(Color(249, 239, 239));
	rectangleMiddle2.setPosition(window.getSize().x / 2 - 120, window.getSize().y / 2 + 125);


	rectangleDDASSA1.setFillColor(Color::Color(234, 222, 215));
	rectangleDDASSA1.setPosition(window.getSize().x / 2 - window.getSize().x / 6 + 5, window.getSize().y / 2 - window.getSize().y / 8 + 5);
	rectangleDDASSA.setFillColor(Color::Color(216, 183, 171));
	rectangleDDASSA.setPosition(window.getSize().x / 2 - window.getSize().x / 6, window.getSize().y / 2 - window.getSize().y / 8);

	rectangleScroll.setPosition(window.getSize().x - 350, 35);
	rectangleScroll.setFillColor(Color(207, 159, 119));

	//rectangleMoreInfo.setFillColor(Color::Red);
	rectangleMoreInfo.setPosition(window.getSize().x - 310, window.getSize().y - 410);

	rectangleMoreInf.setFillColor(Color(249, 239, 239));
	rectangleMoreInf.setPosition(window.getSize().x - 305, window.getSize().y - 405);

	rectangleDDASSAMini1.setFillColor(Color::Color(188, 145, 118));
	rectangleDDASSAMini1.setPosition(window.getSize().x / 2 - 90, window.getSize().y / 2 + 30);

	rectangleDDASSAMini2.setFillColor(Color::Color(150, 103, 74));
	rectangleDDASSAMini2.setPosition(window.getSize().x / 2 + 90, window.getSize().y / 2 + 30);


	setRectangleEventsTab(&rectangle, 50, 50);
	setRectangleEventsTab(&rectangle2, 370, 520);
	setRectangleEventsTab(&rectangle3, 590, 520);
	setRectangleEventsTab(&rectangle4, 810, 520);

	//rectangle5.setFillColor(Color::Color(211, 141, 74)); // ogradata na v nego sa subitatqtq
	rectangle5.setPosition(23, 23);

	rectangle10.setFillColor(Color(249, 239, 239)); // v nego sa subitiqta ggggggggggggggggggggg
	rectangle10.setPosition(28, 28);

	rectangle11.setFillColor(Color::Color(225, 172, 119)); // tabovete sus subitiqtaaaa
	rectangle11.setPosition(35, 35);

	setRectangleCreateMainOne(&rectangle12, 40, 1);
	setRectangleCreateMainOne(&rectangle13, 45, 2);
	setRectangleCreateMainOne(&rectangle14, 50, 3);
	setRectangleCreateMainOne(&rectangle15, 55, 4);
	setRectangleCreateMainOne(&rectangle16, 60, 5);
	setRectangleCreateMainOne(&rectangle17, 65, 6);
	rectangle12.setFillColor(Color::Color(225, 172, 119)); // tabovete sus subitiqtaaaa
	rectangle13.setFillColor(Color::Color(225, 172, 119)); // tabovete sus subitiqtaaaa
	rectangle14.setFillColor(Color::Color(225, 172, 119)); // tabovete sus subitiqtaaaa
	rectangle15.setFillColor(Color::Color(225, 172, 119)); // tabovete sus subitiqtaaaa
	rectangle16.setFillColor(Color::Color(225, 172, 119)); // tabovete sus subitiqtaaaa
	rectangle17.setFillColor(Color::Color(225, 172, 119)); // tabovete sus subitiqtaaaa


	rectangle7.setFillColor(Color::Color(207, 159, 119)); // choose one
	rectangle7.setPosition(window.getSize().x - 310, 25);
	setRectangleDropDown(&rectangle8, 65);
	setRectangleDropDown(&rectangle9, 105);
	setRectangleDropDown(&rectangle22, 145);
	setRectangleDropDown(&rectangle23, 185);
	setRectangleDropDown(&rectangle24, 225);
	setRectangleDropDown(&rectangle25, 265);
	setRectangleDropDown(&rectangle26, 305);
	setRectangleDropDown(&rectangle27, 345);


	rectangle8.setFillColor(Color::Color(147, 87, 57));
	rectangle9.setFillColor(Color::Color(147, 87, 57));
	rectangle22.setFillColor(Color::Color(147, 87, 57));


	//Cray rectangles Create 
	addFromOrBack(&rectangle28, 60); // ogradite vutre v add more taba
	addFromOrBack(&rectangle29, 160);
	addFromOrBack(&rectangle30, 260);
	addFromOrBack(&rectangle31, 360);
	addFromOrBack(&rectangle32, 460);
	addFromOrBack(&rectangle33, 560);
	addFromOrBack(&rectangle42, 660);


	addFromOrBack(&rectangle44, 50);
	addFromOrBack(&rectangle45, window.getSize().y / 2 + 120);
	//rectangle46.setFillColor(Color::Color(249, 239, 239));
	rectangle46.setPosition((window.getSize().x - 160) / 2 + 30, window.getSize().y / 2 + 120);

	//rectangle47.setFillColor(Color::Color(249, 239, 239));
	rectangle47.setPosition(window.getSize().x / 2 + 220, window.getSize().y / 12 + 65);

	//rectangle53.setFillColor(Color::Color(249, 239, 239));
	rectangle53.setPosition(60, 60);

	//rectangle54.setFillColor(Color::Color(249, 239, 239));
	rectangle54.setPosition(window.getSize().x / 2 - 55, window.getSize().y / 2 + 125);


	//rectangle55.setFillColor(Color::Color(249, 239, 239));
	rectangle55.setPosition(window.getSize().x - 90, window.getSize().y / 2 + 125);

	addFromOrBackTwo(&rectangle48, 125);
	addFromOrBackTwo(&rectangle49, window.getSize().y / 2 + 125);
	rectangle50.setFillColor(Color::Color(249, 239, 239));
	rectangle50.setPosition((window.getSize().x - 160) / 2 + 35, window.getSize().y / 2 + 125);

	rectangle51.setFillColor(Color::Color(249, 239, 239));
	rectangle51.setPosition(window.getSize().x / 2 + 225, window.getSize().y / 12 + 70);

	rectangle52.setFillColor(Color::Color(249, 239, 239));
	rectangle52.setPosition(55, 55);


	recrtangleSearch2.setFillColor(Color(249, 239, 239));
	recrtangleSearch2.setPosition(window.getSize().x / 2 + 225, 55);

	//recrtangleSearch1.setFillColor(Color::Color(170, 170, 170, 255));
	recrtangleSearch1.setPosition(window.getSize().x / 2 + 220, 50);

	//White rectangles Create 
	addFromOrBackTwo(&rectangle34, 65);
	addFromOrBackTwo(&rectangle35, 165);
	addFromOrBackTwo(&rectangle36, 265);
	addFromOrBackTwo(&rectangle37, 365);
	addFromOrBackTwo(&rectangle38, 465);
	addFromOrBackTwo(&rectangle39, 565);
	addFromOrBackTwo(&rectangle43, 665);

	//Description rectangles

	rectangle40.setFillColor(Color::Color(249, 239, 239));
	rectangle40.setPosition(window.getSize().x / 2 + 90, 65);

	//rectangle41.setFillColor(Color::Color(249, 239, 239));
	rectangle41.setPosition(window.getSize().x / 2 + 85, 60);

	s1.setTextureRect(IntRect(10, 10, 486, 500));
	s2.setTextureRect(IntRect(10, 10, 1300, 1300));
	s3.setTextureRect(IntRect(0, 0, 50, 50));
	s4.setTextureRect(IntRect(0, 0, 50, 50));
	s5.setTextureRect(IntRect(0, 0, 50, 50));
	s6.setTextureRect(IntRect(0, 0, 50, 50));
	s7.setTextureRect(IntRect(0, 0, 50, 50));
	s8.setTextureRect(IntRect(0, 0, 30, 50));
	s9.setTextureRect(IntRect(0, 0, 30, 50));
	s10.setTextureRect(IntRect(0, 0, 15, 15));
	s11.setTextureRect(IntRect(0, 0, 15, 15));

	s1.setPosition(window.getSize().x / 2 - tex1.getSize().x / 2, 0);
	s3.setPosition(window.getSize().x - 100, 55);
	s4.setPosition(window.getSize().x - 95, window.getSize().y - 270);
	s5.setPosition(window.getSize().x / 2 - 60, window.getSize().y - 270);
	s6.setPosition(window.getSize().x - 95, window.getSize().y - 90);
	s7.setPosition(window.getSize().x / 2 - 60, window.getSize().y - 90);
	s8.setPosition(window.getSize().x - 358, 35);
	s9.setPosition(window.getSize().x - 358, window.getSize().y - 60);
	s10.setPosition(window.getSize().x - 70, window.getSize().y - 270);
	s11.setPosition(window.getSize().x - 70, window.getSize().y - 55);
	int sort = 0;
	int p1 = 0;

	RectangleShape Hello[7] = { rectangle11,
		rectangle12, rectangle13, rectangle14,
		rectangle15, rectangle16, rectangle17 };

	rectangleEvent1.setPosition((window.getSize().x - 160) / 2 + 45, 535);
	rectangleEvent2.setPosition((window.getSize().x - 160) / 2 + 45, 590);
	rectangleEvent3.setPosition((window.getSize().x - 160) / 2 + 45, 645);
	rectangleEvent4.setPosition((window.getSize().x - 160) / 2 + 45, 700);

	rectangleEvent1.setFillColor(Color(225, 172, 119));
	rectangleEvent2.setFillColor(Color(225, 172, 119));
	rectangleEvent3.setFillColor(Color(225, 172, 119));
	rectangleEvent4.setFillColor(Color(225, 172, 119));

	RectangleShape Events[4] = { rectangleEvent1,
		rectangleEvent2, rectangleEvent3, rectangleEvent4 };

	Text hText1, hText2, hText3, hText4, hText5, hText6, hText7;
	Text textRandom1, textRandom2, textRandom3, textRandom4, textRandom5;
	Text infoText1, infoText2, infoText3, infoText4, infoText5, infoText6, infoText7;
	Text h[7] = { hText1, hText2, hText3, hText4, hText5, hText6, hText7 };
	Text random[5] = { textRandom1, textRandom2, textRandom3, textRandom4, textRandom5 };
	Text info[7] = { infoText1, infoText2, infoText3, infoText4, infoText5, infoText6, infoText7 };
	Text info2[7] = { infoText1, infoText2, infoText3, infoText4, infoText5, infoText6, infoText7 };
	Text info3[7] = { infoText1, infoText2, infoText3, infoText4, infoText5, infoText6, infoText7 };
	Text info4[7] = { infoText1, infoText2, infoText3, infoText4, infoText5, infoText6, infoText7 };
	Text error, areYouSure, choicePositionOfEvent, yes, no, position, errorPos, edit, deleteOne;
	bool errorHere = false, errPos = false;
	error.setString("You cannot complete the event while the fields are empty");
	error.setPosition(180, 740);
	error.setFillColor(Color(255, 102, 105));
	error.setFont(f2);
	error.setCharacterSize(18);

	areYouSure.setString("Are you sure?");
	areYouSure.setPosition(480, 350);
	areYouSure.setFillColor(Color(188, 145, 118));
	areYouSure.setFont(f2);
	areYouSure.setCharacterSize(18);

	choicePositionOfEvent.setString("Choice position of event");
	choicePositionOfEvent.setPosition(417, 340);
	choicePositionOfEvent.setFillColor(Color(188, 145, 118));
	choicePositionOfEvent.setFont(f2);
	choicePositionOfEvent.setCharacterSize(18);

	yes.setString("Continue");
	yes.setPosition(424, 439);
	//yes.setFillColor(Color(188, 145, 118));
	yes.setFont(f2);
	yes.setCharacterSize(15);

	no.setString("Cancel");
	no.setPosition(614, 439);
	//no.setFillColor(Color(188, 145, 118));
	no.setFont(f2);
	no.setCharacterSize(15);

	position.setString("Position:");
	position.setPosition(300, 125);
	position.setFillColor(Color::Black);
	position.setFont(f1);
	position.setCharacterSize(25);

	edit.setString("You don't have any events, to edit them");
	edit.setPosition(355, 390);
	edit.setFillColor(Color(188, 145, 118));
	edit.setFont(f2);
	edit.setCharacterSize(17);

	deleteOne.setString("You don't have any events, to delete them");
	deleteOne.setPosition(345, 390);
	deleteOne.setFillColor(Color(188, 145, 118));
	deleteOne.setFont(f2);
	deleteOne.setCharacterSize(17);

	errorPos.setString("There is no such position");
	errorPos.setPosition(340, 740);
	errorPos.setFillColor(Color(255, 102, 105));
	errorPos.setFont(f2);
	errorPos.setCharacterSize(18);

	Node* myEvents = NULL;
	Node* temp;
	savedNodes(&myEvents);
	int stopper = 7;
	int p2 = 0;
	while (window.isOpen())
	{
		Event event;

		int mouseX = sf::Mouse::getPosition(window).x;
		int mouseY = sf::Mouse::getPosition(window).y;

		if (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		window.clear(Color(235, 222, 214));
		if (location == 0)
		{
			window.draw(s2);
			window.draw(s1);
			window.draw(text1);
			window.draw(text2);
			window.draw(text3);
			window.draw(text4);
			window.draw(text5);

			textPosition(&location, event, &text1, 1, 500, 545);
			textPosition(&location, event, &text2, 2, 550, 590);
			textPosition(&location, event, &text3, 3, 600, 640);
			textPosition(&location, event, &text4, 4, 650, 690);
			textPosition(&location, event, &text5, 5, 700, 740);


		}
		else
		{
			window.clear(Color(235, 222, 214));
			switch (location)
			{
			case 1:

				temp = myEvents;
				rectangles = 0;
				while (temp)
				{
					titleAndYear[rectangles] = to_string(rectangles + 1) + "." + temp->title + " - " + to_string(temp->year);

					string t = temp->title;
					string p = temp->participants;
					string e = temp->era;
					string l = temp->location;
					string rea = temp->reason;
					string res = temp->result;
					string d = temp->description;

					if (p.size() > 20) {
						p.insert(20, "\n");
					}

					if (e.size() > 20) {
						e.insert(20, "\n");
					}

					if (l.size() > 20) {
						l.insert(20, "\n             ");
					}

					if (rea.size() > 20) {
						rea.insert(20, "\n");
					}

					if (res.size() > 20) {
						res.insert(20, "\n");
					}


					while (d.size() > 46 * dHelp) {
						d.insert(46 * dHelp, "\n\n");
						dHelp++;
					}

					dHelp = 1;

					allInfo[rectangles] =
						"               More Information\n\n"
						"Participants: \n" + p + "\n\n"
						+ "Era: \n" + e + "\n\n"
						+ "             Location: \n             " + l + "\n\n";

					allInfo2[rectangles] =
						"\n\nReason: \n" + rea + "\n\n"
						+ "Result: \n" + res + "\n";

					allInfo3[rectangles] = t;

					allInfo4[rectangles] = d;

					if (p2 <= 0) {
						if (rectangles < 4) {
							info[rectangles].setString(allInfo[rectangles]);
							info[rectangles].setFont(f2);
							info[rectangles].setCharacterSize(13);
							info[rectangles].setFillColor(Color(188, 145, 118));
							info[rectangles].setPosition(65, 530);
							info2[rectangles].setString(allInfo2[rectangles]);
							info2[rectangles].setFont(f2);
							info2[rectangles].setCharacterSize(13);
							info2[rectangles].setFillColor(Color(188, 145, 118));
							info2[rectangles].setPosition(260, 530);
							info3[rectangles].setString(allInfo3[rectangles]);
							info3[rectangles].setFont(f2);
							info3[rectangles].setCharacterSize(25);
							info3[rectangles].setFillColor(Color(188, 145, 118));
							info3[rectangles].setPosition(75, 75);
							info4[rectangles].setString(allInfo4[rectangles]);
							info4[rectangles].setFont(f2);
							info4[rectangles].setCharacterSize(20);
							info4[rectangles].setFillColor(Color(188, 145, 118));
							info4[rectangles].setPosition(100, 155);
							h[rectangles].setString(titleAndYear[rectangles]);
							h[rectangles].setFont(f2);
							h[rectangles].setCharacterSize(15);
							h[rectangles].setFillColor(Color(254, 254, 254));
							h[rectangles].setPosition(490, 548 + rectangles * 55);
						}
					}
					else {
						int oldRectangles = 0;
						while (oldRectangles != 4) {
							info[oldRectangles].setString(allInfo[oldRectangles + p2]);
							info[oldRectangles].setFont(f2);
							info[oldRectangles].setCharacterSize(13);
							info[oldRectangles].setFillColor(Color(188, 145, 118));
							info[oldRectangles].setPosition(65, 530);
							info2[oldRectangles].setString(allInfo2[oldRectangles + p2]);
							info2[oldRectangles].setFont(f2);
							info2[oldRectangles].setCharacterSize(13);
							info2[oldRectangles].setFillColor(Color(188, 145, 118));
							info2[oldRectangles].setPosition(260, 530);
							info3[oldRectangles].setString(allInfo3[oldRectangles + p2]);
							info3[oldRectangles].setFont(f2);
							info3[oldRectangles].setCharacterSize(25);
							info3[oldRectangles].setFillColor(Color(188, 145, 118));
							info3[oldRectangles].setPosition(75, 75);
							info4[oldRectangles].setString(allInfo4[oldRectangles + p2]);
							info4[oldRectangles].setFont(f2);
							info4[oldRectangles].setCharacterSize(20);
							info4[oldRectangles].setFillColor(Color(188, 145, 118));
							info4[oldRectangles].setPosition(100, 155);
							h[oldRectangles].setString(titleAndYear[oldRectangles + p2]);
							h[oldRectangles].setFont(f2);
							h[oldRectangles].setCharacterSize(15);
							h[oldRectangles].setFillColor(Color(254, 254, 254));
							h[oldRectangles].setPosition(490, 548 + oldRectangles * 55);
							++oldRectangles;
						}
					}
					++rectangles;
					temp = temp->next;
				}

				if (autoSave == "") {
					fstream data;
					data.open("AutoSaveNodes.txt", ios::in);
					if (data.is_open()) {
						string tp;
						while (getline(data, tp)) {
							autoSave = tp;
						}
					}

					data.close();
				}
				autoSaveNodes(&myEvents, autoSave);

				backToMenu(&location, event, &text6);

				window.draw(rectangle44);
				window.draw(rectangle45);
				window.draw(rectangle46);
				window.draw(rectangle47);
				window.draw(recrtangleSearch1);
				window.draw(recrtangleSearch2);


				window.draw(rectangle48);
				window.draw(rectangle49);
				window.draw(rectangle50);
				window.draw(rectangle51);
				window.draw(rectangle52);
				window.draw(rectangle53);

				//window.draw(rectangle54);
				//window.draw(rectangle55);

				window.draw(text6);
				window.draw(s3);
				//window.draw(s4);
				//window.draw(s6);

				//window.draw(s5);
				//window.draw(s7);
				cout << "p2 = " << p2 << endl;
				if (rectangles > 4)
				{
					if (p2 > 0 && p2 <= rectangles - 4)
					{
						if (Mouse::getPosition(window).x > window.getSize().x - 70 && Mouse::getPosition(window).x < window.getSize().x - 55 &&
							Mouse::getPosition(window).y> window.getSize().y - 270 && Mouse::getPosition(window).y < window.getSize().y - 255)
						{
							switch (event.type)
							{
							case Event::MouseButtonPressed:
								if (event.mouseButton.button == Mouse::Left)
								{
									p2--;

									Mouse::setPosition(Vector2i(Mouse::getPosition(window).x + 6, Mouse::getPosition(window).y + 6), window);
								}
							}
						}
					}
					if (p2 >= 0 && p2 < rectangles - 4)
					{
						if (Mouse::getPosition(window).x > window.getSize().x - 70 && Mouse::getPosition(window).x < window.getSize().x - 55 &&
							Mouse::getPosition(window).y>window.getSize().y - 55 && Mouse::getPosition(window).y < window.getSize().y - 40)
						{
							if (event.type == Event::MouseButtonPressed)
							{
								if (event.mouseButton.button == Mouse::Left)
								{
									p2++;
									Mouse::setPosition(Vector2i(Mouse::getPosition(window).x - 4, Mouse::getPosition(window).y - 4), window);
								}
							}
						}
					}
					rectangleScroll1.setSize(Vector2f(window.getSize().x / 66, 4 * (window.getSize().y / 2 - 210) / rectangles));
					rectangleScroll1.setPosition(window.getSize().x - 70, window.getSize().y - 255 + p2 * (window.getSize().y / 2 - 210) / rectangles);
					window.draw(s10);
					window.draw(s11);
					window.draw(rectangleScroll1);
				}
				else
				{
					rectangleScroll1.setSize(Vector2f(window.getSize().x / 66, window.getSize().y / 2 - 210));
					rectangleScroll1.setPosition(window.getSize().x - 70, window.getSize().y - 255);
					window.draw(rectangleScroll1);
				}

				if (rectangles <= 4) {
					for (int i = 0; i < rectangles; i++)
					{
						window.draw(Events[i]);
					}
					for (int i = 0; i < rectangles; i++)
					{
						window.draw(h[i]);
					}
				}
				else {
					for (int i = 0; i < 4; i++)
					{
						window.draw(Events[i]);
					}
					for (int i = 0; i < 4; i++)
					{
						window.draw(h[i]);
					}
				}

				if (Mouse::getPosition(window).x > 485 && Mouse::getPosition(window).x < 935 &&
					Mouse::getPosition(window).y>535 && Mouse::getPosition(window).y < 580) {
					if (event.type == Event::MouseButtonPressed)
					{
						if (event.mouseButton.button == Mouse::Left)
						{
							infoChoice = 1;
						}
					}
				}
				if (Mouse::getPosition(window).x > 485 && Mouse::getPosition(window).x < 935 &&
					Mouse::getPosition(window).y>590 && Mouse::getPosition(window).y < 635) {
					if (event.type == Event::MouseButtonPressed)
					{
						if (event.mouseButton.button == Mouse::Left)
						{
							infoChoice = 2;
						}
					}
				}
				if (Mouse::getPosition(window).x > 485 && Mouse::getPosition(window).x < 935 &&
					Mouse::getPosition(window).y>645 && Mouse::getPosition(window).y < 690) {
					if (event.type == Event::MouseButtonPressed)
					{
						if (event.mouseButton.button == Mouse::Left)
						{
							infoChoice = 3;
						}
					}
				}
				if (Mouse::getPosition(window).x > 485 && Mouse::getPosition(window).x < 935 &&
					Mouse::getPosition(window).y>700 && Mouse::getPosition(window).y < 745) {
					if (event.type == Event::MouseButtonPressed)
					{
						if (event.mouseButton.button == Mouse::Left)
						{
							infoChoice = 4;
						}
					}
				}

				if (rectangles != 0) {
					switch (infoChoice) {
					case 1:
						window.draw(info[0]);
						window.draw(info2[0]);
						window.draw(info3[0]);
						window.draw(info4[0]);
						break;
					case 2:
						window.draw(info[1]);
						window.draw(info2[1]);
						window.draw(info3[1]);
						window.draw(info4[1]);
						break;
					case 3:
						window.draw(info[2]);
						window.draw(info2[2]);
						window.draw(info3[2]);
						window.draw(info4[2]);
						break;
					case 4:
						window.draw(info[3]);
						window.draw(info2[3]);
						window.draw(info3[3]);
						window.draw(info4[3]);
						break;
					}
				}
				break;

				/*
				if (rectangles > 4)
				{
					if (p1 > 0 && p1 <= rectangles - 4)
					{
						if (Mouse::getPosition(window).x > window.getSize().x - 358 && Mouse::getPosition(window).x < window.getSize().x - 338 &&
							Mouse::getPosition(window).y>45 && Mouse::getPosition(window).y < 55)
						{
							switch (event.type)
							{
							case Event::MouseButtonPressed:
								if (event.mouseButton.button == Mouse::Left)
								{
									p1--;

									Mouse::setPosition(Vector2i(Mouse::getPosition(window).x + 6, Mouse::getPosition(window).y + 6), window);
								}
							}
						}
					}
					if (p1 >= 0 && p1 < rectangles - 4)
					{
						if (Mouse::getPosition(window).x > window.getSize().x - 358 && Mouse::getPosition(window).x < window.getSize().x - 338 &&
							Mouse::getPosition(window).y>window.getSize().y - 50 && Mouse::getPosition(window).y < window.getSize().y - 35)
						{
							if (event.type == Event::MouseButtonPressed)
							{
								if (event.mouseButton.button == Mouse::Left)
								{
									p1++;
									Mouse::setPosition(Vector2i(Mouse::getPosition(window).x - 4, Mouse::getPosition(window).y - 4), window);
								}
							}
						}
					}
					rectangleScroll.setSize(Vector2f(window.getSize().x / 66, 7 * (window.getSize().y - 130) / rectangles));
					rectangleScroll.setPosition(window.getSize().x - 350, 65 + p1 * (window.getSize().y - 130) / rectangles);
					window.draw(s8);
					window.draw(s9);
					window.draw(rectangleScroll);
				}
				else
				{
					rectangleScroll.setSize(Vector2f(window.getSize().x / 66, window.getSize().y - 130));
					rectangleScroll.setPosition(window.getSize().x - 350, 65);
					window.draw(rectangleScroll);
				}
				*/
			case 2:

				temp = myEvents;
				rectangles = 0;
				while (temp)
				{
					titleAndYear[rectangles] = to_string(rectangles + 1) + "." + temp->title + " - " + to_string(temp->year);
					//cout << "more: " <<titleAndYear[rectangles] << endl;

					string p = temp->participants;
					string e = temp->era;
					string l = temp->location;
					string rea = temp->reason;
					string res = temp->result;

					if (p.size() > 24) {
						p.insert(24, "\n");
					}

					if (e.size() > 24) {
						e.insert(24, "\n");
					}

					if (l.size() > 24) {
						l.insert(24, "\n");
					}

					if (rea.size() > 24) {
						rea.insert(24, "\n");
					}

					if (res.size() > 24) {
						res.insert(24, "\n");
					}

					allInfo[rectangles] =
						"      More Information\n\n"
						"Participants: \n" + p + "\n\n"
						+ "Era: \n" + e + "\n\n"
						+ "Location: \n" + l + "\n\n"
						+ "Reason: \n" + rea + "\n\n"
						+ "Result: \n" + res + "\n";
					if (p1 <= 0) {
						if (rectangles < stopper) {
							info[rectangles].setString(allInfo[rectangles]);
							info[rectangles].setFont(f2);
							info[rectangles].setCharacterSize(15);
							info[rectangles].setFillColor(Color(188, 145, 118));
							info[rectangles].setPosition(720, 405);
							h[rectangles].setString(titleAndYear[rectangles]);
							h[rectangles].setFont(f2);
							h[rectangles].setCharacterSize(20);
							h[rectangles].setFillColor(Color(254, 254, 254));
							h[rectangles].setPosition(50, 70 + rectangles * 105);
						}
					}
					else {
						int oldRectangles = 0;
						while (oldRectangles != stopper) {
							info[oldRectangles].setString(allInfo[oldRectangles + p1]);
							info[oldRectangles].setFont(f2);
							info[oldRectangles].setCharacterSize(15);
							info[oldRectangles].setFillColor(Color(188, 145, 118));
							info[oldRectangles].setPosition(720, 405);
							h[oldRectangles].setString(titleAndYear[oldRectangles + p1]);
							h[oldRectangles].setFont(f2);
							h[oldRectangles].setCharacterSize(20);
							h[oldRectangles].setFillColor(Color(254, 254, 254));
							h[oldRectangles].setPosition(50, 70 + oldRectangles * 105);
							++oldRectangles;
						}
					}
					++rectangles;
					temp = temp->next;
				}

				if (autoSave == "") {
					fstream data;
					data.open("AutoSaveNodes.txt", ios::in);
					if (data.is_open()) {
						string tp;
						while (getline(data, tp)) {
							autoSave = tp;
						}
					}

					data.close();
				}
				autoSaveNodes(&myEvents, autoSave);

				switch (locCreate)
				{
				case 1: // add front
					text6.setPosition(30, window.getSize().y - 50);
					window.draw(text17);
					window.draw(text18);
					window.draw(text19);
					window.draw(text20);
					window.draw(text21);
					window.draw(text22);
					window.draw(text23);
					window.draw(text24);
					drowFrontBackOrEditTab(rectangle28, rectangle29, rectangle30, rectangle31, rectangle32, rectangle33, rectangle34, rectangle35, rectangle36, rectangle37, rectangle38, rectangle39, rectangle40, rectangle41, rectangle42, rectangle43);
					window.draw(text6);
					backToMenuFromCreate(&locCreate, event, &text6, &text10);

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
						switch (whoIsChoiced) {
						case 1: textBox1.setSelected(true); break;
						case 2: textBox2.setSelected(true); break;
						case 3: textBox3.setSelected(true); break;
						case 4: textBox4.setSelected(true); break;
						case 5: textBox5.setSelected(true); break;
						case 6: textBox6.setSelected(true); break;
						case 7: textBox7.setSelected(true); break;
						case 8:
							if (moreText <= 30) {
								textBox8.setSelected(true);
							}
							else if (moreText <= 60) {
								textBox81.setSelected(true);
							}
							else if (moreText <= 90) {
								textBox82.setSelected(true);
							}
							else if (moreText <= 120) {
								textBox83.setSelected(true);
							}
							else if (moreText <= 150) {
								textBox84.setSelected(true);
							}
							else if (moreText <= 180) {
								textBox85.setSelected(true);
							}
							else if (moreText <= 210) {
								textBox86.setSelected(true);
							}
							else if (moreText <= 240) {
								textBox87.setSelected(true);
							}
							else if (moreText <= 270) {
								textBox88.setSelected(true);
							}
							else if (moreText <= 300) {
								textBox89.setSelected(true);
							}

							break;
						}

					}

					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
						switch (whoIsChoiced) {
						case 1: textBox1.setSelected(false); break;
						case 2: textBox2.setSelected(false); break;
						case 3: textBox3.setSelected(false); break;
						case 4: textBox4.setSelected(false); break;
						case 5: textBox5.setSelected(false); break;
						case 6: textBox6.setSelected(false); break;
						case 7: textBox7.setSelected(false); break;
						case 8:
							if (moreText <= 30) {
								textBox8.setSelected(false);
							}
							else if (moreText <= 60) {
								textBox81.setSelected(false);
							}
							else if (moreText <= 90) {
								textBox82.setSelected(false);
							}
							else if (moreText <= 120) {
								textBox83.setSelected(false);
							}
							else if (moreText <= 150) {
								textBox84.setSelected(false);
							}
							else if (moreText <= 180) {
								textBox85.setSelected(false);
							}
							else if (moreText <= 210) {
								textBox86.setSelected(false);
							}
							else if (moreText <= 240) {
								textBox87.setSelected(false);
							}
							else if (moreText <= 270) {
								textBox88.setSelected(false);
							}
							else if (moreText <= 300) {
								textBox89.setSelected(false);
							}

							break;
						}
					}



					if (event.type == Event::MouseButtonPressed)
					{
						if (event.mouseButton.button == Mouse::Left)
						{
							if (mouseX > 55 && mouseX < 545)
							{
								if (mouseY > 65 && mouseY < 95)
									whoIsChoiced = 1;
								if (mouseY > 165 && mouseY < 195)
									whoIsChoiced = 2;
								if (mouseY > 265 && mouseY < 295)
									whoIsChoiced = 3;
								if (mouseY > 365 && mouseY < 395)
									whoIsChoiced = 4;
								if (mouseY > 465 && mouseY < 495)
									whoIsChoiced = 5;
								if (mouseY > 565 && mouseY < 595)
									whoIsChoiced = 6;
								if (mouseY > 665 && mouseY < 695)
									whoIsChoiced = 7;
							}

							if (mouseX > 590 && mouseX < 970)
								if (mouseY > 65 && mouseY < 695)
									whoIsChoiced = 8;
							if (btn1.isMouseOver(window)) {
								allText = textBox8.getText() + textBox81.getText() + textBox82.getText() + textBox83.getText() + textBox84.getText() + textBox85.getText() + textBox86.getText() + textBox87.getText() + textBox88.getText() + textBox89.getText();
								if (allText.size() > 0 &&
									(textBox1.getText()).size() > 0 &&
									(textBox2.getText()).size() > 0 &&
									(textBox3.getText()).size() > 0 &&
									(textBox4.getText()).size() > 0 &&
									(textBox5.getText()).size() > 0 &&
									(textBox6.getText()).size() > 0 &&
									(textBox7.getText()).size() > 0 &&
									(textBox8.getText()).size() > 0 &&
									textBox1.getText() != "_" &&
									textBox2.getText() != "_" &&
									textBox3.getText() != "_" &&
									textBox4.getText() != "_" &&
									textBox5.getText() != "_" &&
									textBox6.getText() != "_" &&
									textBox7.getText() != "_" &&
									allText != "_") {
									errorHere = false;
									setUpLink(myEvents, textBox9.getText(), textBox1.getText(), textBox2.getText(), textBox3.getText(), textBox4.getText(), textBox5.getText(), textBox6.getText(), textBox7.getText(), allText, 1);
									++EventsHave;
									textBox1.deleteAll();
									textBox2.deleteAll();
									textBox3.deleteAll();
									textBox4.deleteAll();
									textBox5.deleteAll();
									textBox6.deleteAll();
									textBox7.deleteAll();
									textBox8.deleteAll();
									textBox81.deleteAll();
									textBox82.deleteAll();
									textBox83.deleteAll();
									textBox84.deleteAll();
									textBox85.deleteAll();
									textBox86.deleteAll();
									textBox87.deleteAll();
									textBox88.deleteAll();
									textBox89.deleteAll();
									textBox9.deleteAll();
									finishToMenuFromCreate(&locCreate, event, &text10);
								}
								else {
									errorHere = true;
								}
							}
						}
					}
					while (window.pollEvent(event)) {

						if (event.type == sf::Event::TextEntered) {
							if ((event.text.unicode >= 65 && event.text.unicode <= 127) || (event.text.unicode >= 48 && event.text.unicode <= 57) || event.text.unicode == DELETE_KEY || event.text.unicode == 32) {
								switch (whoIsChoiced) {
								case 1: textBox1.typedOn(event); break;
								case 2:
									if ((event.text.unicode >= 48 && event.text.unicode <= 57) || event.text.unicode == DELETE_KEY)
										textBox2.typedOn(event); break;
								case 3: textBox3.typedOn(event); break;
								case 4: textBox4.typedOn(event); break;
								case 5: textBox5.typedOn(event); break;
								case 6: textBox6.typedOn(event); break;
								case 7: textBox7.typedOn(event); break;
								case 8:
									if (moreText < 31) {
										textBox8.typedOn(event);
									}
									else if (moreText < 61) {
										textBox81.typedOn(event);
									}
									else if (moreText < 91) {
										textBox82.typedOn(event);
									}
									else if (moreText < 121) {
										textBox83.typedOn(event);
									}
									else if (moreText < 151) {
										textBox84.typedOn(event);
									}
									else if (moreText < 181) {
										textBox85.typedOn(event);
									}
									else if (moreText < 211) {
										textBox86.typedOn(event);
									}
									else if (moreText < 241) {
										textBox87.typedOn(event);
									}
									else if (moreText < 271) {
										textBox88.typedOn(event);
									}
									else if (moreText < 301) {
										textBox89.typedOn(event);
									}
									if (event.text.unicode != DELETE_KEY)
										++moreText;
									else
										--moreText;
									break;
								}
							}
						}

						if (sf::Event::MouseMoved) {
							if (btn1.isMouseOver(window)) {
								btn1.hoverColorYes();
							}
							else {
								btn1.hoverColorNo();
							}
						}
					}
					textBox1.drawTo(window);
					textBox2.drawTo(window);
					textBox3.drawTo(window);
					textBox4.drawTo(window);
					textBox5.drawTo(window);
					textBox6.drawTo(window);
					textBox7.drawTo(window);
					textBox8.drawTo(window);
					textBox81.drawTo(window);
					textBox82.drawTo(window);
					textBox83.drawTo(window);
					textBox84.drawTo(window);
					textBox85.drawTo(window);
					textBox86.drawTo(window);
					textBox87.drawTo(window);
					textBox88.drawTo(window);
					textBox89.drawTo(window);
					if (errorHere)
						window.draw(error);
					btn1.drawTo(window);

					break;
				case 2: // add first
					text6.setPosition(30, window.getSize().y - 50);
					window.draw(text17);
					window.draw(text18);
					window.draw(text19);
					window.draw(text20);
					window.draw(text21);
					window.draw(text22);
					window.draw(text23);
					window.draw(text24);
					drowFrontBackOrEditTab(rectangle28, rectangle29, rectangle30, rectangle31, rectangle32, rectangle33, rectangle34, rectangle35, rectangle36, rectangle37, rectangle38, rectangle39, rectangle40, rectangle41, rectangle42, rectangle43);
					window.draw(text6);
					backToMenuFromCreate(&locCreate, event, &text6, &text10);

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
						switch (whoIsChoiced) {
						case 1: textBox1.setSelected(true); break;
						case 2: textBox2.setSelected(true); break;
						case 3: textBox3.setSelected(true); break;
						case 4: textBox4.setSelected(true); break;
						case 5: textBox5.setSelected(true); break;
						case 6: textBox6.setSelected(true); break;
						case 7: textBox7.setSelected(true); break;
						case 8:
							if (moreText <= 30) {
								textBox8.setSelected(true);
							}
							else if (moreText <= 60) {
								textBox81.setSelected(true);
							}
							else if (moreText <= 90) {
								textBox82.setSelected(true);
							}
							else if (moreText <= 120) {
								textBox83.setSelected(true);
							}
							else if (moreText <= 150) {
								textBox84.setSelected(true);
							}
							else if (moreText <= 180) {
								textBox85.setSelected(true);
							}
							else if (moreText <= 210) {
								textBox86.setSelected(true);
							}
							else if (moreText <= 240) {
								textBox87.setSelected(true);
							}
							else if (moreText <= 270) {
								textBox88.setSelected(true);
							}
							else if (moreText <= 300) {
								textBox89.setSelected(true);
							}

							break;
						}
					}

					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
						switch (whoIsChoiced) {
						case 1: textBox1.setSelected(false); break;
						case 2: textBox2.setSelected(false); break;
						case 3: textBox3.setSelected(false); break;
						case 4: textBox4.setSelected(false); break;
						case 5: textBox5.setSelected(false); break;
						case 6: textBox6.setSelected(false); break;
						case 7: textBox7.setSelected(false); break;
						case 8:
							if (moreText <= 30) {
								textBox8.setSelected(false);
							}
							else if (moreText <= 60) {
								textBox81.setSelected(false);
							}
							else if (moreText <= 90) {
								textBox82.setSelected(false);
							}
							else if (moreText <= 120) {
								textBox83.setSelected(false);
							}
							else if (moreText <= 150) {
								textBox84.setSelected(false);
							}
							else if (moreText <= 180) {
								textBox85.setSelected(false);
							}
							else if (moreText <= 210) {
								textBox86.setSelected(false);
							}
							else if (moreText <= 240) {
								textBox87.setSelected(false);
							}
							else if (moreText <= 270) {
								textBox88.setSelected(false);
							}
							else if (moreText <= 300) {
								textBox89.setSelected(false);
							}

							break;
						}
					}

					if (event.type == Event::MouseButtonPressed)
					{
						if (event.mouseButton.button == Mouse::Left)
						{
							if (mouseX > 55 && mouseX < 545)
							{
								if (mouseY > 65 && mouseY < 95)
									whoIsChoiced = 1;
								if (mouseY > 165 && mouseY < 195)
									whoIsChoiced = 2;
								if (mouseY > 265 && mouseY < 295)
									whoIsChoiced = 3;
								if (mouseY > 365 && mouseY < 395)
									whoIsChoiced = 4;
								if (mouseY > 465 && mouseY < 495)
									whoIsChoiced = 5;
								if (mouseY > 565 && mouseY < 595)
									whoIsChoiced = 6;
								if (mouseY > 665 && mouseY < 695)
									whoIsChoiced = 7;
							}

							if (mouseX > 590 && mouseX < 970)
								if (mouseY > 65 && mouseY < 695)
									whoIsChoiced = 8;
							if (btn1.isMouseOver(window)) {
								allText = textBox8.getText() + textBox81.getText() + textBox82.getText() + textBox83.getText() + textBox84.getText() + textBox85.getText() + textBox86.getText() + textBox87.getText() + textBox88.getText() + textBox89.getText();
								if (allText.size() > 0 &&
									(textBox1.getText()).size() > 0 &&
									(textBox2.getText()).size() > 0 &&
									(textBox3.getText()).size() > 0 &&
									(textBox4.getText()).size() > 0 &&
									(textBox5.getText()).size() > 0 &&
									(textBox6.getText()).size() > 0 &&
									(textBox7.getText()).size() > 0 &&
									(textBox8.getText()).size() > 0 &&
									textBox1.getText() != "_" &&
									textBox2.getText() != "_" &&
									textBox3.getText() != "_" &&
									textBox4.getText() != "_" &&
									textBox5.getText() != "_" &&
									textBox6.getText() != "_" &&
									textBox7.getText() != "_" &&
									allText != "_") {
									errorHere = false;
									setUpLink(myEvents, textBox9.getText(), textBox1.getText(), textBox2.getText(), textBox3.getText(), textBox4.getText(), textBox5.getText(), textBox6.getText(), textBox7.getText(), allText, 2);
									++EventsHave;
									textBox1.deleteAll();
									textBox2.deleteAll();
									textBox3.deleteAll();
									textBox4.deleteAll();
									textBox5.deleteAll();
									textBox6.deleteAll();
									textBox7.deleteAll();
									textBox8.deleteAll();
									textBox81.deleteAll();
									textBox82.deleteAll();
									textBox83.deleteAll();
									textBox84.deleteAll();
									textBox85.deleteAll();
									textBox86.deleteAll();
									textBox87.deleteAll();
									textBox88.deleteAll();
									textBox89.deleteAll();
									textBox9.deleteAll();
									finishToMenuFromCreate(&locCreate, event, &text10);
								}
								else {
									errorHere = true;
								}
							}
						}
					}
					while (window.pollEvent(event)) {

						if (event.type == sf::Event::TextEntered) {
							if ((event.text.unicode >= 65 && event.text.unicode <= 127) || (event.text.unicode >= 48 && event.text.unicode <= 57) || event.text.unicode == DELETE_KEY || event.text.unicode == 32) {
								switch (whoIsChoiced) {
								case 1: textBox1.typedOn(event); break;
								case 2:
									if ((event.text.unicode >= 48 && event.text.unicode <= 57) || event.text.unicode == DELETE_KEY)
										textBox2.typedOn(event); break;
								case 3: textBox3.typedOn(event); break;
								case 4: textBox4.typedOn(event); break;
								case 5: textBox5.typedOn(event); break;
								case 6: textBox6.typedOn(event); break;
								case 7: textBox7.typedOn(event); break;
								case 8:
									if (moreText < 31) {
										textBox8.typedOn(event);
									}
									else if (moreText < 61) {
										textBox81.typedOn(event);
									}
									else if (moreText < 91) {
										textBox82.typedOn(event);
									}
									else if (moreText < 121) {
										textBox83.typedOn(event);
									}
									else if (moreText < 151) {
										textBox84.typedOn(event);
									}
									else if (moreText < 181) {
										textBox85.typedOn(event);
									}
									else if (moreText < 211) {
										textBox86.typedOn(event);
									}
									else if (moreText < 241) {
										textBox87.typedOn(event);
									}
									else if (moreText < 271) {
										textBox88.typedOn(event);
									}
									else if (moreText < 301) {
										textBox89.typedOn(event);
									}
									if (event.text.unicode != DELETE_KEY)
										++moreText;
									else
										--moreText;
									break;
								}
							}
						}

						if (sf::Event::MouseMoved) {
							if (btn1.isMouseOver(window)) {
								btn1.hoverColorYes();
							}
							else {
								btn1.hoverColorNo();
							}
						}
					}
					textBox1.drawTo(window);
					textBox2.drawTo(window);
					textBox3.drawTo(window);
					textBox4.drawTo(window);
					textBox5.drawTo(window);
					textBox6.drawTo(window);
					textBox7.drawTo(window);
					textBox8.drawTo(window);
					textBox81.drawTo(window);
					textBox82.drawTo(window);
					textBox83.drawTo(window);
					textBox84.drawTo(window);
					textBox85.drawTo(window);
					textBox86.drawTo(window);
					textBox87.drawTo(window);
					textBox88.drawTo(window);
					textBox89.drawTo(window);
					if (errorHere)
						window.draw(error);
					btn1.drawTo(window);

					break;
				case 3: // add to position

					text6.setPosition(30, window.getSize().y - 50);
					window.draw(text17);
					window.draw(text18);
					window.draw(text19);
					window.draw(text20);
					window.draw(text21);
					window.draw(text22);
					window.draw(text23);
					window.draw(text24);
					window.draw(position);
					drowFrontBackOrEditTab(rectangle28, rectangle29, rectangle30, rectangle31, rectangle32, rectangle33, rectangle34, rectangle35, rectangle36, rectangle37, rectangle38, rectangle39, rectangle40, rectangle41, rectangle42, rectangle43);
					window.draw(text6);
					backToMenuFromCreate(&locCreate, event, &text6, &text10);

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
						switch (whoIsChoiced) {
						case 1: textBox1.setSelected(true); break;
						case 2: textBox2.setSelected(true); break;
						case 3: textBox3.setSelected(true); break;
						case 4: textBox4.setSelected(true); break;
						case 5: textBox5.setSelected(true); break;
						case 6: textBox6.setSelected(true); break;
						case 7: textBox7.setSelected(true); break;
						case 8:
							if (moreText <= 30) {
								textBox8.setSelected(true);
							}
							else if (moreText <= 60) {
								textBox81.setSelected(true);
							}
							else if (moreText <= 90) {
								textBox82.setSelected(true);
							}
							else if (moreText <= 120) {
								textBox83.setSelected(true);
							}
							else if (moreText <= 150) {
								textBox84.setSelected(true);
							}
							else if (moreText <= 180) {
								textBox85.setSelected(true);
							}
							else if (moreText <= 210) {
								textBox86.setSelected(true);
							}
							else if (moreText <= 240) {
								textBox87.setSelected(true);
							}
							else if (moreText <= 270) {
								textBox88.setSelected(true);
							}
							else if (moreText <= 300) {
								textBox89.setSelected(true);
							}

							break;
						case 9:	textBox10.setSelected(true); break;
						}
					}

					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
						switch (whoIsChoiced) {
						case 1: textBox1.setSelected(false); break;
						case 2: textBox2.setSelected(false); break;
						case 3: textBox3.setSelected(false); break;
						case 4: textBox4.setSelected(false); break;
						case 5: textBox5.setSelected(false); break;
						case 6: textBox6.setSelected(false); break;
						case 7: textBox7.setSelected(false); break;
						case 8:
							if (moreText <= 30) {
								textBox8.setSelected(false);
							}
							else if (moreText <= 60) {
								textBox81.setSelected(false);
							}
							else if (moreText <= 90) {
								textBox82.setSelected(false);
							}
							else if (moreText <= 120) {
								textBox83.setSelected(false);
							}
							else if (moreText <= 150) {
								textBox84.setSelected(false);
							}
							else if (moreText <= 180) {
								textBox85.setSelected(false);
							}
							else if (moreText <= 210) {
								textBox86.setSelected(false);
							}
							else if (moreText <= 240) {
								textBox87.setSelected(false);
							}
							else if (moreText <= 270) {
								textBox88.setSelected(false);
							}
							else if (moreText <= 300) {
								textBox89.setSelected(false);
							}

							break;
						case 9:	textBox10.setSelected(false); break;
						}
					}



					if (event.type == Event::MouseButtonPressed)
					{
						if (event.mouseButton.button == Mouse::Left)
						{
							if (mouseX > 55 && mouseX < 545)
							{
								if (mouseY > 65 && mouseY < 95)
									whoIsChoiced = 1;
								if (mouseY > 265 && mouseY < 295)
									whoIsChoiced = 3;
								if (mouseY > 365 && mouseY < 395)
									whoIsChoiced = 4;
								if (mouseY > 465 && mouseY < 495)
									whoIsChoiced = 5;
								if (mouseY > 565 && mouseY < 595)
									whoIsChoiced = 6;
								if (mouseY > 665 && mouseY < 695)
									whoIsChoiced = 7;
							}

							if (mouseX > 55 && mouseX < 295)
								if (mouseY > 165 && mouseY < 195)
									whoIsChoiced = 2;

							if (mouseX > 300 && mouseX < 545)
								if (mouseY > 165 && mouseY < 195)
									whoIsChoiced = 9;

							if (mouseX > 590 && mouseX < 970)
								if (mouseY > 65 && mouseY < 695)
									whoIsChoiced = 8;


							if (btn1.isMouseOver(window)) {
								allText = textBox8.getText() + textBox81.getText() + textBox82.getText() + textBox83.getText() + textBox84.getText() + textBox85.getText() + textBox86.getText() + textBox87.getText() + textBox88.getText() + textBox89.getText();
								if (allText.size() > 0 &&
									(textBox1.getText()).size() > 0 &&
									(textBox2.getText()).size() > 0 &&
									(textBox3.getText()).size() > 0 &&
									(textBox4.getText()).size() > 0 &&
									(textBox5.getText()).size() > 0 &&
									(textBox6.getText()).size() > 0 &&
									(textBox7.getText()).size() > 0 &&
									(textBox8.getText()).size() > 0 &&
									(textBox10.getText()).size() > 0 &&
									textBox1.getText() != "_" &&
									textBox2.getText() != "_" &&
									textBox3.getText() != "_" &&
									textBox4.getText() != "_" &&
									textBox5.getText() != "_" &&
									textBox6.getText() != "_" &&
									textBox7.getText() != "_" &&
									allText != "_" &&
									textBox10.getText() != "_") {
									int errorP = stoi(textBox10.getText());
									if (errorP <= rectangles) {
										errorHere = false;
										errPos = false;
										setUpLink(myEvents, textBox10.getText(), textBox1.getText(), textBox2.getText(), textBox3.getText(), textBox4.getText(), textBox5.getText(), textBox6.getText(), textBox7.getText(), allText, 3);
										++EventsHave;
										textBox1.deleteAll();
										textBox2.deleteAll();
										textBox3.deleteAll();
										textBox4.deleteAll();
										textBox5.deleteAll();
										textBox6.deleteAll();
										textBox7.deleteAll();
										textBox8.deleteAll();
										textBox81.deleteAll();
										textBox82.deleteAll();
										textBox83.deleteAll();
										textBox84.deleteAll();
										textBox85.deleteAll();
										textBox86.deleteAll();
										textBox87.deleteAll();
										textBox88.deleteAll();
										textBox89.deleteAll();
										textBox10.deleteAll();
										finishToMenuFromCreate(&locCreate, event, &text10);
									}
									else {
										errorHere = false;
										errPos = true;
									}
								}
								else {
									errPos = false;
									errorHere = true;
								}
							}
						}
					}
					while (window.pollEvent(event)) {

						if (event.type == sf::Event::TextEntered) {
							if ((event.text.unicode >= 65 && event.text.unicode <= 127) || (event.text.unicode >= 48 && event.text.unicode <= 57) || event.text.unicode == DELETE_KEY || event.text.unicode == 32) {
								switch (whoIsChoiced) {
								case 1: textBox1.typedOn(event); break;
								case 2:
									if ((event.text.unicode >= 48 && event.text.unicode <= 57) || event.text.unicode == DELETE_KEY)
										textBox2.typedOn(event); break;
								case 3: textBox3.typedOn(event); break;
								case 4: textBox4.typedOn(event); break;
								case 5: textBox5.typedOn(event); break;
								case 6: textBox6.typedOn(event); break;
								case 7: textBox7.typedOn(event); break;
								case 8:
									if (moreText < 31) {
										textBox8.typedOn(event);
									}
									else if (moreText < 61) {
										textBox81.typedOn(event);
									}
									else if (moreText < 91) {
										textBox82.typedOn(event);
									}
									else if (moreText < 121) {
										textBox83.typedOn(event);
									}
									else if (moreText < 151) {
										textBox84.typedOn(event);
									}
									else if (moreText < 181) {
										textBox85.typedOn(event);
									}
									else if (moreText < 211) {
										textBox86.typedOn(event);
									}
									else if (moreText < 241) {
										textBox87.typedOn(event);
									}
									else if (moreText < 271) {
										textBox88.typedOn(event);
									}
									else if (moreText < 301) {
										textBox89.typedOn(event);
									}
									if (event.text.unicode != DELETE_KEY)
										++moreText;
									else
										--moreText;
									break;
								case 9:
									if ((event.text.unicode >= 48 && event.text.unicode <= 57) || event.text.unicode == DELETE_KEY)
										textBox10.typedOn(event); break;
								}
							}
						}

						if (sf::Event::MouseMoved) {
							if (btn1.isMouseOver(window)) {
								btn1.hoverColorYes();
							}
							else {
								btn1.hoverColorNo();
							}
						}
					}
					textBox1.drawTo(window);
					textBox2.drawTo(window);
					textBox3.drawTo(window);
					textBox4.drawTo(window);
					textBox5.drawTo(window);
					textBox6.drawTo(window);
					textBox7.drawTo(window);
					textBox8.drawTo(window);
					textBox81.drawTo(window);
					textBox82.drawTo(window);
					textBox83.drawTo(window);
					textBox84.drawTo(window);
					textBox85.drawTo(window);
					textBox86.drawTo(window);
					textBox87.drawTo(window);
					textBox88.drawTo(window);
					textBox89.drawTo(window);
					textBox10.drawTo(window);
					if (errorHere) {
						errPos = false;
						window.draw(error);
					}
					if (errPos) {
						errorHere = false;
						window.draw(errorPos);
					}
					btn1.drawTo(window);

					break;
				case 4: // edit
					text6.setPosition(30, window.getSize().y - 50);
					window.draw(text17);
					window.draw(text18);
					window.draw(text19);
					window.draw(text20);
					window.draw(text21);
					window.draw(text22);
					window.draw(text23);
					window.draw(text24);
					window.draw(position);
					drowFrontBackOrEditTab(rectangle28, rectangle29, rectangle30, rectangle31, rectangle32, rectangle33, rectangle34, rectangle35, rectangle36, rectangle37, rectangle38, rectangle39, rectangle40, rectangle41, rectangle42, rectangle43);
					window.draw(text6);
					backToMenuFromCreate(&locCreate, event, &text6, &text10);

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
						switch (whoIsChoiced) {
						case 1: textBox1.setSelected(true); break;
						case 2: textBox2.setSelected(true); break;
						case 3: textBox3.setSelected(true); break;
						case 4: textBox4.setSelected(true); break;
						case 5: textBox5.setSelected(true); break;
						case 6: textBox6.setSelected(true); break;
						case 7: textBox7.setSelected(true); break;
						case 8:
							if (moreText <= 30) {
								textBox8.setSelected(true);
							}
							else if (moreText <= 60) {
								textBox81.setSelected(true);
							}
							else if (moreText <= 90) {
								textBox82.setSelected(true);
							}
							else if (moreText <= 120) {
								textBox83.setSelected(true);
							}
							else if (moreText <= 150) {
								textBox84.setSelected(true);
							}
							else if (moreText <= 180) {
								textBox85.setSelected(true);
							}
							else if (moreText <= 210) {
								textBox86.setSelected(true);
							}
							else if (moreText <= 240) {
								textBox87.setSelected(true);
							}
							else if (moreText <= 270) {
								textBox88.setSelected(true);
							}
							else if (moreText <= 300) {
								textBox89.setSelected(true);
							}

							break;
						case 9:	textBox10.setSelected(true); break;
						}
					}

					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
						switch (whoIsChoiced) {
						case 1: textBox1.setSelected(false); break;
						case 2: textBox2.setSelected(false); break;
						case 3: textBox3.setSelected(false); break;
						case 4: textBox4.setSelected(false); break;
						case 5: textBox5.setSelected(false); break;
						case 6: textBox6.setSelected(false); break;
						case 7: textBox7.setSelected(false); break;
						case 8:
							if (moreText <= 30) {
								textBox8.setSelected(false);
							}
							else if (moreText <= 60) {
								textBox81.setSelected(false);
							}
							else if (moreText <= 90) {
								textBox82.setSelected(false);
							}
							else if (moreText <= 120) {
								textBox83.setSelected(false);
							}
							else if (moreText <= 150) {
								textBox84.setSelected(false);
							}
							else if (moreText <= 180) {
								textBox85.setSelected(false);
							}
							else if (moreText <= 210) {
								textBox86.setSelected(false);
							}
							else if (moreText <= 240) {
								textBox87.setSelected(false);
							}
							else if (moreText <= 270) {
								textBox88.setSelected(false);
							}
							else if (moreText <= 300) {
								textBox89.setSelected(false);
							}

							break;
						case 9:	textBox10.setSelected(false); break;
						}
					}



					if (event.type == Event::MouseButtonPressed)
					{
						if (event.mouseButton.button == Mouse::Left)
						{
							if (mouseX > 55 && mouseX < 545)
							{
								if (mouseY > 65 && mouseY < 95)
									whoIsChoiced = 1;
								if (mouseY > 265 && mouseY < 295)
									whoIsChoiced = 3;
								if (mouseY > 365 && mouseY < 395)
									whoIsChoiced = 4;
								if (mouseY > 465 && mouseY < 495)
									whoIsChoiced = 5;
								if (mouseY > 565 && mouseY < 595)
									whoIsChoiced = 6;
								if (mouseY > 665 && mouseY < 695)
									whoIsChoiced = 7;
							}

							if (mouseX > 55 && mouseX < 295)
								if (mouseY > 165 && mouseY < 195)
									whoIsChoiced = 2;

							if (mouseX > 300 && mouseX < 545)
								if (mouseY > 165 && mouseY < 195)
									whoIsChoiced = 9;

							if (mouseX > 590 && mouseX < 970)
								if (mouseY > 65 && mouseY < 695)
									whoIsChoiced = 8;


							if (btn1.isMouseOver(window)) {
								allText = textBox8.getText() + textBox81.getText() + textBox82.getText() + textBox83.getText() + textBox84.getText() + textBox85.getText() + textBox86.getText() + textBox87.getText() + textBox88.getText() + textBox89.getText();
								if (allText.size() > 0 &&
									(textBox1.getText()).size() > 0 &&
									(textBox2.getText()).size() > 0 &&
									(textBox3.getText()).size() > 0 &&
									(textBox4.getText()).size() > 0 &&
									(textBox5.getText()).size() > 0 &&
									(textBox6.getText()).size() > 0 &&
									(textBox7.getText()).size() > 0 &&
									(textBox8.getText()).size() > 0 &&
									(textBox10.getText()).size() > 0 &&
									textBox1.getText() != "_" &&
									textBox2.getText() != "_" &&
									textBox3.getText() != "_" &&
									textBox4.getText() != "_" &&
									textBox5.getText() != "_" &&
									textBox6.getText() != "_" &&
									textBox7.getText() != "_" &&
									allText != "_" &&
									textBox10.getText() != "_") {
									int errorP = stoi(textBox10.getText());
									if (errorP <= rectangles) {
										errorHere = false;
										errPos = false;
										setUpLink(myEvents, textBox10.getText(), textBox1.getText(), textBox2.getText(), textBox3.getText(), textBox4.getText(), textBox5.getText(), textBox6.getText(), textBox7.getText(), allText, 4);
										++EventsHave;
										textBox1.deleteAll();
										textBox2.deleteAll();
										textBox3.deleteAll();
										textBox4.deleteAll();
										textBox5.deleteAll();
										textBox6.deleteAll();
										textBox7.deleteAll();
										textBox8.deleteAll();
										textBox81.deleteAll();
										textBox82.deleteAll();
										textBox83.deleteAll();
										textBox84.deleteAll();
										textBox85.deleteAll();
										textBox86.deleteAll();
										textBox87.deleteAll();
										textBox88.deleteAll();
										textBox89.deleteAll();
										textBox10.deleteAll();
										finishToMenuFromCreate(&locCreate, event, &text10);
									}
									else {
										errorHere = false;
										errPos = true;
									}
								}
								else {
									errPos = false;
									errorHere = true;
								}
							}
						}
					}
					while (window.pollEvent(event)) {

						if (event.type == sf::Event::TextEntered) {
							if ((event.text.unicode >= 65 && event.text.unicode <= 127) || (event.text.unicode >= 48 && event.text.unicode <= 57) || event.text.unicode == DELETE_KEY || event.text.unicode == 32) {
								switch (whoIsChoiced) {
								case 1: textBox1.typedOn(event); break;
								case 2:
									if ((event.text.unicode >= 48 && event.text.unicode <= 57) || event.text.unicode == DELETE_KEY)
										textBox2.typedOn(event); break;
								case 3: textBox3.typedOn(event); break;
								case 4: textBox4.typedOn(event); break;
								case 5: textBox5.typedOn(event); break;
								case 6: textBox6.typedOn(event); break;
								case 7: textBox7.typedOn(event); break;
								case 8:
									if (moreText < 31) {
										textBox8.typedOn(event);
									}
									else if (moreText < 61) {
										textBox81.typedOn(event);
									}
									else if (moreText < 91) {
										textBox82.typedOn(event);
									}
									else if (moreText < 121) {
										textBox83.typedOn(event);
									}
									else if (moreText < 151) {
										textBox84.typedOn(event);
									}
									else if (moreText < 181) {
										textBox85.typedOn(event);
									}
									else if (moreText < 211) {
										textBox86.typedOn(event);
									}
									else if (moreText < 241) {
										textBox87.typedOn(event);
									}
									else if (moreText < 271) {
										textBox88.typedOn(event);
									}
									else if (moreText < 301) {
										textBox89.typedOn(event);
									}
									if (event.text.unicode != DELETE_KEY)
										++moreText;
									else
										--moreText;
									break;
								case 9:
									if ((event.text.unicode >= 48 && event.text.unicode <= 57) || event.text.unicode == DELETE_KEY)
										textBox10.typedOn(event); break;
								}
							}
						}

						if (sf::Event::MouseMoved) {
							if (btn1.isMouseOver(window)) {
								btn1.hoverColorYes();
							}
							else {
								btn1.hoverColorNo();
							}
						}
					}
					textBox1.drawTo(window);
					textBox2.drawTo(window);
					textBox3.drawTo(window);
					textBox4.drawTo(window);
					textBox5.drawTo(window);
					textBox6.drawTo(window);
					textBox7.drawTo(window);
					textBox8.drawTo(window);
					textBox81.drawTo(window);
					textBox82.drawTo(window);
					textBox83.drawTo(window);
					textBox84.drawTo(window);
					textBox85.drawTo(window);
					textBox86.drawTo(window);
					textBox87.drawTo(window);
					textBox88.drawTo(window);
					textBox89.drawTo(window);
					textBox10.drawTo(window);
					if (errorHere) {
						errPos = false;
						window.draw(error);
					}
					if (errPos) {
						errorHere = false;
						window.draw(errorPos);
					}
					btn1.drawTo(window);

					break;
					/*
					case 5: // delete one
					case 6: // delete all
					case 7: // save
					case 8: // auto save
					*/

				default:
					text6.setPosition(0, 770);
					window.draw(rectangleMoreInfo);
					window.draw(rectangleMoreInf);

					window.draw(rectangle5);
					window.draw(rectangle7);
					window.draw(rectangle10);

					if (rectangles > 7)
					{
						if (p1 > 0 && p1 <= rectangles - 7)
						{
							if (Mouse::getPosition(window).x > window.getSize().x - 358 && Mouse::getPosition(window).x < window.getSize().x - 338 &&
								Mouse::getPosition(window).y>45 && Mouse::getPosition(window).y < 55)
							{
								switch (event.type)
								{
								case Event::MouseButtonPressed:
									if (event.mouseButton.button == Mouse::Left)
									{
										p1--;

										Mouse::setPosition(Vector2i(Mouse::getPosition(window).x + 6, Mouse::getPosition(window).y + 6), window);
									}
								}
							}
						}
						if (p1 >= 0 && p1 < rectangles - 7)
						{
							if (Mouse::getPosition(window).x > window.getSize().x - 358 && Mouse::getPosition(window).x < window.getSize().x - 338 &&
								Mouse::getPosition(window).y>window.getSize().y - 50 && Mouse::getPosition(window).y < window.getSize().y - 35)
							{
								if (event.type == Event::MouseButtonPressed)
								{
									if (event.mouseButton.button == Mouse::Left)
									{
										p1++;
										Mouse::setPosition(Vector2i(Mouse::getPosition(window).x - 4, Mouse::getPosition(window).y - 4), window);
									}
								}
							}
						}
						rectangleScroll.setSize(Vector2f(window.getSize().x / 66, 7 * (window.getSize().y - 130) / rectangles));
						rectangleScroll.setPosition(window.getSize().x - 350, 65 + p1 * (window.getSize().y - 130) / rectangles);
						window.draw(s8);
						window.draw(s9);
						window.draw(rectangleScroll);
					}
					else
					{
						rectangleScroll.setSize(Vector2f(window.getSize().x / 66, window.getSize().y - 130));
						rectangleScroll.setPosition(window.getSize().x - 350, 65);
						window.draw(rectangleScroll);
					}

					if (howManyEventsHave == EventsHave) {
						++howManyEventsHave;
						Node* temp = myEvents;
						rectangles = 0;
						while (temp)
						{
							titleAndYear[rectangles] = to_string(rectangles) + "." + temp->title + " - " + to_string(temp->year);

							string p = temp->participants;
							string e = temp->era;
							string l = temp->location;
							string rea = temp->reason;
							string res = temp->result;

							if (p.size() > 24) {
								p.insert(24, "\n");
							}

							if (e.size() > 24) {
								e.insert(24, "\n");
							}

							if (l.size() > 24) {
								l.insert(24, "\n");
							}

							if (rea.size() > 24) {
								rea.insert(24, "\n");
							}

							if (res.size() > 24) {
								res.insert(24, "\n");
							}

							allInfo[rectangles] =
								"      More Information\n\n"
								"Participants: \n" + p + "\n\n"
								+ "Era: \n" + e + "\n\n"
								+ "Location: \n" + l + "\n\n"
								+ "Reason: \n" + rea + "\n\n"
								+ "Result: \n" + res + "\n";
							if (p1 == 0) {
								if (rectangles < 7) {
									info[rectangles].setString(allInfo[rectangles]);
									info[rectangles].setFont(f2);
									info[rectangles].setCharacterSize(15);
									info[rectangles].setFillColor(Color(188, 145, 118));
									info[rectangles].setPosition(720, 405);
									h[rectangles].setString(titleAndYear[rectangles]);
									h[rectangles].setFont(f2);
									h[rectangles].setCharacterSize(20);
									h[rectangles].setFillColor(Color(254, 254, 254));
									h[rectangles].setPosition(50, 70 + rectangles * 105);
								}
							}
							else {
								int oldRectangles = 0;
								while (oldRectangles != 7) {
									info[oldRectangles].setString(allInfo[oldRectangles + p1]);
									info[oldRectangles].setFont(f2);
									info[oldRectangles].setCharacterSize(15);
									info[oldRectangles].setFillColor(Color(188, 145, 118));
									info[oldRectangles].setPosition(720, 405);
									h[oldRectangles].setString(titleAndYear[oldRectangles + p1]);
									h[oldRectangles].setFont(f2);
									h[oldRectangles].setCharacterSize(20);
									h[oldRectangles].setFillColor(Color(254, 254, 254));
									h[oldRectangles].setPosition(50, 70 + oldRectangles * 105);
									++oldRectangles;
								}
							}
							++rectangles;
							temp = temp->next;
						}
						//--rectangles;
					}

					text6.setPosition(0, 770);

					if (rectangles <= 7) {
						for (int i = 0; i < rectangles; i++)
						{
							window.draw(Hello[i]);
						}
						for (int i = 0; i < rectangles; i++)
						{
							window.draw(h[i]);
						}
					}
					else {
						for (int i = 0; i < 7; i++)
						{
							window.draw(Hello[i]);
						}
						for (int i = 0; i < 7; i++)
						{
							window.draw(h[i]);
						}
					}
					if (Mouse::getPosition(window).x > 35 && Mouse::getPosition(window).x < 645 &&
						Mouse::getPosition(window).y>35 && Mouse::getPosition(window).y < 135) {
						if (event.type == Event::MouseButtonPressed)
						{
							if (event.mouseButton.button == Mouse::Left)
							{
								infoChoice = 1;
							}
						}
					}
					if (Mouse::getPosition(window).x > 35 && Mouse::getPosition(window).x < 645 &&
						Mouse::getPosition(window).y>35 + 105 * 1 && Mouse::getPosition(window).y < 135 + 105 * 1) {
						if (event.type == Event::MouseButtonPressed)
						{
							if (event.mouseButton.button == Mouse::Left)
							{
								infoChoice = 2;
							}
						}
					}
					if (Mouse::getPosition(window).x > 35 && Mouse::getPosition(window).x < 645 &&
						Mouse::getPosition(window).y>35 + 105 * 2 && Mouse::getPosition(window).y < 135 + 105 * 2) {
						if (event.type == Event::MouseButtonPressed)
						{
							if (event.mouseButton.button == Mouse::Left)
							{
								infoChoice = 3;
							}
						}
					}
					if (Mouse::getPosition(window).x > 35 && Mouse::getPosition(window).x < 645 &&
						Mouse::getPosition(window).y>35 + 105 * 3 && Mouse::getPosition(window).y < 135 + 105 * 3) {
						if (event.type == Event::MouseButtonPressed)
						{
							if (event.mouseButton.button == Mouse::Left)
							{
								infoChoice = 4;
							}
						}
					}
					if (Mouse::getPosition(window).x > 35 && Mouse::getPosition(window).x < 645 &&
						Mouse::getPosition(window).y>35 + 105 * 4 && Mouse::getPosition(window).y < 135 + 105 * 4) {
						if (event.type == Event::MouseButtonPressed)
						{
							if (event.mouseButton.button == Mouse::Left)
							{
								infoChoice = 5;
							}
						}
					}
					if (Mouse::getPosition(window).x > 35 && Mouse::getPosition(window).x < 645 &&
						Mouse::getPosition(window).y>35 + 105 * 5 && Mouse::getPosition(window).y < 135 + 105 * 5) {
						if (event.type == Event::MouseButtonPressed)
						{
							if (event.mouseButton.button == Mouse::Left)
							{
								infoChoice = 6;
							}
						}
					}
					if (Mouse::getPosition(window).x > 35 && Mouse::getPosition(window).x < 645 &&
						Mouse::getPosition(window).y>35 + 105 * 6 && Mouse::getPosition(window).y < 135 + 105 * 6) {
						if (event.type == Event::MouseButtonPressed)
						{
							if (event.mouseButton.button == Mouse::Left)
							{
								infoChoice = 7;
							}
						}
					}
					if (rectangles != 0) {
						switch (infoChoice) {
						case 1:
							window.draw(info[0]);
							break;
						case 2:
							window.draw(info[1]);
							break;
						case 3:
							window.draw(info[2]);
							break;
						case 4:
							window.draw(info[3]);
							break;
						case 5:
							window.draw(info[4]);
							break;
						case 6:
							window.draw(info[5]);
							break;
						case 7:
							window.draw(info[6]);
							break;
						default:
							break;
						}
					}
					window.draw(text10);
					if (Mouse::getPosition(window).x > window.getSize().x - 310 && Mouse::getPosition(window).x < window.getSize().x - 10 &&
						Mouse::getPosition(window).y>25 && Mouse::getPosition(window).y < fu1)
					{
						fu1 = 385;
						dropDown(&rectangle8, 65, 105);
						dropDown(&rectangle9, 105, 145);
						dropDown(&rectangle22, 145, 185);
						dropDown(&rectangle23, 185, 225);
						dropDown(&rectangle24, 225, 265);
						dropDown(&rectangle25, 265, 305);
						dropDown(&rectangle26, 305, 345);
						dropDown(&rectangle27, 345, 385);
						window.draw(rectangle7);
						window.draw(rectangle8);
						window.draw(rectangle9);
						window.draw(rectangle22);
						window.draw(rectangle23);
						window.draw(rectangle24);
						window.draw(rectangle25);
						window.draw(rectangle26);
						window.draw(rectangle27);

						window.draw(text8);
						window.draw(text9);
						window.draw(text11);
						window.draw(text12);
						window.draw(text13);
						window.draw(text14);
						window.draw(text15);
						window.draw(text16);
						if (Mouse::getPosition(window).x > window.getSize().x - 310 && Mouse::getPosition(window).x < window.getSize().x - 10 &&
							Mouse::getPosition(window).y>65 && Mouse::getPosition(window).y < 105)
						{
							currentLocationDropDown(&locCreate, 1, event);
						}

						if (Mouse::getPosition(window).x > 50 && Mouse::getPosition(window).x < window.getSize().x - 50 &&
							Mouse::getPosition(window).y>105 && Mouse::getPosition(window).y < 145)
						{
							currentLocationDropDown(&locCreate, 2, event);
						}

						if (Mouse::getPosition(window).x > 50 && Mouse::getPosition(window).x < window.getSize().x - 50 &&
							Mouse::getPosition(window).y>145 && Mouse::getPosition(window).y < 185)
						{
							currentLocationDropDown(&locCreate, 3, event);
						}

						if (Mouse::getPosition(window).x > 50 && Mouse::getPosition(window).x < window.getSize().x - 50 &&
							Mouse::getPosition(window).y>185 && Mouse::getPosition(window).y < 225)
						{
							if (rectangles != 0) {
								currentLocationDropDown(&locCreate, 4, event);
							}
							else {
								if (event.type == Event::MouseButtonPressed)
								{
									if (event.mouseButton.button == Mouse::Left)
									{
										window.draw(rectangleDDASSA);
										window.draw(rectangleDDASSA1);
										window.draw(edit);
									}
								}
							}
						}

						if (Mouse::getPosition(window).x > 50 && Mouse::getPosition(window).x < window.getSize().x - 50 &&
							Mouse::getPosition(window).y>225 && Mouse::getPosition(window).y < 265)
						{
							// delete one
							if (rectangles != 0) {
								if (event.type == Event::MouseButtonPressed)
								{
									if (event.mouseButton.button == Mouse::Left)
									{
										D = 0;
										choicePos = 0;
									}
								}
							}
							else {
								if (event.type == Event::MouseButtonPressed)
								{
									if (event.mouseButton.button == Mouse::Left)
									{
										window.draw(rectangleDDASSA);
										window.draw(rectangleDDASSA1);
										window.draw(deleteOne);
									}
								}
							}

						}

						if (Mouse::getPosition(window).x > 50 && Mouse::getPosition(window).x < window.getSize().x - 50 &&
							Mouse::getPosition(window).y>265 && Mouse::getPosition(window).y < 305 /*&& locCreate == 6*/)
						{
							// delete all
							if (rectangles != 0) {
								if (event.type == Event::MouseButtonPressed)
								{
									if (event.mouseButton.button == Mouse::Left)
									{
										D = 0;
										choiceYesNo = 1;
									}
								}
							}
							else {
								if (event.type == Event::MouseButtonPressed)
								{
									if (event.mouseButton.button == Mouse::Left)
									{
										window.draw(rectangleDDASSA);
										window.draw(rectangleDDASSA1);
										window.draw(deleteOne);
									}
								}
							}
						}

						if (Mouse::getPosition(window).x > 50 && Mouse::getPosition(window).x < window.getSize().x - 50 &&
							Mouse::getPosition(window).y>305 && Mouse::getPosition(window).y < 345 /*&& locCreate == 7*/)
						{
							if (event.type == Event::MouseButtonPressed)
							{
								if (event.mouseButton.button == Mouse::Left)
								{
									D = 0;
									choiceYesNo = 2;
								}
							}
						}

						if (Mouse::getPosition(window).x > 50 && Mouse::getPosition(window).x < window.getSize().x - 50 &&
							Mouse::getPosition(window).y>345 && Mouse::getPosition(window).y < 385)
						{
							if (event.type == Event::MouseButtonPressed)
							{
								if (event.mouseButton.button == Mouse::Left)
								{
									D = 0;
									choiceYesNo = 3;
								}
							}
						}

						window.draw(text6);
						backToMenu(&location, event, &text6);
					}
					else
					{
						fu1 = 65;
						window.draw(text6);
						backToMenu(&location, event, &text6);
					}
					if (D == 0) {
						window.draw(rectangleDDASSA);
						window.draw(rectangleDDASSA1);
						window.draw(rectangleDDASSAMini1);
						window.draw(rectangleDDASSAMini2);
						window.draw(yes);
						window.draw(no);
						if (choicePos > -1) {
							window.draw(choicePositionOfEvent);
							if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
								textBox9.setSelected(true);
							}
							else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
								textBox9.setSelected(false);
							}

							while (window.pollEvent(event)) {
								if (event.type == sf::Event::TextEntered) {
									if ((event.text.unicode >= 48 && event.text.unicode <= 57) || event.text.unicode == DELETE_KEY) {
										textBox9.typedOn(event);
									}
								}
							}
							if (Mouse::getPosition(window).x > window.getSize().x / 2 - 90 && Mouse::getPosition(window).x < window.getSize().x / 10 + window.getSize().x / 2 - 90 &&
								Mouse::getPosition(window).y>window.getSize().y / 2 + 30 && Mouse::getPosition(window).y < window.getSize().y / 2 + 30 + window.getSize().y / 10)
							{
								if (choicePos == 0)
									choiceYesNo = 0;
							}
							textBox9.drawTo(window);
						}
						else {
							window.draw(areYouSure);
						}
					}

					if (Mouse::getPosition(window).x > window.getSize().x / 2 - 90 && Mouse::getPosition(window).x < window.getSize().x / 10 + window.getSize().x / 2 - 90 &&
						Mouse::getPosition(window).y>window.getSize().y / 2 + 30 && Mouse::getPosition(window).y < window.getSize().y / 2 + 30 + window.getSize().y / 10)
					{ // yes
						if (event.type == Event::MouseButtonPressed)
						{
							if (event.mouseButton.button == Mouse::Left)
							{
								D = 1;
								switch (choiceYesNo) {
								case 0:
									pos = stoi(textBox9.getText());
									textBox9.deleteAll();
									if (pos > 0) {
										choiceYesNo = -1;
										deleteNode(&myEvents, --pos);
									}
									choiceYesNo = -1;
									choicePos = -1;
									pos = -1;
									if (p1 > 0)
										--p1;
									break;
								case 1:
									choiceYesNo = -1;
									choicePos = -1;
									rectangles = 0;
									pos = -1;
									p1 = 0;
									deleteAllNodes(&myEvents);
									break;
								case 2:
									choiceYesNo = -1;
									choicePos = -1;
									pos = -1;
									saveNodes(&myEvents);
									break;
								case 3:
									choiceYesNo = -1;
									choicePos = -1;
									pos = -1;
									autoSave = "yes";
									break;
								case 4: // edit

									break;
								case 5: // add to position
									if (pos > 0) {
										choiceYesNo = -1;
										choicePos = -1;
										pos = -1;
									}
									break;
								}
							}
						}
					}

					if (Mouse::getPosition(window).x > window.getSize().x / 2 + 90 && Mouse::getPosition(window).x < window.getSize().x / 10 + window.getSize().x / 2 + 90 &&
						Mouse::getPosition(window).y>window.getSize().y / 2 + 30 && Mouse::getPosition(window).y < window.getSize().y / 2 + 30 + window.getSize().y / 10)
					{ // no
						if (event.type == Event::MouseButtonPressed)
						{
							if (event.mouseButton.button == Mouse::Left)
							{
								textBox9.deleteAll();
								choiceYesNo = -1;
								choicePos = -1;
								pos = -1;
								autoSave = "no";
								D = 1;
							}
						}
					}

					break;
				}

				break;
			case 3:
				window.draw(text6);
				switch (locGame)
				{
				case 1:

					if (Mouse::getPosition(window).x > 30 && Mouse::getPosition(window).x < 100 &&
						Mouse::getPosition(window).y>window.getSize().y - 50 && Mouse::getPosition(window).y < window.getSize().y - 20)
					{
						text6.setFillColor(Color::White);
						if (event.type == Event::MouseButtonPressed)
						{
							if (event.mouseButton.button == Mouse::Left)
							{
								locGame = 0;
							}
						}
					}
					else
					{
						text6.setFillColor(Color::Black);
					}
					window.draw(rectanglePlay1);
					window.draw(rectanglePlay2);
					if (Mouse::getPosition(window).x > window.getSize().x - 180 && Mouse::getPosition(window).x < window.getSize().x - 100 &&
						Mouse::getPosition(window).y> window.getSize().y - 90 && Mouse::getPosition(window).y < window.getSize().y - 50)
					{
						textCheck.setFillColor(Color::White);
						if (event.type == Event::MouseButtonPressed)
						{
							if (event.mouseButton.button == Mouse::Left)
							{
								n1 = 1;
							}
						}
					}
					else
					{
						textCheck.setFillColor(Color::Black);
					}
					window.draw(textCheck);

					window.draw(rectangleHint1);
					window.draw(rectangleHint2);

					if (Mouse::getPosition(window).x > 100 && Mouse::getPosition(window).x < 220 &&
						Mouse::getPosition(window).y> window.getSize().y - 90 && Mouse::getPosition(window).y < window.getSize().y - 60)
					{
						textRandom.setFillColor(Color::White);
						if (event.type == Event::MouseButtonPressed)
						{
							if (event.mouseButton.button == Mouse::Left)
							{

							}
						}
					}
					else
					{
						textRandom.setFillColor(Color::Black);
					}
					window.draw(textRandom);

					if (Mouse::getPosition(window).x > window.getSize().x / 2 + 180 && Mouse::getPosition(window).x < window.getSize().x / 2 + 250 &&
						Mouse::getPosition(window).y> 50 && Mouse::getPosition(window).y < 90)
					{
						textHint.setFillColor(Color::White);
						if (event.type == Event::MouseButtonPressed)
						{
							if (event.mouseButton.button == Mouse::Left)
							{
								n1 = 2;
							}
						}
					}
					else
					{
						textHint.setFillColor(Color::Black);
					}
					window.draw(textHint);
					window.draw(rectanglePlayBox1);
					window.draw(rectanglePlayBox11);
					window.draw(rectanglePlayBox2);
					window.draw(rectanglePlayBox21);
					window.draw(rectanglePlayBox3);
					window.draw(rectanglePlayBox31);
					window.draw(rectanglePlayBox9);
					window.draw(rectanglePlayBox91);
					window.draw(rectanglePlayBox10);
					window.draw(rectanglePlayBox101);

					window.draw(rectanglePlayBox4);
					window.draw(rectanglePlayBox41);
					window.draw(rectanglePlayBox5);
					window.draw(rectanglePlayBox51);
					window.draw(rectanglePlayBox6);
					window.draw(rectanglePlayBox61);
					window.draw(rectanglePlayBox7);
					window.draw(rectanglePlayBox71);
					window.draw(rectanglePlayBox8);
					window.draw(rectanglePlayBox81);
					window.draw(text6);
					if (n1 == 1)
					{
						window.draw(rectangleCheck1);
						window.draw(rectangleCheck2);
					}

					text6.setPosition(30, window.getSize().y - 50);

					// 1111111111111111111111111111111111111
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
						textBoxGame1.setSelected(true);

					if (Mouse::getPosition(window).x > 715 && Mouse::getPosition(window).x < 825 &&
						Mouse::getPosition(window).y > 175 && Mouse::getPosition(window).y < 215) {
						if (event.type == Event::MouseButtonPressed)
						{
							if (event.mouseButton.button == Mouse::Left)
							{
								canWriteGame1 = true;
							}
						}
					}

					if (Mouse::getPosition(window).x > 840 && Mouse::getPosition(window).x < 880 &&
						Mouse::getPosition(window).y > 175 && Mouse::getPosition(window).y < 215) {

						if (event.type == Event::MouseButtonPressed)
						{
							if (event.mouseButton.button == Mouse::Left)
							{
								canWriteGame1 = false;
								if (btn2.isMouseOver(window)) {
									textBoxGame1.deleteAll();
								}
							}
						}
					}

					if (canWriteGame1) {
						while (window.pollEvent(event)) {
							if (event.type == sf::Event::TextEntered) {
								if ((event.text.unicode >= 48 && event.text.unicode <= 57) ||
									event.text.unicode == DELETE_KEY) {
									textBoxGame1.typedOn(event);
								}
							}
						}
					}

					textBoxGame1.drawTo(window);

					//222222222222222222222
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
						textBoxGame2.setSelected(true);

					if (Mouse::getPosition(window).x > 715 && Mouse::getPosition(window).x < 825 &&
						Mouse::getPosition(window).y > 280 && Mouse::getPosition(window).y < 320) {
						if (event.type == Event::MouseButtonPressed)
						{
							if (event.mouseButton.button == Mouse::Left)
							{
								canWriteGame2 = true;
							}
						}
					}

					if (Mouse::getPosition(window).x > 840 && Mouse::getPosition(window).x < 880 &&
						Mouse::getPosition(window).y > 285 && Mouse::getPosition(window).y < 325) {

						if (event.type == Event::MouseButtonPressed)
						{
							if (event.mouseButton.button == Mouse::Left)
							{
								canWriteGame2 = false;
								if (btn2.isMouseOver(window)) {
									textBoxGame2.deleteAll();
								}
							}
						}
					}

					if (canWriteGame2) {
						while (window.pollEvent(event)) {
							if (event.type == sf::Event::TextEntered) {
								if ((event.text.unicode >= 48 && event.text.unicode <= 57) ||
									event.text.unicode == DELETE_KEY) {
									textBoxGame2.typedOn(event);
								}
							}
						}
					}

					textBoxGame2.drawTo(window);



					// 3333333333333333333333333333
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
						textBoxGame3.setSelected(true);

					if (Mouse::getPosition(window).x > 715 && Mouse::getPosition(window).x < 825 &&
						Mouse::getPosition(window).y > 380 && Mouse::getPosition(window).y < 425) {
						if (event.type == Event::MouseButtonPressed)
						{
							if (event.mouseButton.button == Mouse::Left)
							{
								canWriteGame3 = true;
							}
						}
					}

					if (Mouse::getPosition(window).x > 840 && Mouse::getPosition(window).x < 880 &&
						Mouse::getPosition(window).y > 390 && Mouse::getPosition(window).y < 430) {

						if (event.type == Event::MouseButtonPressed)
						{
							if (event.mouseButton.button == Mouse::Left)
							{
								canWriteGame2 = false;
								if (btn2.isMouseOver(window)) {
									textBoxGame2.deleteAll();
								}
							}
						}
					}

					if (canWriteGame3) {
						while (window.pollEvent(event)) {
							if (event.type == sf::Event::TextEntered) {
								if ((event.text.unicode >= 48 && event.text.unicode <= 57) ||
									event.text.unicode == DELETE_KEY) {
									textBoxGame3.typedOn(event);
								}
							}
						}
					}

					textBoxGame3.drawTo(window);


					// 44444444444444444444444
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
						textBoxGame4.setSelected(true);

					if (Mouse::getPosition(window).x > 715 && Mouse::getPosition(window).x < 825 &&
						Mouse::getPosition(window).y > 490 && Mouse::getPosition(window).y < 530) {
						if (event.type == Event::MouseButtonPressed)
						{
							if (event.mouseButton.button == Mouse::Left)
							{
								canWriteGame4 = true;
							}
						}
					}

					if (Mouse::getPosition(window).x > 840 && Mouse::getPosition(window).x < 880 &&
						Mouse::getPosition(window).y > 490 && Mouse::getPosition(window).y < 530) {

						if (event.type == Event::MouseButtonPressed)
						{
							if (event.mouseButton.button == Mouse::Left)
							{
								canWriteGame2 = false;
								if (btn2.isMouseOver(window)) {
									textBoxGame2.deleteAll();
								}
							}
						}
					}

					if (canWriteGame4) {
						while (window.pollEvent(event)) {
							if (event.type == sf::Event::TextEntered) {
								if ((event.text.unicode >= 48 && event.text.unicode <= 57) ||
									event.text.unicode == DELETE_KEY) {
									textBoxGame4.typedOn(event);
								}
							}
						}
					}

					textBoxGame4.drawTo(window);


					//5555555555555555555555555
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
						textBoxGame5.setSelected(true);

					if (Mouse::getPosition(window).x > 715 && Mouse::getPosition(window).x < 825 &&
						Mouse::getPosition(window).y > 595 && Mouse::getPosition(window).y < 635) {
						if (event.type == Event::MouseButtonPressed)
						{
							if (event.mouseButton.button == Mouse::Left)
							{
								canWriteGame5 = true;
							}
						}
					}

					if (Mouse::getPosition(window).x > 840 && Mouse::getPosition(window).x < 880 &&
						Mouse::getPosition(window).y > 600 && Mouse::getPosition(window).y < 640) {

						if (event.type == Event::MouseButtonPressed)
						{
							if (event.mouseButton.button == Mouse::Left)
							{
								canWriteGame2 = false;
								if (btn2.isMouseOver(window)) {
									textBoxGame2.deleteAll();
								}
							}
						}
					}

					if (canWriteGame5) {
						while (window.pollEvent(event)) {
							if (event.type == sf::Event::TextEntered) {
								if ((event.text.unicode >= 48 && event.text.unicode <= 57) ||
									event.text.unicode == DELETE_KEY) {
									textBoxGame5.typedOn(event);
								}
							}
						}
					}

					textBoxGame5.drawTo(window);
					break;
				default:
					n1 = 0;
					text6.setPosition(0, 770);
					window.draw(recrtangleGame1);
					window.draw(recrtangleGame2);
					window.draw(recrtangleGame3);
					window.draw(recrtangleGame4);
					window.draw(recrtangleGame5);
					window.draw(textGame1);
					window.draw(textGame2);
					window.draw(textPlay);
					if (Mouse::getPosition(window).x > window.getSize().x - 70 && Mouse::getPosition(window).x < window.getSize().x &&
						Mouse::getPosition(window).y>760 && Mouse::getPosition(window).y < window.getSize().y)
					{
						textPlay.setFillColor(Color::White);
						if (event.type == Event::MouseButtonPressed)
						{
							if (event.mouseButton.button == Mouse::Left)
							{
								locGame = 1;
							}
						}
					}
					else
					{
						textPlay.setFillColor(Color::Black);
					}

					window.draw(textHowToPlay);
					window.draw(textCodeOfGray);
					backToMenu(&location, event, &text6);
					break;
				}
				break;
			case 4:
				window.draw(text6);
				window.draw(recrtangleAboutUs1);
				window.draw(recrtangleAboutUs2);
				window.draw(recrtangleAboutUs3);
				window.draw(recrtangleAboutUs4);

				window.draw(recrtangleAboutUs5);
				window.draw(recrtangleAboutUs6);
				window.draw(recrtangleAboutUs7);
				window.draw(recrtangleAboutUs8);


				window.draw(recrtangleAboutUsH1);
				window.draw(recrtangleAboutUsH2);
				window.draw(recrtangleAboutUsS1);
				window.draw(recrtangleAboutUsS2);

				window.draw(recrtangleAboutUsG1);
				window.draw(recrtangleAboutUsG2);
				window.draw(recrtangleAboutUsM1);
				window.draw(recrtangleAboutUsM2);
				window.draw(sH);
				window.draw(sS);
				window.draw(sG);
				window.draw(sM);
				window.draw(textFE);
				window.draw(textBE);
				window.draw(textST);
				window.draw(textQA);

				window.draw(textH);
				window.draw(textS);
				window.draw(textG);
				window.draw(textM);


				window.draw(rectangleMiddle1);
				window.draw(rectangleMiddle2);
				backToMenu(&location, event, &text6);
				break;
			case 5:
				window.close();
				break;
			}
		}
		//cout << "rectangles = " << rectangles << endl;
		cout << Mouse::getPosition(window).x << " " << Mouse::getPosition(window).y << endl;
		window.display();
	}
}

