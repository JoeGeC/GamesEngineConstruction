#pragma once
#include <HAPI_lib.h>
#include <unordered_map>
#include "Sprite.h"
#include "Rectangle.h"

using namespace HAPISPACE;

class Visualisation
{
public:
	Visualisation();
	~Visualisation();
	bool Initialise(int width, int height);
	void ClearToColour(HAPI_TColour colour);
	void ClearToGrey(int colour);
	bool CreateSprite(std::string name, std::string fileName, bool isAlpha, int noOfFrames);
	void RenderSprite(const std::string& name, int posX, int posY, bool isAlpha);

	int GetScreenWidth() const;
	int GetScreenHeight() const;
	std::unordered_map<std::string, Sprite*> GetSpriteCollection() const;
	
private:
	BYTE* m_screenPnter{ nullptr };
	std::unordered_map<std::string, Sprite*> m_spriteMap;
	Rectangle m_screenRect;
};

