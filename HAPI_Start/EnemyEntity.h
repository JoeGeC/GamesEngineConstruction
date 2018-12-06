#pragma once
#include "Entity.h"


class EnemyEntity : public Entity
{
public:
	EnemyEntity(std::string spriteName, int noOfFrames);
	~EnemyEntity();

	void Update(Visualisation &viz) override final;
	ESide GetSide() const override final { return ESide::eEnemy; };
	int GetDamage() const override final { return 20; };
	void Collision(int damage, string collider);
	
	int GetNextDest() const { return m_nextDest; };
	void SetNextDest() { m_nextDest++; }

private:
	int m_health{ 100 };
	int m_nextDest{ 0 };
};

