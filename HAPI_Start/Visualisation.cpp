#include "Visualisation.h"

Visualisation::Visualisation()
{
}

Visualisation::~Visualisation()
{
}

bool Visualisation::Initialise(int width, int height)
{
	if (!HAPI.Initialise(width, height, "Bleh", 0))
	{
		std::cerr << "Could not init" << std::endl;
		return false;
	}
	
	m_screenRect = Rectangle(width, height);

	m_screenPnter = HAPI.GetScreenPointer();

	return true;
}

bool Visualisation::CreateSprite(std::string name, std::string fileName, bool isAlpha, int noOfFrames)
{
	Sprite *newSprite = new Sprite(isAlpha, noOfFrames);
	if (!newSprite->LoadTexture(fileName))
		return false;
	m_spriteMap[name] = newSprite; // populate sprite map
	return true;
}

void Visualisation::RenderSprite(const std::string& name, int posX, int posY, bool isAlpha, int frameNo)
{
	if (m_spriteMap.find(name) == m_spriteMap.end())
	{
		HAPI.UserMessage("Render sprite","Error");
		HAPI.Close();
	}

	//create sprite rectangle
	Rectangle spriteRect = m_spriteMap.at(name)->CreateRectangle();

	//doesn't blit if completely off screen
	if (posX + spriteRect.m_right < 0 || posX > m_screenRect.Width() || posY + spriteRect.m_bottom < 0 || posY > m_screenRect.Height())
		return;

	//translate to screen space
	spriteRect.Translate(posX, posY);
	//do the clipping
	spriteRect.ClipTo(m_screenRect);
	//translate back into source space
	spriteRect.Translate(-posX, -posY);
	
	//clamps to screen if off
	if (posX < 0)
		posX = 0;
	if (posY < 0)
		posY = 0;

	//blit sprite
	if (m_spriteMap.at(name)->IsAlpha())
		m_spriteMap.at(name)->BlitAlpha(m_screenPnter, spriteRect, m_screenRect.Width(), posX, posY, frameNo);
	else
		m_spriteMap.at(name)->Blit(m_screenPnter, spriteRect, m_screenRect.Width() , posX, posY, frameNo);
}

void Visualisation::ClearToGrey(int colour)
{
	memset(m_screenPnter, colour, m_screenRect.Width() * m_screenRect.Width() * 4);
}

void Visualisation::ClearToColour(HAPI_TColour colour)
{
	HAPI_TColour *tempColour = (HAPI_TColour*)m_screenPnter;

	for (int i = 0; i < m_screenRect.Width() * m_screenRect.Width(); i++)
	{
		*tempColour = colour;
		tempColour++;
	}
}

int Visualisation::GetScreenHeight() const
{
	return m_screenRect.Width();
}

int Visualisation::GetScreenWidth() const
{
	return m_screenRect.Width();
}

std::unordered_map<std::string, Sprite*> Visualisation::GetSpriteCollection() const
{
	return m_spriteMap;
}