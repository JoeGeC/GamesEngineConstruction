#pragma once
#include <HAPI_lib.h>

using namespace HAPISPACE;

class Screen
{
public:
	Screen();
	~Screen();
	void ClearToColour(BYTE *screenPointer, HAPI_TColour colour);
	int GetScreenWidth();
	int GetScreenHeight();

private:
	int screenWidth{ 1000 };
	int screenHeight{ 720 };
};

