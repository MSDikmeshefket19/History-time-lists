#include<SFML/Graphics.hpp> 
#include <iostream>
using namespace std;
using namespace sf;
int main()
{
	int location = 0;
	RenderWindow window(VideoMode(1000, 800), "Helpopedia");

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		window.display();
	}
	return 0;
}