#pragma once
#include <vector>
#include "Wave.h"
#include <HAPI_lib.h>

class EnemyEntity;

class AI
{
public:
	AI();
	~AI();
	void SpawnEnemy();
	void CreateWave(Vector2 startPoint, vector<EnemyEntity*> enemies, vector<Vector2> route);

private:
	int m_nextWave{ 0 };
	vector<Wave> m_waves;
	DWORD m_timeSinceLastSpawn{ 0 };
};

