#include<SFML/Graphics.hpp> 
#include <iostream>
#include<windows.h>
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


void backToMenuFromCreate(int* ptr1, Event event, Text* textOne,Text* textTwo,int* ptr2)
{
	if (Mouse::getPosition(window).x > 0 && Mouse::getPosition(window).x < (*textOne).getCharacterSize() * 2.25 && Mouse::getPosition(window).y>770 && Mouse::getPosition(window).y < 800)
	{
		(*textOne).setFillColor(Color::White);
		if (event.type == Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == Mouse::Left)
			{
				*ptr1 = 0;
				*ptr2 = 0;
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
void currentLocationDropDown(int* ptr, int n, Event event, Text* textOne,Text* textTwo)
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
	(*rectangle).setPosition(50, posY);
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
	(*text).setPosition(window.getSize().x / 2 - 50, posY);
	(*text).setFillColor(Color::White);
}
int main()
{
	int location = 0, locCreate = 0;
	Texture tex1, tex2;
	Sprite s1(tex1), s2(tex2);
	Font f1;
	f1.loadFromFile("Pacifico-Regular.ttf");

	Text text1, text2, text3, text4, text5, text, text6, text7, text8, text9, text10;

	text1.setFont(f1);
	setMenuText("Events", &text1, 50, 500);

	text2.setFont(f1);
	setMenuText("Create", &text2, 50, 550);

	text3.setFont(f1);
	setMenuText("Game", &text3, 55, 600);

	text4.setFont(f1);
	setMenuText("About us", &text4, 65, 650);

	text5.setFont(f1);
	setMenuText("Quit", &text5, 50, 700);

	text6.setString("Back");
	text6.setFont(f1);
	text6.setCharacterSize(30);
	text6.setPosition(0, 770);
	text6.setFillColor(Color::Color(210, 210, 210, 255));

	text7.setString("Create");
	text7.setFont(f1);
	setDropDownMenuText(&text7, 100);

	text8.setString("Delete");
	text8.setFont(f1);
	setDropDownMenuText(&text8, 140);

	text9.setString("Stas");
	text9.setFont(f1);
	setDropDownMenuText(&text9, 180);

	text10.setString("Choose one:");
	text10.setFont(f1);
	setDropDownMenuText(&text10, 60);

	tex1.loadFromFile("Logo.png");
	tex2.loadFromFile("Screenshot 2022-01-30 180704_auto_x2-modified.png");

	int fu1 = 90;

	RectangleShape rectangle(Vector2f(900, 450)), rectangle1(Vector2f(300, 250)),
		rectangle2(Vector2f(200, 250)), rectangle3(Vector2f(200, 250)),
		rectangle4(Vector2f(140, 250)), rectangle5(Vector2f(window.getSize().x - 100, 40)),
		rectangle7(Vector2f(window.getSize().x - 100, 40)), rectangle8(Vector2f(window.getSize().x - 100, 40)), rectangle9(Vector2f(window.getSize().x - 100, 40));

	setRectangleEventsTab(&rectangle, 50, 50);
	setRectangleEventsTab(&rectangle1, 50, 520);
	setRectangleEventsTab(&rectangle2, 370, 520);
	setRectangleEventsTab(&rectangle3, 590, 520);
	setRectangleEventsTab(&rectangle4, 810, 520);

	rectangle5.setFillColor(Color::Color(150, 150, 150, 255));
	rectangle5.setPosition(50, 50);

	setRectangleDropDown(&rectangle7, 90);
	setRectangleDropDown(&rectangle8, 130);
	setRectangleDropDown(&rectangle9, 170);

	s1.setTextureRect(IntRect(10, 10, 486, 500));
	s2.setTextureRect(IntRect(10, 10, 1300, 1300));
	s1.setPosition(window.getSize().x / 2 - tex1.getSize().x / 2, 0);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		window.clear(Color(210, 210, 210, 255));
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
			switch (location)
			{
			case 1:
				backToMenu(&location, event, &text6);
				window.draw(rectangle);
				window.draw(rectangle1);
				window.draw(rectangle2);
				window.draw(rectangle3);
				window.draw(rectangle4);
				window.draw(text6);
				break;
			case 2:
				window.draw(rectangle5);
				window.draw(text10);
				if (Mouse::getPosition(window).x > 50 && Mouse::getPosition(window).x < window.getSize().x - 50 &&
					Mouse::getPosition(window).y>50 && Mouse::getPosition(window).y < fu1)
				{
					fu1 = 210;
					dropDown(&rectangle7, 90, 130);
					dropDown(&rectangle8, 130, 170);
					dropDown(&rectangle9, 170, 210);
					window.draw(rectangle7);
					window.draw(rectangle8);
					window.draw(rectangle9);
					window.draw(text7);
					window.draw(text8);
					window.draw(text9);
					if (Mouse::getPosition(window).x > 50 && Mouse::getPosition(window).x < window.getSize().x - 50 &&
						Mouse::getPosition(window).y>90 && Mouse::getPosition(window).y < window.getSize().x - 130)
					{
						currentLocationDropDown(&locCreate, 1, event, &text7,&text10);
					}

					if (Mouse::getPosition(window).x > 50 && Mouse::getPosition(window).x < window.getSize().x - 50 &&
						Mouse::getPosition(window).y>130 && Mouse::getPosition(window).y < window.getSize().x - 170)
					{
						currentLocationDropDown(&locCreate, 2, event, &text8, &text10);
					}

					if (Mouse::getPosition(window).x > 50 && Mouse::getPosition(window).x < window.getSize().x - 50 &&
						Mouse::getPosition(window).y>170 && Mouse::getPosition(window).y < window.getSize().x - 210)
					{
						currentLocationDropDown(&locCreate, 3, event, &text9, &text10);
					}
					switch (locCreate)
					{
					case 1:
						window.draw(rectangle1);
						break;
					case 2:
						window.draw(rectangle2);
						break;
					case 3:
						window.draw(rectangle3);
						break;
					}
					
				}
				else
				{
					fu1 = 90;
					switch (locCreate)
					{
					case 1:
						window.draw(rectangle1);
						break;
					case 2:
						window.draw(rectangle2);
						break;
					case 3:
						window.draw(rectangle3);
						break;
					}
				}
				window.draw(text6);
				backToMenuFromCreate(&location, event, &text6,&text10,&locCreate);
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
		cout << Mouse::getPosition(window).y << " " << text1.getCharacterSize() << endl;
		window.display();
	}
	return 0;
}