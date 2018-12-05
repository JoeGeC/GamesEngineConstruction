#include "World.h"
#include "Visualisation.h"
#include "EnemyEntity.h"
#include "PlayerEntity.h"
#include "BackgroundEntity.h"
#include "BulletEntity.h"
#include "ExplosionEntity.h"
#include "Sound.h"

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
	if (!m_viz->CreateSprite("bullet", "Data\\sprites\\bullet.png", true, 1))
		return false;
	if (!m_viz->CreateSprite("enemy", "Data\\sprites\\enemy.png", true, 4))
		return false;
	if (!m_viz->CreateSprite("explosion", "Data\\sprites\\Explosion.png", true, 12))
		return false;

	BackgroundEntity *background1 = new BackgroundEntity("background", 1);
	m_entityVector.push_back(background1);
	background1->SetPosition(Vector2(0, 0));

	BackgroundEntity *background2 = new BackgroundEntity("background", 1);
	m_entityVector.push_back(background2);
	background2->SetPosition(Vector2(0, -1000));
	
	PlayerEntity *player = new PlayerEntity("player", 3);
	m_entityVector.push_back(player);
	player->SetPosition(Vector2(500, 700));

	//enemies
	for (int i = 0; i < 10; i++)
	{
		EnemyEntity *enemy = new EnemyEntity("enemy", 4);
		m_entityVector.push_back(enemy);
		enemy->SetPosition(Vector2(i * 40.f, 50.f));
	}

	// bullets
	for (int i = 0; i < 20; i++)
	{
		BulletEntity *bullet = new BulletEntity("bullet", 1);
		bullet->SetAlive(false);
		m_entityVector.push_back(bullet);
		m_bulletVector.push_back(bullet);
	}

	//explosions
	for (int i = 0; i < 20; i++)
	{
		ExplosionEntity *explosion = new ExplosionEntity("explosion", 12);
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

	return true;
}

void World::Update()
{
	while (HAPI.Update())
	{
		DWORD time = HAPI.GetTime();
		if (time - timeSinceLastUpdate > 3)
		{
			HAPI.SetShowFPS(true);

			FireBullet();

			//update what entities are doing
			for (auto p : m_entityVector)
			{
				if (p->IsAlive())
					p->Update(*m_viz);
				if (p->GetSpriteName() == "enemy")
					p->MoveToDest(Vector2(500, 500));
				if (p->GetSpriteName() != "bullet" && p->GetSpriteName() != "explosion" && !p->IsAlive() && !p->HasExploded())
				{
					Explosion(p->GetPosition());
					p->SetExploded(true);
				}
			}

			//clear screen to black
			m_viz->ClearToGrey(0);

			//render sprites
			for (auto p : m_entityVector)
			{
				if (p->IsAlive())
					p->Render(*m_viz);
			}

			//collisions
			Collision();

			timeSinceLastUpdate = time;
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
				return;
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
			e->SetPosition(Vector2(pos.x - 20, pos.y - 40));
			for (auto s : m_soundVector)
			{
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
				if (i->IsAlive() && i->GetSide() != ESide::eNeutral && p->GetSide() != i->GetSide())
				{
					Rectangle pRect = p->GetRect();
					Rectangle iRect = i->GetRect();
					pRect.ShrinkRect();
					iRect.ShrinkRect();
					pRect.Translate((int)p->GetPosition().x, (int)p->GetPosition().y);
					iRect.Translate((int)i->GetPosition().x, (int)i->GetPosition().y);

					if ((pRect.m_right < iRect.m_left || pRect.m_left > iRect.m_right) // p is to one side of i
						|| (pRect.m_bottom < iRect.m_top || pRect.m_top > iRect.m_bottom)) // p is completely above or below i
					{
						//No collision
					}
					else
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