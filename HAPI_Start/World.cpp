#include "World.h"
#include "Visualisation.h"
#include "EnemyEntity.h"
#include "PlayerEntity.h"
#include "BackgroundEntity.h"
#include "BulletEntity.h"

World::World()
{
}


World::~World()
{
	delete m_viz;

	for (auto p : m_entityVector)
		delete p;
}

bool World::LoadLevel()
{
	//load all the sprites
	if(!m_viz->CreateSprite("player", "Data\\spaceship.png", true, 3))
		return false;
	if (!m_viz->CreateSprite("background", "Data\\spaceBackground.png", false, 1))
		return false;
	if (!m_viz->CreateSprite("bullet", "Data\\bullet.png", true, 1))
		return false;
	
	BackgroundEntity *background1 = new BackgroundEntity("background");
	m_entityVector.push_back(background1);
	background1->SetPosition(Vector2(0, 0));

	BackgroundEntity *background2 = new BackgroundEntity("background");
	m_entityVector.push_back(background2);
	background2->SetPosition(Vector2(0, -1000));
	
	for (int i = 0; i < 3; i++)
	{
		BulletEntity *bullet = new BulletEntity("bullet");
		bullet->SetAlive(false);
		m_entityVector.push_back(bullet);
	}

	PlayerEntity *newPlayer = new PlayerEntity("player");
	m_entityVector.push_back(newPlayer);
	newPlayer->SetPosition(Vector2(50, 50));
	
	return true;
}

void World::Update()
{
	while (HAPI.Update())
	{
		HAPI.SetShowFPS(true);

		FireBullet();

		//update what entities are doing
		for (auto p : m_entityVector)
		{
			p->Update();
		}

		//clear screen to black
		m_viz->ClearToGrey(0);

		//render sprites
		for (auto p : m_entityVector)
		{
			if(p->IsAlive())
				p->Render(*m_viz);
		}
	}
}

void World::Run()
{
	m_viz = new Visualisation;

	if (!m_viz->Initialise(800, 1000))
		return;

	if (!LoadLevel())
		return;

	Update();

}

void World::FireBullet()
{
	const HAPI_TKeyboardData &keyData = HAPI.GetKeyboardData();

	DWORD time = HAPI.GetTime();
	if (time - lastPlayerBullet > 300 && keyData.scanCode[HK_SPACE])
	{
		lastPlayerBullet = time;
		for (auto p : m_entityVector)
		{
			if (p->GetSpriteName() == "bullet" && !p->IsAlive())
			{
				Vector2 playerPos;
				for (auto p : m_entityVector)
					if (p->GetSpriteName() == "player")
						playerPos = p->GetPosition();
				p->SetAlive(true);
				p->SetPosition(Vector2(playerPos.x, playerPos.y - 30));
				return;
			}
		}
	}
}