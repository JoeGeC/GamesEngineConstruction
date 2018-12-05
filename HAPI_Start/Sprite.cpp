#include "Sprite.h"

Sprite::~Sprite()
{
	delete[] m_textureData;
}

Rectangle Sprite::CreateRectangle()
{
	Rectangle spriteRect(m_textureWidth / m_noOfFrames, m_textureHeight);
	return spriteRect;
}

bool Sprite::LoadTexture(std::string fileName)
{
	if (!HAPI.LoadTexture(fileName, &m_textureData, m_textureWidth, m_textureHeight))
	{
		HAPI.UserMessage(fileName + " not found!", "Error");
		return false;
	}
	return true;
}

void Sprite::Blit(BYTE *screenPnter, Rectangle &clippedRect, int screenWidth, int posX, int posY, int frameNo)
{
	//Animate();

	clippedRect.Translate(frameNo * (m_textureWidth / m_noOfFrames), 0);
	BYTE *texturePnter = m_textureData + (clippedRect.m_left + clippedRect.m_top * m_textureWidth) * 4;
	screenPnter += (posX + posY * screenWidth) * 4;

	for (int y = 0; y < clippedRect.Height(); y++)
	{
		memcpy(screenPnter, texturePnter, clippedRect.Width() * 4);
				
		screenPnter += screenWidth * 4; // Move screen pointer to next line
		texturePnter += m_textureWidth * 4; // Move texture pointer to next line
		
	}
}

void Sprite::BlitAlpha(BYTE *screenPnter, Rectangle &clippedRect, int screenWidth, int posX, int posY, int frameNo)
{
	//Animate();

	clippedRect.Translate(frameNo * (m_textureWidth / m_noOfFrames), 0);
	BYTE *texturePnter = m_textureData + (clippedRect.m_left + clippedRect.m_top * m_textureWidth) * 4;
	screenPnter += (posX + posY * screenWidth) * 4;

	int endOfLinescreenIncrement = (screenWidth - clippedRect.Width()) * 4;
	for (int y = 0; y < clippedRect.Height(); y++)
	{
		for (int x = 0; x < clippedRect.Width(); x++)
		{
			BYTE alpha = texturePnter[3];

			if (alpha == 255)
			{
				memcpy(screenPnter, texturePnter, 4);
			}
			else if (alpha > 0)
			{
				BYTE blue = texturePnter[0];
				BYTE green = texturePnter[1];
				BYTE red = texturePnter[2];

				screenPnter[0] = screenPnter[0] + ((alpha * (blue - screenPnter[0])) >> 8);
				screenPnter[1] = screenPnter[1] + ((alpha * (green - screenPnter[1])) >> 8);
				screenPnter[2] = screenPnter[2] + ((alpha * (red - screenPnter[2])) >> 8);
			}

			texturePnter += 4;
			screenPnter += 4;
		}

		screenPnter += endOfLinescreenIncrement;
		texturePnter += (m_textureWidth - clippedRect.Width()) * 4;
	}
}

//void Sprite::Animate()
//{
//	//animation time
//	DWORD time = HAPI.GetTime();
//	if (time - lastFrameUpdateTime > 150)
//	{
//		m_frameNo++;
//		lastFrameUpdateTime = time;
//	}
//	if (m_frameNo > m_noOfFrames - 1)
//		m_frameNo = 0;
//}