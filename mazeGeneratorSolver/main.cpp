#pragma once
#include "box.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;
using namespace sf;

int main()
{
	Box box(1280, 720, "mazeGereratorSolver");

	box.addButton(400, 100, 20, 10, 0);

	box.addButton(400, 100, 400, 400, 0);

	box.setFramerateLimit(10);
	while (box.isOpen())
	{
		Event event;
		while (box.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				box.close();
			}
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				box.mousePress(event.mouseButton.x, event.mouseButton.y);
			}
			else if (event.type == sf::Event::MouseButtonReleased)
			{
				box.mouseRelease(event.mouseButton.x, event.mouseButton.y);
			}
		}
		box.clear();
		box.drawUI();
		box.display();

	}

	return 0;
}