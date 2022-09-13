#include "box.h"

Box::Box(int width, int height, String title) : RenderWindow(VideoMode(width, height), title)
{
	buttonVertices.setPrimitiveType(Quads);
	sliderVertices.setPrimitiveType(Quads);
	if (!buttonTexture.loadFromFile("buttons.png"))
	{
		cout << "could not load texture for buttons\n";
	}
	
	buttonRenderStates.texture = &buttonTexture;
}
void Box::addSlider(int width, int height, int topLeftX, int topLeftY)
{
	numSliderVertices += 8;
	sliderVertices.resize(numSliderVertices);
	//vertices for the range bar
	sliderVertices[numSliderVertices - 8].position = Vector2f(topLeftX, topLeftY + ((2.f / 5) * height));
	sliderVertices[numSliderVertices - 7].position = Vector2f(topLeftX + width, topLeftY + ((2.f / 5) * height));
	sliderVertices[numSliderVertices - 6].position = Vector2f(topLeftX + width, topLeftY + ((3.f / 5) * height));
	sliderVertices[numSliderVertices - 5].position = Vector2f(topLeftX, topLeftY + ((3.f / 5) * height));
	sliderVertices[numSliderVertices - 8].color = Color::Green;
	sliderVertices[numSliderVertices - 7].color = Color::Green;
	sliderVertices[numSliderVertices - 6].color = Color::Green;
	sliderVertices[numSliderVertices - 5].color = Color::Green;
	//vertices for the thumb
	sliderVertices[numSliderVertices - 4].position = Vector2f(topLeftX + ((4.5/10) * width), topLeftY);
	sliderVertices[numSliderVertices - 3].position = Vector2f(topLeftX + ((5.5 / 10) * width), topLeftY);
	sliderVertices[numSliderVertices - 2].position = Vector2f(topLeftX + ((5.5 / 10) * width), topLeftY + height);
	sliderVertices[numSliderVertices - 1].position = Vector2f(topLeftX + ((4.5 / 10) * width), topLeftY + height);
	sliderVertices[numSliderVertices - 4].color = Color::Magenta;
	sliderVertices[numSliderVertices - 3].color = Color::Magenta;
	sliderVertices[numSliderVertices - 2].color = Color::Magenta;
	sliderVertices[numSliderVertices - 1].color = Color::Magenta;
}
void Box::addButton(int width, int height, int topLeftX, int topLeftY, int buttonType, void(*funcptr)())
{
	numButtonVertices += 4;
	buttonTypes.push_back(buttonType);
	buttonFunctions.push_back(funcptr);
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
	int buttonVertexIndex = 0;
	while (buttonVertexIndex < numButtonVertices)
	{
		if ((XCoord > buttonVertices[buttonVertexIndex].position.x) && (YCoord > buttonVertices[buttonVertexIndex].position.y))//below and to the right of top left courner of button
		{
			if ((XCoord < buttonVertices[buttonVertexIndex + 2].position.x) && (YCoord < buttonVertices[buttonVertexIndex + 2].position.y))//above and to the left of the bottom right
			{
				cout << "BUTTON PRESSED!\n";
				return buttonVertexIndex / 4;
			}
		}
		buttonVertexIndex += 4;
	}
	return -1;//no button intersected
}

int Box::whichSlider(int XCoord, int YCoord)
{
	int sliderVertexIndex = 0;
	while (sliderVertexIndex < numSliderVertices)
	{
		if ((XCoord > sliderVertices[sliderVertexIndex + 4].position.x) && (YCoord > sliderVertices[sliderVertexIndex + 4].position.y))
		{
			if ((XCoord < sliderVertices[sliderVertexIndex + 6].position.x) && (YCoord < sliderVertices[sliderVertexIndex + 6].position.y))
			{
				cout << "Slider clicked\n";
				return sliderVertexIndex / 8;
			}
		}
		sliderVertexIndex += 8;
	}
}

void Box::mousePress(int XCoord, int YCoord)
{
	int buttonIndex = whichButton(XCoord, YCoord);
	if (buttonIndex != -1)
	{
		if (buttonTypes[buttonIndex] == buttonTextureCodes::startPosReleased)
		{
			int topYTextureCoord = buttonTextureCodes::startPosPressed * 75;//YCoord of the top of the texture rect in the texture sheet
			buttonVertices[(4 * buttonIndex)].texCoords = Vector2f(0, topYTextureCoord);
			buttonVertices[(4 * buttonIndex) + 1].texCoords = Vector2f(300, topYTextureCoord);
			buttonVertices[(4 * buttonIndex) + 2].texCoords = Vector2f(300, topYTextureCoord + 75);
			buttonVertices[(4 * buttonIndex) + 3].texCoords = Vector2f(0, topYTextureCoord + 75);
			buttonTypes[buttonIndex] = buttonTextureCodes::startPosPressed;
		}
		else if (buttonTypes[buttonIndex] == buttonTextureCodes::endPosReleased)
		{
			int topYTextureCoord = buttonTextureCodes::endPosPressed * 75;//YCoord of the top of the texture rect in the texture sheet
			buttonVertices[(4 * buttonIndex)].texCoords = Vector2f(0, topYTextureCoord);
			buttonVertices[(4 * buttonIndex) + 1].texCoords = Vector2f(300, topYTextureCoord);
			buttonVertices[(4 * buttonIndex) + 2].texCoords = Vector2f(300, topYTextureCoord + 75);
			buttonVertices[(4 * buttonIndex) + 3].texCoords = Vector2f(0, topYTextureCoord + 75);
			buttonTypes[buttonIndex] = buttonTextureCodes::endPosPressed;
		}
		(*buttonFunctions[buttonIndex])();//call the function assisiated with the button
	}
	else
	{
		int sliderIndex = whichSlider(XCoord, YCoord);
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
		if (buttonTypes[buttonIndex] == buttonTextureCodes::endPosPressed)
		{
			topYTextureCoord = buttonTextureCodes::endPosReleased * 75;
			buttonVertices[(4 * buttonIndex)].texCoords = Vector2f(0, topYTextureCoord);
			buttonVertices[(4 * buttonIndex) + 1].texCoords = Vector2f(300, topYTextureCoord);
			buttonVertices[(4 * buttonIndex) + 2].texCoords = Vector2f(300, topYTextureCoord + 75);
			buttonVertices[(4 * buttonIndex) + 3].texCoords = Vector2f(0, topYTextureCoord + 75);
			buttonTypes[buttonIndex] = buttonTextureCodes::endPosReleased;
		}
	}
}

void Box::drawUI()
{
	draw(buttonVertices, buttonRenderStates);
	draw(sliderVertices);
}