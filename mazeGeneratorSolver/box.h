#pragma once
#include <vector>

#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

class Box : public RenderWindow
{
	//using RenderWindow::RenderWindow;
public:
	Box(int width, int height, String title);
	void mousePress(int XCoord, int YCoord);
	void mouseRelease(int XCoord, int YCoord);
	void addButton(int width, int height, int topLeftX, int topLeftY, int buttonType);
	void drawUI();

	int whichButton(int XCoord, int YCoord);
private:
	VertexArray buttonVertices;

	Texture buttonTexture;
	RenderStates buttonRenderStates;

	enum buttonTextureCodes
	{
		startPosReleased = 0,
		startPosPressed = 1
	};

	int numButtonVertices = 0;
	
	vector<int> buttonTypes;

};