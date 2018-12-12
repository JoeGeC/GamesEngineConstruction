#include "World.h"
#include "Visualisation.h"
#include "EnemyEntity.h"
#include "PlayerEntity.h"
#include "BackgroundEntity.h"
#include "BulletEntity.h"
#include "ExplosionEntity.h"
#include "Sound.h"
#include "AI.h"

#include <cassert>

//TODO: UI
//TODO: MENU
//TODO: LEVELS

World::World()
{
}


World::~World()
{
	delete m_viz;

	for (auto p : m_entityVector)
		delete p;
	for (auto p : m_soundVector)
		delete p;
}

bool World::LoadLevel()
{
	//load all the sprites
	if(!m_viz->CreateSprite("player", "Data\\sprites\\spaceship.png", true, 3))
		return false;
	if (!m_viz->CreateSprite("background", "Data\\sprites\\spaceBackground.png", false, 1))
		return false;
	if (!m_viz->CreateSprite("bullet", "Data\\sprites\\bullet2.png", true, 1))
		return false;
	if (!m_viz->CreateSprite("enemy", "Data\\sprites\\enemy.png", true, 4))
		return false;
	if (!m_viz->CreateSprite("enemy1", "Data\\sprites\\enemy1.png", true, 4))
		return false;
	if (!m_viz->CreateSprite("explosion", "Data\\sprites\\Explosion.png", true, 12))
		return false;

	BackgroundEntity *background1 = new BackgroundEntity("background", 1, 5);
	m_entityVector.push_back(background1);
	background1->SetPosition(Vector2(0, 0));

	BackgroundEntity *background2 = new BackgroundEntity("background", 1, 5);
	m_entityVector.push_back(background2);
	background2->SetPosition(Vector2(0, -1000));
	
	PlayerEntity *player = new PlayerEntity("player", 3, 15);
	m_entityVector.push_back(player);
	player->SetPosition(Vector2(500, 700));

	//enemies
	std::vector<EnemyEntity*> enemyVector1;
	std::vector<EnemyEntity*> enemyVector2;
	CreateEnemy(10, "enemy", &enemyVector1, 5, 1000);
	CreateEnemy(10, "enemy1", &enemyVector2, 3, 0);

	// bullets
	for (int i = 0; i < 1000; i++)
	{
		BulletEntity *bullet = new BulletEntity("bullet", 1, 20);
		bullet->SetAlive(false);
		m_entityVector.push_back(bullet);
		m_bulletVector.push_back(bullet);
	}

	//explosions
	for (int i = 0; i < 20; i++)
	{
		ExplosionEntity *explosion = new ExplosionEntity("explosion", 12, 0);
		explosion->SetAlive(false);
		m_entityVector.push_back(explosion);
		m_explosionVector.push_back(explosion);
	}

	//load all the sounds
	Sound *explosionSound = new Sound("explosion", "Data\\sounds\\explosion.flac");
	explosionSound->LoadSound();
	m_soundVector.push_back(explosionSound);

	Sound *music = new Sound("explosion", "Data\\sounds\\music.flac");
	m_soundVector.push_back(music);
	music->LoadSound();
	music->PlayStreamed();

	//manage waves
	m_AI.CreateWave(Vector2(-50, -50), enemyVector1, vector<Vector2>{Vector2(800, 100), Vector2(0, 300), Vector2(400, 500)});
	m_AI.CreateWave(Vector2(850, -50), enemyVector2, vector<Vector2>{Vector2(0, 100), Vector2(800, 300), Vector2(400, 500)});

	return true;
}

