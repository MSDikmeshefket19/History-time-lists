#include<SFML/Graphics.hpp> 
#include <iostream>
#include<windows.h>
using namespace std;
using namespace sf;

void backToMenu(int* ptr1, Event event, Text* textOne)
{
	if (Mouse::getPosition().x > 470 && Mouse::getPosition().x < 530 && Mouse::getPosition().y>950 && Mouse::getPosition().y < 975)
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
int main()
{
	int location = 0;
	RenderWindow window(VideoMode(1000, 800), "Helpopedia");
	Texture tex1, tex2;
	Sprite s1(tex1), s2(tex2);
	Font f1;
	f1.loadFromFile("Pacifico-Regular.ttf");

	Text text1, text2, text3, text4, text5, text, text6;
	text1.setFont(f1);
	text1.setCharacterSize(40);
	text1.setString("Events");
	text1.setPosition(window.getSize().x / 2 - 50, 500);
	text1.setFillColor(Color::Black);

	text2.setFont(f1);
	text2.setCharacterSize(40);
	text2.setString("Create");
	text2.setPosition(window.getSize().x / 2 - 50, 550);
	text2.setFillColor(Color::Black);

	text3.setFont(f1);
	text3.setCharacterSize(40);
	text3.setString("Game");
	text3.setPosition(window.getSize().x / 2 - 55, 600);
	text3.setFillColor(Color::Black);

	text4.setFont(f1);
	text4.setCharacterSize(40);
	text4.setString("About us");
	text4.setPosition(window.getSize().x / 2 - 65, 650);
	text4.setFillColor(Color::Black);

	text5.setFont(f1);
	text5.setCharacterSize(40);
	text5.setString("Quit");
	text5.setPosition(window.getSize().x / 2 - 50, 700);
	text5.setFillColor(Color::Black);

	text6.setFont(f1);
	text6.setCharacterSize(30);
	text6.setString("Back");
	text6.setPosition(0, 770);
	text6.setFillColor(Color::Color(210, 210, 210, 255));

	tex1.loadFromFile("Logo.png");
	tex2.loadFromFile("Screenshot 2022-01-30 180704_auto_x2-modified.png");


	RectangleShape rectangle(Vector2f(900, 450));
	rectangle.setFillColor(Color::Black);
	rectangle.setPosition(50, 50);

	RectangleShape rectangle1(Vector2f(300, 250));
	rectangle1.setFillColor(Color::Black);
	rectangle1.setPosition(50, 520);

	RectangleShape rectangle2(Vector2f(200, 250));
	rectangle2.setFillColor(Color::Black);
	rectangle2.setPosition(370, 520);

	RectangleShape rectangle3(Vector2f(200, 250));
	rectangle3.setFillColor(Color::Black);
	rectangle3.setPosition(590, 520);

	RectangleShape rectangle4(Vector2f(140, 250));
	rectangle4.setFillColor(Color::Black);
	rectangle4.setPosition(810, 520);

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

			//text1
			if (Mouse::getPosition().x > 915 && Mouse::getPosition().x < 1025 && Mouse::getPosition().y>685 && Mouse::getPosition().y < 715)
			{
				currentLocation(&location, 1, event, &text1);
			}
			else
			{
				text1.setFillColor(Color::Black);
			}

			//text2
			if (Mouse::getPosition().x > 915 && Mouse::getPosition().x < 1025 && Mouse::getPosition().y>730 && Mouse::getPosition().y < 765)
			{
				currentLocation(&location, 2, event, &text2);
			}
			else
			{
				text2.setFillColor(Color::Black);
			}

			//text3
			if (Mouse::getPosition().x > 915 && Mouse::getPosition().x < 1025 && Mouse::getPosition().y>785 && Mouse::getPosition().y < 820)
			{
				currentLocation(&location, 3, event, &text3);
			}
			else
			{
				text3.setFillColor(Color::Black);
			}

			//text4
			if (Mouse::getPosition().x > 895 && Mouse::getPosition().x < 1040 && Mouse::getPosition().y>830 && Mouse::getPosition().y < 870)
			{
				currentLocation(&location, 4, event, &text4);
			}
			else
			{
				text4.setFillColor(Color::Black);
			}

			//text5
			if (Mouse::getPosition().x > 910 && Mouse::getPosition().x < 1015 && Mouse::getPosition().y>880 && Mouse::getPosition().y < 920)
			{
				currentLocation(&location, 5, event, &text5);
			}
			else
			{
				text5.setFillColor(Color::Black);
			}
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
				window.draw(text6);
				backToMenu(&location, event, &text6);
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
				window.draw(text6);
				backToMenu(&location, event, &text6);
				break;
			}
		}
		window.display();
	}
	return 0;
}