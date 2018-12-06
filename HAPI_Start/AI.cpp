#include "AI.h"

AI::AI()
{

}


AI::~AI()
{
}

void AI::CreateWave(Vector2 startPoint, vector<EnemyEntity*> enemies, vector<Vector2> route)
{
	Wave newWave(startPoint);
	for (auto i : route)
		newWave.PopulateRoute(i);
	for (auto i : enemies)
		newWave.PopulateEnemies(i);
	m_waves.push_back(newWave);
}

void AI::SpawnEnemy()
{
	DWORD time = HAPI.GetTime();
	if (time - m_timeSinceLastSpawn >= 3000)
	{
		if (m_nextWave < m_waves.size())
		{
			m_waves[m_nextWave].SpawnEnemy(m_waves[m_nextWave].GetNextEnemy());
			m_timeSinceLastSpawn = time;
		}
		
	}
}