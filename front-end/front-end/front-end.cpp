#include<SFML/Graphics.hpp> 
#include <iostream>
using namespace std;
using namespace sf;
int main()
{
	int location = 0;
	RenderWindow window(VideoMode(1000, 800), "Helpopedia");
	Texture tex1;
	Sprite s1(tex1);
	Font f1;
	f1.loadFromFile("Pacifico-Regular.ttf");

	Text text1, text2, text3, text4, text5;
	text1.setFont(f1);
	text1.setCharacterSize(40);
	text1.setString("Start");
	text1.setPosition(window.getSize().x / 2 - 50, 500);
	text1.setFillColor(Color::Black);

	text2.setFont(f1);
	text2.setCharacterSize(40);
	text2.setString("Login");
	text2.setPosition(window.getSize().x / 2 - 50, 550);
	text2.setFillColor(Color::Black);

	text3.setFont(f1);
	text3.setCharacterSize(40);
	text3.setString("Rules");
	text3.setPosition(window.getSize().x / 2 - 55, 600);
	text3.setFillColor(Color::Black);

	text4.setFont(f1);
	text4.setCharacterSize(40);
	text4.setString("History");
	text4.setPosition(window.getSize().x / 2 - 65, 650);
	text4.setFillColor(Color::Black);

	text5.setFont(f1);
	text5.setCharacterSize(40);
	text5.setString("Lines");
	text5.setPosition(window.getSize().x / 2 - 50, 700);
	text5.setFillColor(Color::Black);

	tex1.loadFromFile("Logo.png");
	s1.setTextureRect(IntRect(10, 10, 486, 500));
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
		window.draw(s1);
		window.draw(text1);
		window.draw(text2);
		window.draw(text3);
		window.draw(text4);
		window.draw(text5);
		window.display();
	}
	return 0;
}