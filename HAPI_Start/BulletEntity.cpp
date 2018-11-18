#include "BulletEntity.h"

BulletEntity::BulletEntity(std::string spriteName) : Entity(spriteName)
{
}

BulletEntity::~BulletEntity()
{
}

void BulletEntity::Update()
{
	if (GetSide() == ESide::ePlayer)
		m_position.y -= speed;
	else if (GetSide() == ESide::eEnemy)
		m_position.y += speed;

	if (m_position.y <= -32 || m_position.y >= 1000)
		m_alive = false;
}