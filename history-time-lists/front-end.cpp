#include"SFML/Graphics.hpp"
#include<iostream>
#include<cmath>
#include <thread>
#include <chrono>
using namespace std;
using namespace sf;
RenderWindow window(VideoMode(1000, 800), "Helpopedia");

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
	if (Mouse::getPosition(window).x > 70 && Mouse::getPosition(window).x < 140 && Mouse::getPosition(window).y>window.getSize().y - 30 && Mouse::getPosition(window).y < window.getSize().y)
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

void dropDown(RectangleShape* rectangle, int minY, int maxY)
{
	if (Mouse::getPosition(window).x > 50 && Mouse::getPosition(window).x < window.getSize().x - 50 &&
		Mouse::getPosition(window).y>minY && Mouse::getPosition(window).y < maxY)
	{
		(*rectangle).setFillColor(Color::Color(200, 200, 200, 255));
	}
	else
	{
		(*rectangle).setFillColor(Color::Color(170, 170, 170, 255));
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

void currentLocationDropDown(int* ptr, int n, Event event, Text* textOne, Text* textTwo)
{
	(*textOne).setFillColor(Color::White);
	if (event.type == Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == Mouse::Left)
		{
			*ptr = n;
			(*textTwo).setString(((*textOne).getString()));
		}
	}

}

void deleteOption(Event event, Text* textOne, RectangleShape rectangleDDASSA, int* p)
{
	(*textOne).setFillColor(Color::White);
	if (event.type == Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == Mouse::Left)
		{
			*p = 1;
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
	(*rectangle).setFillColor(Color::Color(170, 170, 170, 255));
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
	(*rectangle).setFillColor(Color::Color(150, 150, 150, 255));
	(*rectangle).setPosition(35, plusLeft + (window.getSize().y / 8) * mulRight);
}

void addFromOrBack(RectangleShape* rectangle, int posY)
{
	(*rectangle).setFillColor(Color::Color(170, 170, 170, 255));
	(*rectangle).setPosition(50, posY);
}

void addFromOrBackTwo(RectangleShape* rectangle, int posY)
{
	(*rectangle).setFillColor(Color::White);
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

void inputData() {

}

void setUpMenu() {

	/*Font font;
	if (!font.loadFromFile("arial.ttf"))
		std::cout << "Font not found!\n";

	Textbox text100(20, sf::Color::White, true);
	text100.setPosition({ 100, 100 });
	text100.setLimit(true, 30);
	text100.setFont(font);

	Button btn1("Enter", { 200, 100 }, 30, sf::Color::Green, sf::Color::Black);
	btn1.setFont(font);
	btn1.setPosition({ 100, 300 });*/

	int location = 0, locCreate = 0;
	Texture tex1, tex2, tex3, tex4, tex5, tex6, tex7, tex8, tex9;
	Sprite s1(tex1), s2(tex2), s3(tex3), s4(tex4), s5(tex5), s6(tex6), s7(tex7), s8(tex8), s9(tex9);
	Font f1;
	f1.loadFromFile("Pacifico-Regular.ttf");

	Text text1, text2, text3, text4, text5, text, text6, text7, text8, text9, text10, text11, text12, text13, text14, text15, text16,
		text17, text18, text19, text20, text21, text22, text61, text23, text24;

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

	text8.setString("Add front");
	text8.setFont(f1);
	setDropDownMenuText(&text8, 75);

	text9.setString("Add back");
	text9.setFont(f1);
	setDropDownMenuText(&text9, 115);

	text11.setString("Add to position");
	text11.setFont(f1);
	setDropDownMenuText(&text11, 155);

	text12.setString("Edit");
	text12.setFont(f1);
	setDropDownMenuText(&text12, 195);

	text13.setString("Delete");
	text13.setFont(f1);
	setDropDownMenuText(&text13, 235);

	text14.setString("Delete all");
	text14.setFont(f1);
	setDropDownMenuText(&text14, 275);

	text15.setString("Save");
	text15.setFont(f1);
	setDropDownMenuText(&text15, 315);

	text16.setString("Auto save");
	text16.setFont(f1);
	setDropDownMenuText(&text16, 355);

	text10.setString("Choose one:");
	text10.setFont(f1);
	setDropDownMenuText(&text10, 30);



	text17.setString("Title:");
	text17.setFont(f1);
	textFrontBackOrEditTab(&text17, 30);

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

	tex8.loadFromFile("../images/upArrow.png");
	tex9.loadFromFile("../images/downArrow.png");

	tex4.loadFromFile("../images/arrowRight.png");
	tex5.loadFromFile("../images/arrowRight.png");

	tex6.loadFromFile("../images/arrowLeft.png");
	tex7.loadFromFile("../images/arrowLeft.png");
	Text textsArray[] = { text1, text2, text3, text4, text5, text6, text7, text8, text9, text10, text11, text12, text13, text14 , text15, text16, text17, text18,
						  text19, text20,  text21,  text22, text23, text24, text23, text22, text21, text20 , text19, text18, text17, text16, text15, text14, text13,
						  text12, text11, text10, text9, text8, text7, text6, text5, text4, text3, text2, text1, text2, text3, text4, text5, text6, text7, text8, text9, text10 };
	int widthDropDownMenu = 65;

	int n;
	int D = 0;
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

		//Gray rectangles Events
		rectangle44(Vector2f(window.getSize().x / 2 + 150, window.getSize().y / 2 + 50)),
		rectangle45(Vector2f((window.getSize().x - 130) / 2, window.getSize().y / 2 - 160)),
		rectangle46(Vector2f((window.getSize().x - 130) / 2, window.getSize().y / 2 - 160)),
		rectangle47(Vector2f(window.getSize().x / 2 - 270, window.getSize().y / 2 - 30)),
		rectangle53(Vector2f(window.getSize().x / 2 + 130, window.getSize().y / 14)),

		//White rectangles Events 
		rectangle48(Vector2f(window.getSize().x / 2 + 140, window.getSize().y / 2 - 30)),
		rectangle49(Vector2f((window.getSize().x - 230) / 2, window.getSize().y / 2 - 170)),
		rectangle50(Vector2f(window.getSize().x / 2 - 110, window.getSize().y / 2 - 170)),
		rectangle51(Vector2f((window.getSize().x / 2 - 60) / 2, window.getSize().y / 2 - 40)),
		rectangle52(Vector2f(window.getSize().x / 2 + 140, window.getSize().y / 12)),


		recrtangleSearch1(Vector2f(window.getSize().x / 2 - 270, window.getSize().y / 13.5)),
		recrtangleSearch2(Vector2f((window.getSize().x / 2 - 60) / 2, window.getSize().y / 16.5)),
		rectangle54(Vector2f(window.getSize().x / 2 - 465, window.getSize().y / 2 - 170)),
		rectangle55(Vector2f(window.getSize().x / 2 - 470, window.getSize().y / 2 - 170)),
		rectangleDDASSA(Vector2f(window.getSize().x / 3 + 100, window.getSize().y / 4)),
		rectangleDDASSAMini1(Vector2f(window.getSize().x / 10, window.getSize().y / 20)),
		rectangleDDASSAMini2(Vector2f(window.getSize().x / 10, window.getSize().y / 20)),
		rectangleDDASSA1(Vector2f(window.getSize().x / 3 + 90, window.getSize().y / 4 - 10)),
		rectangleScroll, rectangleMoreInfo(Vector2f((window.getSize().x - 100)/3, window.getSize().y/2-15)), 
		rectangleMoreInf(Vector2f((window.getSize().x - 130) / 3, window.getSize().y/2 - 25));


	rectangleDDASSA1.setFillColor(Color::Color(28, 167, 199, 255));
	rectangleDDASSA1.setPosition(window.getSize().x / 2 - window.getSize().x / 6 + 5, window.getSize().y / 2 - window.getSize().y / 8 + 5);
	rectangleScroll.setPosition(window.getSize().x - 350, 35);
	setRectangleEventsTab(&rectangle, 50, 50);
	setRectangleEventsTab(&rectangle2, 370, 520);
	setRectangleEventsTab(&rectangle3, 590, 520);
	setRectangleEventsTab(&rectangle4, 810, 520);

	rectangle5.setFillColor(Color::Color(150, 150, 150, 255));
	rectangle5.setPosition(25, 25);

	rectangleMoreInfo.setFillColor(Color::Red);
	rectangleMoreInfo.setPosition(window.getSize().x - 310, window.getSize().y - 410);

	rectangleMoreInf.setFillColor(Color::Blue);
	rectangleMoreInf.setPosition(window.getSize().x - 305, window.getSize().y - 405);

	rectangleDDASSA.setFillColor(Color::Color(175, 255, 255, 255));
	rectangleDDASSA.setPosition(window.getSize().x / 2 - window.getSize().x / 6, window.getSize().y / 2 - window.getSize().y / 8);

	rectangleDDASSA1.setFillColor(Color::Color(28, 167, 199, 255));
	rectangleDDASSA1.setPosition(window.getSize().x / 2 - window.getSize().x / 6 + 5, window.getSize().y / 2 - window.getSize().y / 8 + 5);

	rectangleDDASSAMini1.setFillColor(Color::Color(125, 106, 180, 255));
	rectangleDDASSAMini1.setPosition(window.getSize().x / 2 - 70, window.getSize().y / 2 + 10);

	rectangleDDASSAMini2.setFillColor(Color::Color(125, 106, 180, 255));
	rectangleDDASSAMini2.setPosition(window.getSize().x / 2 + 70, window.getSize().y / 2 + 10);

	rectangle10.setFillColor(Color::White);
	rectangle10.setPosition(30, 30);

	rectangle11.setFillColor(Color::Color(150, 150, 150, 255));
	rectangle11.setPosition(35, 35);
	rectangleScroll.setFillColor(Color::Color(130, 130, 130, 255));
	setRectangleCreateMainOne(&rectangle12, 40, 1);
	setRectangleCreateMainOne(&rectangle13, 45, 2);
	setRectangleCreateMainOne(&rectangle14, 50, 3);
	setRectangleCreateMainOne(&rectangle15, 55, 4);
	setRectangleCreateMainOne(&rectangle16, 60, 5);
	setRectangleCreateMainOne(&rectangle17, 65, 6);

	rectangle7.setFillColor(Color::Color(150, 150, 150, 255));
	rectangle7.setPosition(window.getSize().x - 310, 25);
	setRectangleDropDown(&rectangle8, 65);
	setRectangleDropDown(&rectangle9, 105);
	setRectangleDropDown(&rectangle22, 145);
	setRectangleDropDown(&rectangle23, 185);
	setRectangleDropDown(&rectangle24, 225);
	setRectangleDropDown(&rectangle25, 265);
	setRectangleDropDown(&rectangle26, 305);
	setRectangleDropDown(&rectangle27, 345);


	//Cray rectangles Create 
	addFromOrBack(&rectangle28, 60);
	addFromOrBack(&rectangle29, 160);
	addFromOrBack(&rectangle30, 260);
	addFromOrBack(&rectangle31, 360);
	addFromOrBack(&rectangle32, 460);
	addFromOrBack(&rectangle33, 560);
	addFromOrBack(&rectangle42, 660);

	addFromOrBack(&rectangle44, 50);
	addFromOrBack(&rectangle45, window.getSize().y / 2 + 120);
	rectangle46.setFillColor(Color::Color(170, 170, 170, 255));
	rectangle46.setPosition((window.getSize().x - 120) / 2 + 70, window.getSize().y / 2 + 120);

	rectangle47.setFillColor(Color::Color(170, 170, 170, 255));
	rectangle47.setPosition(window.getSize().x / 2 + 220, window.getSize().y / 12 + 65);

	rectangle53.setFillColor(Color::Color(170, 170, 170, 255));
	rectangle53.setPosition(60, 60);

	rectangle54.setFillColor(Color::White);
	rectangle54.setPosition(window.getSize().x / 2 - 55, window.getSize().y / 2 + 125);


	rectangle55.setFillColor(Color::White);
	rectangle55.setPosition(window.getSize().x - 90, window.getSize().y / 2 + 125);

	addFromOrBackTwo(&rectangle48, 125);
	addFromOrBackTwo(&rectangle49, window.getSize().y / 2 + 125);
	rectangle50.setFillColor(Color::White);
	rectangle50.setPosition((window.getSize().x - 120) / 2 + 75, window.getSize().y / 2 + 125);

	rectangle51.setFillColor(Color::White);
	rectangle51.setPosition(window.getSize().x / 2 + 225, window.getSize().y / 12 + 70);

	//rectangle1.setFillColor(Color::Color(170, 170, 170, 255));
	//rectangle1.setPosition(window.getSize().x / 2 + 225, window.getSize().y / 12 + 70);

	rectangle52.setFillColor(Color::White);
	rectangle52.setPosition(55, 55);

	recrtangleSearch2.setFillColor(Color::White);
	recrtangleSearch2.setPosition(window.getSize().x / 2 + 225, 55);

	recrtangleSearch1.setFillColor(Color::Color(170, 170, 170, 255));
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

	rectangle40.setFillColor(Color::White);
	rectangle40.setPosition(window.getSize().x / 2 + 90, 65);

	rectangle41.setFillColor(Color::Color(170, 170, 170, 255));
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

	s1.setPosition(window.getSize().x / 2 - tex1.getSize().x / 2, 0);
	s3.setPosition(window.getSize().x - 100, 55);
	s4.setPosition(window.getSize().x - 95, window.getSize().y - 270);
	s5.setPosition(window.getSize().x / 2 - 60, window.getSize().y - 270);
	s6.setPosition(window.getSize().x - 95, window.getSize().y - 90);
	s7.setPosition(window.getSize().x / 2 - 60, window.getSize().y - 90);
	s8.setPosition(window.getSize().x - 358, 35);
	s9.setPosition(window.getSize().x - 358, window.getSize().y - 60);

	RectangleShape rectanglesArray[7] = { rectangle11,
		rectangle12, rectangle13, rectangle14,
		rectangle15, rectangle16, rectangle17 };

	int p;
	cin >> p;
	int m = 2;
	int p1 = 0;
	int p2 = p;
	while (window.isOpen())
	{

		Event event;
		if (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		window.clear(Color(210, 210, 210, 255));
		cout << Mouse::getPosition(window).x<<" "<<  Mouse::getPosition(window).y << endl;
		if (location == 0)
		{
			window.draw(s1);
			window.draw(s2);
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
			switch (location)
			{
			case 1:
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
				window.draw(rectangle54);
				window.draw(rectangle55);
				//window.draw(rectangle1);
				window.draw(text6);
				window.draw(s3);
				window.draw(s4);
				window.draw(s6);

				window.draw(s5);
				window.draw(s7);
				break;
			case 2:
				switch (locCreate)
				{
				case 1:
					text6.setPosition(70, window.getSize().y - 30);
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
					break;
				case 2:
					text6.setPosition(70, window.getSize().y - 30);
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
					break;
				case 3:
					text6.setPosition(70, window.getSize().y - 30);
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
					break;
				case 4:
					text6.setPosition(70, window.getSize().y - 30);
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
					break;
				case 5:
					text6.setPosition(70, window.getSize().y - 30);
					window.draw(text6);
					backToMenuFromCreate(&locCreate, event, &text6, &text10);
					break;
				case 6:
					window.draw(rectangle28);
					break;
				case 7:
					text6.setPosition(70, window.getSize().y - 30);
					window.draw(text6);
					backToMenuFromCreate(&locCreate, event, &text6, &text10);
					break;
				case 8:
					text6.setPosition(70, window.getSize().y - 30);
					window.draw(text6);
					backToMenuFromCreate(&locCreate, event, &text6, &text10);
					break;
				default:
					/*if (p > 7)
					{
						rectangleScroll.setSize(Vector2f(window.getSize().x / 66, 7 * (window.getSize().y - 70) / p));
						rectangleScroll.setFillColor(Color::Color(130, 130, 130, 255));
						if (rectangleScroll.getPosition().y>=35&& rectangleScroll.getPosition().y<=window.getSize().y- 7 * (window.getSize().y - 70) / p)
						{
							if (event.mouseWheel.x > pow(10, 9))
							{

								if (p1 >= 0 && p1 <= 3)
								{
									rectangleScroll.setPosition(window.getSize().x - 350, 35 + p1 * 7 * (window.getSize().y - 70) / p);
									p1--;
								}
							}
							if (event.mouseWheel.x < -pow(10, 9))
							{

								if (p1 >= 0 && p1 <= 3)
								{
									rectangleScroll.setPosition(window.getSize().x - 350, 35 + p1 * 7 * (window.getSize().y - 70) / p);
									p1++;
								}
							}
						}
						if (p1 < 0)
						{
							while (p1 < 0)
							{
								p1++;
							}
						}

						if (p1 > 3)
						{
							while (p1 > 3)
							{
								p1--;
							}
						}
					}
					else
					{
						rectangleScroll.setFillColor(Color::Color(225, 225, 225, 225));
						rectangleScroll.setSize(Vector2f(window.getSize().x / 66, window.getSize().y - 70));
					}*/



					window.draw(rectangle5);
					window.draw(rectangle7);
					window.draw(rectangle10);
					window.draw(rectangleMoreInfo);
					window.draw(rectangleMoreInf);


					if (p > 7)
					{


						if (p1 > 0 && p1 <= p-7)
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
						if (p1 >= 0 && p1 < p - 7)
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
						rectangleScroll.setSize(Vector2f(window.getSize().x / 66, 7 * (window.getSize().y - 130) / p));
						rectangleScroll.setPosition(window.getSize().x - 350, 65 + p1 * (window.getSize().y - 130) / p);
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
					if (p >= 0 && p <= 7)
					{
						for (int i = 0; i < p; i++)
						{
							window.draw(rectanglesArray[i]);
						}
						for (int i = 0; i < p; i++)
						{
							window.draw(textsArray[i]);
						}
					}
					else
					{
						for (int i = 0; i < 7; i++)
						{
							window.draw(rectanglesArray[i]);
						}
						for (int i = 0; i < 7; i++)
						{
							window.draw(textsArray[i]);
						}
					}
					text6.setPosition(0, 770);
					window.draw(text10);
					if (D == 1)
					{
						window.draw(rectangleDDASSA);
						window.draw(rectangleDDASSA1);
						window.draw(rectangleDDASSAMini1);
						window.draw(rectangleDDASSAMini2);


						if (Mouse::getPosition(window).x > window.getSize().x / 2 - 70 && Mouse::getPosition(window).x < window.getSize().x / 10 + window.getSize().x / 2 - 70 &&
							Mouse::getPosition(window).y>window.getSize().y / 2 + 10 && Mouse::getPosition(window).y < window.getSize().y / 2 + 10 + window.getSize().y / 10)
						{
							deleteAllButton(event, &p);
							if (p == 0)
							{
								D = 0;
							}
						}

						if (Mouse::getPosition(window).x > window.getSize().x / 2 + 70 && Mouse::getPosition(window).x < window.getSize().x / 10 + window.getSize().x / 2 + 70 &&
							Mouse::getPosition(window).y>window.getSize().y / 2 + 10 && Mouse::getPosition(window).y < window.getSize().y / 2 + 10 + window.getSize().y / 10)
						{
							deleteAllButton(event, &D);
						}
					}
					if (Mouse::getPosition(window).x > window.getSize().x - 310 && Mouse::getPosition(window).x < window.getSize().x - 10 &&
						Mouse::getPosition(window).y>25 && Mouse::getPosition(window).y < widthDropDownMenu)
					{
						widthDropDownMenu = 385;
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
							currentLocationDropDown(&locCreate, 1, event, &text8, &text10);
						}

						if (Mouse::getPosition(window).x > 50 && Mouse::getPosition(window).x < window.getSize().x - 50 &&
							Mouse::getPosition(window).y>105 && Mouse::getPosition(window).y < 145)
						{
							currentLocationDropDown(&locCreate, 2, event, &text9, &text10);
						}

						if (Mouse::getPosition(window).x > 50 && Mouse::getPosition(window).x < window.getSize().x - 50 &&
							Mouse::getPosition(window).y>145 && Mouse::getPosition(window).y < 185)
						{
							currentLocationDropDown(&locCreate, 3, event, &text11, &text10);
						}

						if (Mouse::getPosition(window).x > 50 && Mouse::getPosition(window).x < window.getSize().x - 50 &&
							Mouse::getPosition(window).y>185 && Mouse::getPosition(window).y < 225)
						{
							currentLocationDropDown(&locCreate, 4, event, &text12, &text10);
						}

						if (Mouse::getPosition(window).x > 50 && Mouse::getPosition(window).x < window.getSize().x - 50 &&
							Mouse::getPosition(window).y>225 && Mouse::getPosition(window).y < 265)
						{
							currentLocationDropDown(&locCreate, 5, event, &text13, &text10);
						}

						if (Mouse::getPosition(window).x > 50 && Mouse::getPosition(window).x < window.getSize().x - 50 &&
							Mouse::getPosition(window).y>265 && Mouse::getPosition(window).y < 305)
						{
							deleteOption(event, &text14, rectangleDDASSA, &D);
						}
						if (Mouse::getPosition(window).x > 50 && Mouse::getPosition(window).x < window.getSize().x - 50 &&
							Mouse::getPosition(window).y>305 && Mouse::getPosition(window).y < 345)
						{
							deleteOption(event, &text14, rectangleDDASSA, &D);
						}

						if (Mouse::getPosition(window).x > 50 && Mouse::getPosition(window).x < window.getSize().x - 50 &&
							Mouse::getPosition(window).y>345 && Mouse::getPosition(window).y < 385)
						{
							deleteOption(event, &text14, rectangleDDASSA, &D);
						}
						window.draw(text6);
						backToMenu(&location, event, &text6);
					}
					else
					{
						widthDropDownMenu = 65;
						window.draw(text6);
						backToMenu(&location, event, &text6);
					}
					break;
				}
				break;
			case 3:
				window.draw(text6);
				backToMenu(&location, event, &text6);
				break;
			case 4:
				window.draw(text6);
				backToMenu(&location, event, &text6);
				break;
			case 5:
				window.close();
				break;
			}

		}
		//cout << Mouse::getPosition(window).x << " " << Mouse::getPosition(window).y << endl;
		window.display();
	}

}