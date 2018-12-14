#include "BulletEntity.h"

BulletEntity::BulletEntity(std::string spriteName, int noOfFrames, float speed) : Entity(spriteName, noOfFrames, speed)
{
}

BulletEntity::~BulletEntity()
{
}

void BulletEntity::Update(Visualisation &viz)
{
	Vector2 pos{ GetPosition() };

	if (GetSide() == ESide::ePlayer)
		pos.y -= m_speed;
	else if (GetSide() == ESide::eEnemy)
		pos.y += m_speed;
	if (pos.y <= -32 || pos.y >= 1000)
		m_alive = false;

	SetPosition(pos);
}

int BulletEntity::Collision(int damage, string collider)
{
	m_alive = false;
	return 0;
}