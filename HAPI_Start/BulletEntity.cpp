#include "BulletEntity.h"

BulletEntity::BulletEntity(std::string spriteName, int noOfFrames) : Entity(spriteName, noOfFrames)
{
}

BulletEntity::~BulletEntity()
{
}

void BulletEntity::Update(Visualisation &viz)
{
	if (GetSide() == ESide::ePlayer)
		m_position.y -= m_speed;
	else if (GetSide() == ESide::eEnemy)
		m_position.y += m_speed;

	if (m_position.y <= -32 || m_position.y >= 1000)
		m_alive = false;
}

void BulletEntity::Collision(int damage, string collider)
{
	m_alive = false;
}