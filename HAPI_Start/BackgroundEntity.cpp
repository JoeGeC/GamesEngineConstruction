#include "BackgroundEntity.h"



BackgroundEntity::BackgroundEntity(std::string spriteName) : Entity(spriteName)
{
}


BackgroundEntity::~BackgroundEntity()
{
}

void BackgroundEntity::Update(Visualisation &viz)
{
	//move background
	m_position.y += m_speed;
	if (m_position.y >= 1000)
		m_position.y -= 2000;
}
