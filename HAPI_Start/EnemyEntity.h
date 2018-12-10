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
	
	int GetNextDestId() const { return m_nextDestId; };
	void SetNextDestId(int i) { m_nextDestId += i; }
	void SetNextDest(Vector2 nextDest) { m_nextDest = nextDest; }


private:
	int m_health{ 100 };
	Vector2 m_nextDest;
	int m_nextDestId{ 0 };
};

