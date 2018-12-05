#pragma once
#include <string>
#include <HAPI_lib.h>
#include <unordered_map>
#include "Rectangle.h"
using namespace HAPISPACE;

class Sprite
{
public:
	Sprite(bool alpha, int noOfFrames) : m_isAlpha(alpha), m_noOfFrames(noOfFrames) {};
	~Sprite();
	bool LoadTexture(std::string fileName);
	void Blit(BYTE *screen, Rectangle &clippedRect, int screenWidth, int posX, int posY, int frameNo); // no alpha
	void BlitAlpha(BYTE *screen, Rectangle &clippedRect, int screenWidth, int posX, int posY, int frameNo); // alpha
	void Animate();
	Rectangle CreateRectangle();

	int GetTextureWidth() const { return m_textureWidth; }
	int GetTextureHeight() const { return m_textureHeight; }
	//int GetFrameNo() const { return m_frameNo; }
	bool IsAlpha() const { return m_isAlpha; }

	//void SetFrameNo(int frameNo) { m_frameNo = frameNo; }

private:
	int m_textureWidth;
	int m_textureHeight;
	BYTE *m_textureData{ nullptr };
	bool m_isAlpha;
	int m_noOfFrames;
	DWORD lastFrameUpdateTime{ 0 };
	//int m_frameNo{ 0 };
};

