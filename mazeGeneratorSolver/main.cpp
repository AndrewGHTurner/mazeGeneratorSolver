
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;
using namespace sf;


int tileSize = 60;

int tilesInViewX = 10;
int tilesInViewY = 10;




int main()
{
	

	



	RenderWindow window(VideoMode(tileSize * (tilesInViewX - 1), tileSize * (tilesInViewY - 1)), "SFML works!");

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}


			window.display();
		}

	}

	return 0;
}