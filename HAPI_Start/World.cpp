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
	for (auto p : m_buttonVector)
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
	if (!m_viz->CreateSprite("retryButton", "Data\\sprites\\retryButton.png", true, 1))
		return false;
	if (!m_viz->CreateSprite("boss", "Data\\sprites\\boss.png", true, 1))
		return false;

	BackgroundEntity *background1 = new BackgroundEntity("background", 1, Vector2(0, 0), 5);
	m_entityVector.push_back(background1);

	BackgroundEntity *background2 = new BackgroundEntity("background", 1, Vector2(0, -1000), 5);
	m_entityVector.push_back(background2);
		
	PlayerEntity *player = new PlayerEntity("player", 3, Vector2(500, 700), 15);
	m_entityVector.push_back(player);

	//enemies
	std::vector<EnemyEntity*> enemyVector1;
	std::vector<EnemyEntity*> enemyVector2;
	std::vector<EnemyEntity*> enemyVector3;
	std::vector<EnemyEntity*> bossVector;
	CreateEnemy(5, "enemy", &enemyVector1, EType::eShooter, 20, 5, 1000, 20);
	CreateEnemy(5, "enemy1", &enemyVector1, EType::eShooter, 40, 3, 1000, 35);
	CreateEnemy(10, "enemy1", &enemyVector2, EType::eShooter, 40, 3, 750, 35);
	CreateEnemy(10, "enemy", &enemyVector3, EType::eKamikaze, 20, 30, 0, 25);
	CreateEnemy(10, "enemy1", &enemyVector3, EType::eShooter, 40, 5, 500, 45);
	CreateEnemy(1, "boss", &bossVector, EType::eShooter, 200, 8, 300, 150);

	// bullets
	for (int i = 0; i < 1000; i++)
	{
		BulletEntity *bullet = new BulletEntity("bullet", 1, Vector2(0, 0), 20);
		bullet->SetAlive(false);
		m_entityVector.push_back(bullet);
		m_bulletVector.push_back(bullet);
	}

	//explosions
	for (int i = 0; i < 20; i++)
	{
		ExplosionEntity *explosion = new ExplosionEntity("explosion", 12, Vector2(0, 0), 0);
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
	m_AI.CreateWave(Vector2(-100, 100), enemyVector1, vector<Vector2>{Vector2(850, 100), Vector2(-50, 300), Vector2(850, 500)});
	m_AI.CreateWave(Vector2(850, 250), enemyVector2, vector<Vector2>{Vector2(-50, 100), Vector2(850, 300), Vector2(-50, 500)});
	m_AI.CreateWave(Vector2(400, -50), enemyVector3, vector<Vector2>{Vector2(50, 200), Vector2(750, 400), Vector2(50, 400)});
	m_AI.CreateWave(Vector2(-100, 100), bossVector, vector<Vector2>{Vector2(700, 100), Vector2(0, 100)});


	//UI
	m_buttonVector.push_back(m_pauseButton);
	m_buttonVector.push_back(m_retryButton);

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
		EnemyEntity *enemy = new EnemyEntity(enemyName, 4, Vector2(-1000, -1000), speed, score, health, type);
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
				playerHealth = p->GetCurrentHealth();
				break;
			}
		}

		m_pauseButton->Update(*m_viz);
		if (m_pauseButton->IsClicked())
		{
			m_paused = true;
			HAPI.RenderText(m_screenWidth / 2 - 120, m_screenHeight / 2 - 50, HAPI_TColour::WHITE, "PAUSED", 60, eBold);
		}
		else
			m_paused = false;

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
			HAPI.RenderText(m_screenWidth / 2 - 100, m_screenHeight / 2 - 50, HAPI_TColour::WHITE, "Final Score: " + to_string(m_score), 30, eBold);

			m_retryButton->Update(*m_viz);
			if (m_retryButton->IsClicked())
			{
				Reset();
				m_retryButton->SetClicked(false);
			}

		}
	}
}

void World::WinGame()
{
	if (m_AI.GetNextWave() >= m_AI.GetSizeOfWaves())
	{
		for (const auto e : m_enemyVector)
		{
			if (e->IsAlive())
			{
				return;
			}
		}

		HAPI.RenderText(m_screenWidth / 2 - 120, m_screenHeight / 2 - 100, HAPI_TColour::WHITE, "CONGRATULATIONS", 30, eBold);
		HAPI.RenderText(m_screenWidth / 2 - 120, m_screenHeight / 2 - 50, HAPI_TColour::WHITE, "Final Score: " + to_string(m_score), 30, eBold);

		m_retryButton->Update(*m_viz);
		if (m_retryButton->IsClicked())
		{
			Reset();
			m_retryButton->SetClicked(false);
		}
			
	}
}

void World::Reset()
{
	for (auto& p : m_entityVector)
	{
		p->Reset();
		if (p->GetSpriteName() == "player" || p->GetSpriteName() == "background")
			p->SetAlive(true);
	}
	for (auto& p : m_enemyVector)
	{
		p->SetExploded(true);
		p->SetNextDestId(0);
	}
	for (auto& p : m_AI.GetWaves())
	{
		p->SetNextEnemy(0);
	}
	m_AI.SetTimeSinceLastWave(HAPI.GetTime());
	m_AI.SetNextWave(0);
	m_score = 0;
	m_gameOver = false;
}