void World::Update()
{
	DWORD lastTimeTicked{ 0 };

	while (HAPI.Update())
	{
		DWORD timeSinceLastTick{ HAPI.GetTime() - lastTimeTicked };
		if (timeSinceLastTick >= tickTime)
		{
			HAPI.SetShowFPS(true);

			m_AI.SpawnEnemy();

			FireBullet();

			//update what entities are doing
			for (auto p : m_entityVector)
			{
				if (p->IsAlive())
					p->Update(*m_viz);
			}

			m_AI.Update();		
		
			//clear screen to black
			m_viz->ClearToGrey(0);

			timeSinceLastTick = 0;
			lastTimeTicked = HAPI.GetTime();

			float s = timeSinceLastTick / (float)tickTime;

			//render sprites
			for (auto p : m_entityVector)
			{
				if (p->IsAlive())
					p->Render(*m_viz, s);
			}

			//check collisions
			Collision();
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
		for (auto b : m_bulletVector)
		{
			if (!b->IsAlive())
			{
				Vector2 playerPos;
				for (auto p : m_entityVector)
					if (p->GetSpriteName() == "player")
						playerPos = p->GetPosition();
				b->SetAlive(true);
				b->SetPosition(Vector2(playerPos.x + 16, playerPos.y - 20));
				b->SetSide(ESide::ePlayer);
				return;
			}
		}
	}

	for (auto e : m_enemyVector)
	{
		float fireRate = e->GetFireRate();
		if (fireRate > 0 && time - e->GetTimeSinceLastBulletFired() > fireRate && e->IsAlive())
		{
			e->SetTimeSinceLastBulletFired(time);
			for (auto b : m_bulletVector)
			{
				if (!b->IsAlive())
				{
					Vector2 enemyPos{ e->GetPosition() };
					b->SetAlive(true);
					b->SetPosition(Vector2(enemyPos.x + 16, enemyPos.y + 20));
					b->SetSide(ESide::eEnemy);
					return;
				}
			}
		}
	}

}

void World::Explosion(Vector2 pos)
{
	for (auto e : m_explosionVector)
	{
		if (!e->IsAlive())
		{
			e->SetAlive(true);
			e->SetPosition(Vector2(pos.x - 20, pos.y - 40), Vector2(pos.x - 20, pos.y - 40)); //needed twice because not interpolating between two points
			for (auto s : m_soundVector)
			{
				//TODO: Fix explosion sound looping
				if (s->GetName() == "explosion")
					s->PlaySound();
			}
			return;
		}
	}
}

void World::Collision()
{
	for (auto p : m_entityVector)
	{
		if (p->IsAlive() && p->GetSide() != ESide::eNeutral)
		{
			for (auto i : m_entityVector)
			{
				if (i->IsAlive() && i->GetSide() != ESide::eNeutral && p->GetSide() != i->GetSide() && !(p->GetSpriteName() == "bullet" && i->GetSpriteName() == "bullet"))
				{
					Rectangle pRect = p->GetRect();
					Rectangle iRect = i->GetRect();
					pRect.ShrinkRect();
					iRect.ShrinkRect();
					pRect.Translate((int)p->GetPosition().x, (int)p->GetPosition().y);
					iRect.Translate((int)i->GetPosition().x, (int)i->GetPosition().y);

					if (!((pRect.m_right < iRect.m_left || pRect.m_left > iRect.m_right) // p is to one side of i
						|| (pRect.m_bottom < iRect.m_top || pRect.m_top > iRect.m_bottom))) // p is completely above or below i
					{
						//Collision occurred
						p->Collision(i->GetDamage(), i->GetSpriteName());
						i->Collision(p->GetDamage(), p->GetSpriteName());
						Explosion(i->GetPosition());
					}
				}
			}
		}
	}
}

void World::CreateEnemy(int noOfEnemies, std::string enemyName, std::vector<EnemyEntity*> *enemyVector, float speed, float fireRate)
{
	for (int i = 0; i < noOfEnemies; i++)
	{
		EnemyEntity *enemy = new EnemyEntity(enemyName, 4, speed);
		enemy->SetAlive(false);
		enemy->SetExploded(true);
		enemy->SetFireRate(fireRate);
		m_entityVector.push_back(enemy);
		enemyVector->push_back(enemy);
		m_enemyVector.push_back(enemy);
	}
}