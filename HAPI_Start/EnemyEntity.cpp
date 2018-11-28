#include "EnemyEntity.h"


EnemyEntity::EnemyEntity(std::string spriteName) : Entity(spriteName)
{
}


EnemyEntity::~EnemyEntity()
{
}

void EnemyEntity::Update()
{
	if (m_health <= 0)
		m_alive = false;

	//m_position.y += m_speed;
}

void EnemyEntity::Collision(int damage, string collider)
{
	if (collider == "player")
		m_alive = false;
	else
		m_health -= damage;
}