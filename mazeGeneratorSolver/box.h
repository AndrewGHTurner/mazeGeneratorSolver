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
	void addButton(int width, int height, int topLeftX, int topLeftY, int buttonType, void(*funcptr)());
	void addSlider(int width, int height, int topLeftX, int topLeftY);
	void drawUI();

	

	enum buttonTextureCodes
	{
		endPosReleased = 0,
		endPosPressed = 1,
		startPosReleased = 2,
		startPosPressed = 3
	};
private:
	VertexArray buttonVertices;
	VertexArray sliderVertices;

	Texture buttonTexture;
	RenderStates buttonRenderStates;

	int whichButton(int XCoord, int YCoord);
	int whichSlider(int XCoord, int YCoord);

	int numButtonVertices = 0;
	int numSliderVertices = 0;
	
	vector<int> buttonTypes;
	vector<void(*)()> buttonFunctions;

};