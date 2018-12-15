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

void Wave::FollowRoute(Vector2 playerPos)
{
	for (auto e : m_enemies)
	{
		e->SetNextDest(m_route[e->GetNextDestId()]);
		if (e->IsAlive())
		{
			if (e->GetType() == EType::eShooter)
			{
				float speed = e->GetSpeed();
				int nextDestId = e->GetNextDestId();
				Vector2 pos = e->GetPosition();
				//checks to see if enemy is at the nextdest
				if (pos.x >= m_route[nextDestId].x - speed && pos.x <= m_route[nextDestId].x + speed && pos.y >= m_route[nextDestId].y - speed && pos.y <= m_route[nextDestId].y + speed)
				{
					if (nextDestId == m_route.size() - 1)
					{
						//if at last dest in route
						e->IncrementNextDestId(-((int)m_route.size()));
					}
					e->IncrementNextDestId(1);
					e->SetNextDest(m_route[e->GetNextDestId()]);
				}
				e->MoveToDest(m_route[nextDestId]);
			}
			else if (e->GetType() == EType::eKamikaze)
			{
				e->SetNextDest(playerPos);
			}
		}
	}
}

void Wave::SpawnEnemy(int i)
{
	if (m_enemies.size() > i)
	{
		m_enemies[i]->SetAlive(true);
		m_enemies[i]->SetExploded(false);
		m_enemies[i]->SetPosition(m_startPoint);
		m_nextEnemy++;
	}
}