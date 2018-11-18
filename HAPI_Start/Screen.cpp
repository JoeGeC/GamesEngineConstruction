#include "Screen.h"

Screen::Screen()
{
	if (!HAPI.Initialise(screenWidth, screenHeight, "Bleh", 0))
	{
		return;
	}
}


Screen::~Screen()
{
}

void Screen::ClearToColour(BYTE *screenPointer, HAPI_TColour colour)
{
	//memset(screenPointer, 0, screenWidth * screenHeight * 4);
	HAPI_TColour *tempColour = (HAPI_TColour*)screenPointer;

	for (int i = 0; i < screenHeight * screenWidth; i++)
	{
		*tempColour = colour;
		tempColour++;
	}
}

int Screen::GetScreenHeight()
{
	return screenHeight;
}

int Screen::GetScreenWidth()
{
	return screenWidth;
}