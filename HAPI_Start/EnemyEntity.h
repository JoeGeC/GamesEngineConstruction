#pragma once
#include "Entity.h"
class EnemyEntity : public Entity
{
public:
	EnemyEntity(std::string spriteName);
	~EnemyEntity();

	void Update() override final;
	ESide GetSide() const override final { return ESide::eEnemy; };
};

