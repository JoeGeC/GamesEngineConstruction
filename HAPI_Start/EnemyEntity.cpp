#include "EnemyEntity.h"
#include <math.h>

EnemyEntity::EnemyEntity(std::string spriteName, int noOfFrames, float speed, int score, int health, EType type) : Entity(spriteName, noOfFrames, speed)
{
	m_score = score;
	m_health = health;
	m_type = type;
}

EnemyEntity::~EnemyEntity()
{
}

void EnemyEntity::Update(Visualisation &viz)
{
	MoveToDest(m_nextDest);
}

int EnemyEntity::Collision(int damage, string collider)
{
	if (collider == "player")
		m_alive = false;
	else
		m_health -= damage;

	if (m_health <= 0)
	{
		m_alive = false;
		return m_score;
	}
	else
		return 0;
}

