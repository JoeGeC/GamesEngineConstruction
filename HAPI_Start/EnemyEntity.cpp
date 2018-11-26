#include "EnemyEntity.h"


EnemyEntity::EnemyEntity(std::string spriteName) : Entity(spriteName)
{
}


EnemyEntity::~EnemyEntity()
{
}

void EnemyEntity::Update()
{
	m_position.y++;
}