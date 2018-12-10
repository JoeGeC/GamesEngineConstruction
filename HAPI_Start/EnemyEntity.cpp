#include "EnemyEntity.h"
#include <math.h>

EnemyEntity::EnemyEntity(std::string spriteName, int noOfFrames) : Entity(spriteName, noOfFrames)
{
}


EnemyEntity::~EnemyEntity()
{
}

void EnemyEntity::Update(Visualisation &viz)
{
	if (m_health <= 0)
		m_alive = false;
	MoveToDest(m_nextDest);
}

void EnemyEntity::Collision(int damage, string collider)
{
	if (collider == "player")
		m_alive = false;
	else
		m_health -= damage;
}

