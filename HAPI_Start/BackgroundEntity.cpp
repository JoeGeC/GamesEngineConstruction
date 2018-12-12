#include "BackgroundEntity.h"

BackgroundEntity::BackgroundEntity(std::string spriteName, int noOfFrames) : Entity(spriteName, noOfFrames)
{
}

BackgroundEntity::~BackgroundEntity()
{
}

void BackgroundEntity::Update(Visualisation &viz)
{
	Vector2 pos{ GetPosition() };

	//move background
	pos.y += m_speed;
	if (pos.y >= 1000)
		pos.y -= 2000;

	SetPosition(pos);
}
