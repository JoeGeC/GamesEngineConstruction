#include "Wave.h"



Wave::Wave(Vector2 startPoint) : m_startPoint(startPoint)
{
}


Wave::~Wave()
{
}

void Wave::PopulateRoute(Vector2 point)
{
	m_route.push_back(point);
}

void Wave::PopulateEnemies(EnemyEntity* enemy)
{
	m_enemies.push_back(enemy);
}

void Wave::FollowRoute()
{
	for (auto e : m_enemies)
	{
		if (e->GetPosition().x == m_route[e->GetNextDest()].x && e->GetPosition().y == m_route[e->GetNextDest()].y)
			e->SetNextDest();
		if(e->IsAlive())
			e->MoveToDest(m_route[e->GetNextDest()]);
	}
}

void Wave::SpawnEnemy(int i)
{
	if (m_enemies.size() >= i)
	{
		m_enemies[i]->SetAlive(true);
		m_enemies[i]->SetPosition(m_startPoint);
	}
}