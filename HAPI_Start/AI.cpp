#include "AI.h"

AI::AI()
{

}


AI::~AI()
{
}

void AI::Update(Vector2 playerPos)
{
	for (auto i : m_waves)
	{
		i->FollowRoute(playerPos);
	}
	
	DWORD time = HAPI.GetTime();

	if (time - m_timeSinceLastWave >= 15000)
	{
		m_nextWave++;
		m_timeSinceLastWave = time;
	}
}

void AI::CreateWave(Vector2 startPoint, vector<EnemyEntity*> enemies, vector<Vector2> route)
{
	Wave *newWave = new Wave(startPoint);
	for (auto& i : route)
		newWave->PopulateRoute(i);
	for (auto& i : enemies)
		newWave->PopulateEnemies(i);
	m_waves.push_back(newWave);
}

void AI::SpawnEnemy()
{
	DWORD time = HAPI.GetTime();
	if (time - m_timeSinceLastSpawn >= 1000)
	{
		if (m_nextWave < m_waves.size())
		{
			m_waves[m_nextWave]->SpawnEnemy(m_waves[m_nextWave]->GetNextEnemy());
			m_timeSinceLastSpawn = time;
		}
		
	}
}