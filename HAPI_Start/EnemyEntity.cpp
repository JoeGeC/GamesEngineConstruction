#include "EnemyEntity.h"
#include <math.h>

EnemyEntity::EnemyEntity(std::string spriteName, int noOfFrames, Vector2 startPos, float speed, int score, int health, EType type) : Entity(spriteName, noOfFrames, startPos, speed)
{
	m_score = score;
	m_maxHealth = health;
	m_currentHealth = health;
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
		m_currentHealth -= damage;

	if (m_currentHealth <= 0)
	{
		m_alive = false;
		return m_score;
	}
	else
		return 0;
}

