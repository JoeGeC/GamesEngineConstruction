#pragma once
#include <vector>
#include "EnemyEntity.h"
#include "Vector2.h"

class Wave
{
public:
	Wave(Vector2 startPoint);
	~Wave();
	void SpawnEnemy(int i);
	void PopulateRoute(Vector2 point);
	void PopulateEnemies(EnemyEntity* enemy);
	void FollowRoute(Vector2 playerPos);

	int GetNextEnemy() const { return m_nextEnemy; }

private:
	Vector2 m_startPoint;
	vector<Vector2> m_route;
	vector<EnemyEntity*> m_enemies;
	int m_nextEnemy{ 0 };

};

