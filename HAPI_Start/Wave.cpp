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
	enemy->SetNextDest(m_route[0]);
}

void Wave::FollowRoute()
{
	for (auto e : m_enemies)
	{
		if (e->IsAlive())
		{
			//checks to see if enemy is at the nextdest
			if (e->GetPosition().x >= m_route[e->GetNextDestId()].x - 1 && e->GetPosition().x <= m_route[e->GetNextDestId()].x + 1 && e->GetPosition().y >= m_route[e->GetNextDestId()].y - 1 && e->GetPosition().y <= m_route[e->GetNextDestId()].y + 1)
			{
				if (e->GetNextDestId() == m_route.size() - 1)
				{
					//if at last dest in route
					e->SetNextDestId(-((int)m_route.size()));
				}
				e->SetNextDestId(1);
				e->SetNextDest(m_route[e->GetNextDestId()]);
			}
			e->MoveToDest(m_route[e->GetNextDestId()]);
		}
	}
}

void Wave::SpawnEnemy(int i)
{
	if (m_enemies.size() > i)
	{
		m_enemies[i]->SetAlive(true);
		m_enemies[i]->SetPosition(m_startPoint);
		m_nextEnemy++;
	}
}