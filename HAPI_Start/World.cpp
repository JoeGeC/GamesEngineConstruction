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

//TODO: MENU
//TODO: LEVELS
//TODO: RESET

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
	if (!m_viz->CreateSprite("pauseButton", "Data\\sprites\\pauseButton.png", true, 1))
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
	CreateEnemy(10, "enemy", &enemyVector1, EType::eKamikaze, 20, 30, 0, 20);
	CreateEnemy(10, "enemy1", &enemyVector2, EType::eShooter, 30, 3, 1000, 30);

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

	Sound *pewSound = new Sound("pew", "Data\\sounds\\pew.flac");
	pewSound->LoadSound();
	m_soundVector.push_back(pewSound);

	Sound *music = new Sound("music", "Data\\sounds\\music.flac");
	m_soundVector.push_back(music);
	music->LoadSound();
	music->PlayStreamed();

	//manage waves
	m_AI.CreateWave(Vector2(-100, -100), enemyVector1, vector<Vector2>{Vector2(800, 100), Vector2(0, 300), Vector2(400, 500)});
	m_AI.CreateWave(Vector2(850, -50), enemyVector2, vector<Vector2>{Vector2(0, 100), Vector2(800, 300), Vector2(400, 500)});

	//UI
	Button *pauseButton = new Button("pauseButton", Vector2(1, 1));
	m_buttonVector.push_back(pauseButton);

	return true;
}

void World::Update()
{
	DWORD lastTimeTicked{ 0 };

	while (HAPI.Update())
	{
		if (!m_paused)
		{
			DWORD timeSinceLastTick{ HAPI.GetTime() - lastTimeTicked };
			if (timeSinceLastTick >= tickTime)
			{
				HAPI.SetShowFPS(true);

				m_AI.SpawnEnemy();

				FireEnemyBullet();

				Vector2 playerPos{ (float)m_screenWidth / 2, (float)m_screenHeight + 1000 };

				//update what entities are doing
				for (auto p : m_entityVector)
				{
					if (p->IsAlive() && p->GetSpriteName() == "player")
					{
						FirePlayerBullet();
						playerPos = p->GetPosition();
					}
					if (p->IsAlive())
						p->PreUpdate(*m_viz);
				}

				m_AI.Update(playerPos);

				lastTimeTicked = HAPI.GetTime();
				timeSinceLastTick = 0;

				//check collisions
				Collision();
			}

			float s = timeSinceLastTick / (float)tickTime;
			assert(s >= 0 && s <= 1);

			//render sprites
			for (auto p : m_entityVector)
			{
				if (p->IsAlive())
					p->Render(*m_viz, s);
			}

			EndGame();
			WinGame();
		}

		RenderUI();
	}
}

void World::Run()
{
	m_viz = new Visualisation;

	if (!m_viz->Initialise(m_screenWidth, m_screenHeight))
		return;

	if (!LoadLevel())
		return;

	Update();

}

void World::FirePlayerBullet()
{
	const HAPI_TKeyboardData &keyData = HAPI.GetKeyboardData();
	const HAPI_TControllerData &contData = HAPI.GetControllerData(0);
	
	DWORD time = HAPI.GetTime();
	if (time - lastPlayerBullet > 300 && (keyData.scanCode[HK_SPACE] || contData.digitalButtons[HK_DIGITAL_A]))
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
				for (auto s : m_soundVector)
				{
					if (s->GetName() == "pew")
						s->PlaySound();
				}
				return;
			}
		}
	}
}

void World::FireEnemyBullet()
{
	DWORD time = HAPI.GetTime();
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
						m_score += p->Collision(i->GetDamage(), i->GetSpriteName());
						m_score += i->Collision(p->GetDamage(), p->GetSpriteName());
						Explosion(i->GetPosition());
					}
				}
			}
		}
	}
}

void World::CreateEnemy(int noOfEnemies, std::string enemyName, std::vector<EnemyEntity*> *enemyVector, EType type, int health, float speed, float fireRate, int score)
{
	for (int i = 0; i < noOfEnemies; i++)
	{
		EnemyEntity *enemy = new EnemyEntity(enemyName, 4, speed, score, health, type);
		enemy->SetAlive(false);
		enemy->SetExploded(true);
		enemy->SetFireRate(fireRate);
		m_entityVector.push_back(enemy);
		enemyVector->push_back(enemy);
		m_enemyVector.push_back(enemy);
	}
}

void World::RenderUI()
{
	if (!m_gameOver)
	{
		int playerHealth{ 0 };
		for (auto p : m_entityVector)
		{
			if (p->GetSpriteName() == "player")
			{
				playerHealth = p->GetHealth();
				break;
			}
		}

		for (auto& b : m_buttonVector)
		{
			b->Update(*m_viz);
			b->Render(*m_viz);
			if (b->GetSpriteName() == "pauseButton" && b->IsClicked())
			{
				m_paused = true;
				HAPI.RenderText(m_screenWidth / 2 - 120, m_screenHeight / 2 - 50, HAPI_TColour::WHITE, "PAUSED", 60, eBold);
			}
			else
				m_paused = false;
		}

		HAPI.RenderText(300, 50, HAPI_TColour::WHITE, "LEVEL 1", 30, eBold);
		HAPI.RenderText(10, m_screenHeight - 50, HAPI_TColour::WHITE, "Health: " + std::to_string(playerHealth), 30, eBold);
		HAPI.RenderText(m_screenWidth / 2 - 120, 10, HAPI_TColour::WHITE, "Score: " + std::to_string(m_score), 30, eBold);
	}
}

void World::EndGame()
{
	for (const auto e : m_entityVector)
	{
		if (e->GetSpriteName() == "player" && !e->IsAlive())
		{
			m_gameOver = true;
			HAPI.RenderText(m_screenWidth / 2 - 100, m_screenHeight / 2 - 100, HAPI_TColour::WHITE, "GAME OVER", 30, eBold);
			HAPI.RenderText(m_screenWidth / 2 - 150, m_screenHeight / 2 - 50, HAPI_TColour::WHITE, "Final Score: " + to_string(m_score), 30, eBold);
		}
	}
}

void World::WinGame()
{
	for (const auto e : m_enemyVector)
	{
		if (e->IsAlive())
		{
			return;
		}
	}
	HAPI.RenderText(m_screenWidth / 2 - 100, m_screenHeight / 2 - 100, HAPI_TColour::WHITE, "CONGRATULATIONS", 30, eBold);
	HAPI.RenderText(m_screenWidth / 2 - 150, m_screenHeight / 2 - 50, HAPI_TColour::WHITE, "Final Score: " + to_string(m_score), 30, eBold);
}