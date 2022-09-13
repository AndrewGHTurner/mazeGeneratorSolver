#include "box.h"

Box::Box(int width, int height, String title) : RenderWindow(VideoMode(width, height), title)
{
	buttonVertices.setPrimitiveType(Quads);
	if (!buttonTexture.loadFromFile("buttons.png"))
	{
		cout << "could not load texture for buttons\n";
	}
	
	buttonRenderStates.texture = &buttonTexture;
}
//button type 0 = set start position released
//button type 1 = set start position pressed
void Box::addButton(int width, int height, int topLeftX, int topLeftY, int buttonType)
{
	numButtonVertices += 4;
	buttonTypes.push_back(buttonType);
	buttonVertices.resize(numButtonVertices);
	cout << "hedllo" << endl;

	buttonVertices[numButtonVertices - 4].position = Vector2f(topLeftX, topLeftY);
	buttonVertices[numButtonVertices - 3].position = Vector2f(topLeftX + width, topLeftY);
	buttonVertices[numButtonVertices - 2].position = Vector2f(topLeftX + width, topLeftY + height);
	buttonVertices[numButtonVertices - 1].position = Vector2f(topLeftX, topLeftY + height);
	//buttons are 75 by 300 
	int topYTextureCoord = buttonType * 75;
	buttonVertices[numButtonVertices - 4].texCoords = Vector2f(0, topYTextureCoord);
	buttonVertices[numButtonVertices - 3].texCoords = Vector2f(300, topYTextureCoord);
	buttonVertices[numButtonVertices - 2].texCoords = Vector2f(300, topYTextureCoord + 75);
	buttonVertices[numButtonVertices - 1].texCoords = Vector2f(0, topYTextureCoord + 75);
	
}

int Box::whichButton(int XCoord, int YCoord)
{
	int buttonIndex = 0;
	while (buttonIndex < numButtonVertices)
	{
		if ((XCoord > buttonVertices[buttonIndex].position.x) && (YCoord > buttonVertices[buttonIndex].position.y))//below and to the right of top left courner of button
		{
			if ((XCoord < buttonVertices[buttonIndex + 2].position.x) && (YCoord < buttonVertices[buttonIndex + 2].position.y))//above and to the left of the bottom right
			{
				cout << "BUTTON PRESSED!\n";
				return buttonIndex / 4;
			}
		}
		buttonIndex += 4;
	}
	return -1;//no button intersected
}

void Box::mousePress(int XCoord, int YCoord)
{
	int buttonIndex = whichButton(XCoord, YCoord);
	if (buttonIndex != -1)
	{
		int topYTextureCoord = buttonTextureCodes::startPosPressed * 75;//YCoord of the top of the texture rect in the texture sheet
		buttonVertices[(4 * buttonIndex)].texCoords = Vector2f(0, topYTextureCoord);
		buttonVertices[(4 * buttonIndex) + 1].texCoords = Vector2f(300, topYTextureCoord);
		buttonVertices[(4 * buttonIndex) + 2].texCoords = Vector2f(300, topYTextureCoord + 75);
		buttonVertices[(4 * buttonIndex) + 3].texCoords = Vector2f(0, topYTextureCoord + 75);
		buttonTypes[buttonIndex] = buttonTextureCodes::startPosPressed;
		
	}
}

void Box::mouseRelease(int XCoord, int YCoord)
{
	int buttonIndex = whichButton(XCoord, YCoord);
	if (buttonIndex != -1)
	{
		int topYTextureCoord = 0;
		if (buttonTypes[buttonIndex] == buttonTextureCodes::startPosPressed)
		{
			topYTextureCoord = buttonTextureCodes::startPosReleased * 75;
			buttonVertices[(4 * buttonIndex)].texCoords = Vector2f(0, topYTextureCoord);
			buttonVertices[(4 * buttonIndex) + 1].texCoords = Vector2f(300, topYTextureCoord);
			buttonVertices[(4 * buttonIndex) + 2].texCoords = Vector2f(300, topYTextureCoord + 75);
			buttonVertices[(4 * buttonIndex) + 3].texCoords = Vector2f(0, topYTextureCoord + 75);
			buttonTypes[buttonIndex] = buttonTextureCodes::startPosReleased;
		}
	}
}

void Box::drawUI()
{
	draw(buttonVertices, buttonRenderStates);
}