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
	void CreateWave(Vector2 startPoint, std::vector<EnemyEntity*> enemies, std::vector<Vector2> route);
	void Update(Vector2 playerPos);

	int GetNextWave() const { return m_nextWave; }
	size_t GetSizeOfWaves() const { return m_waves.size(); }
	std::vector<Wave*> GetWaves() const { return m_waves; }

	void SetNextWave(int nextWave) { m_nextWave = nextWave; }
	void SetTimeSinceLastWave(DWORD time) { m_timeSinceLastWave = time; }

private:
	int m_nextWave{ 0 };
	std::vector<Wave*> m_waves;
	DWORD m_timeSinceLastSpawn{ 0 };
	DWORD m_timeSinceLastWave{ 0 };
};

