#pragma once
#include <vector>
#include "Vector2.h"
#include <HAPI_lib.h>
#include "AI.h"
#include "Button.h"

using namespace HAPISPACE;

class Visualisation;
class Entity;
class BulletEntity;
class ExplosionEntity;
class Sound;
class EnemyEntity;

class World
{
private:
	Visualisation *m_viz{ nullptr };

	std::vector<Entity*> m_entityVector;
	std::vector<ExplosionEntity*> m_explosionVector;
	std::vector<BulletEntity*> m_bulletVector;
	std::vector<Sound*> m_soundVector;
	std::vector<EnemyEntity*> m_enemyVector;
	std::vector<Button*> m_buttonVector;
	AI m_AI;

	bool LoadLevel();
	void Update();
	int lastPlayerBullet{ 0 };
	const DWORD tickTime{ 50 };
	int m_screenWidth{ 800 };
	int m_screenHeight{ 1000 };
	bool m_paused{ false };
	int m_score{ 0 };
	bool m_gameOver{ false };

	void FirePlayerBullet();
	void FireEnemyBullet();
	void Collision();
	void Explosion(Vector2 pos);
	void CreateEnemy(int noOfEnemies, std::string enemyName, std::vector<EnemyEntity*> *enemyVector, EType type, int health, float speed, float fireRate, int score);
	void RenderUI();
	void EndGame();
	void WinGame();

public:
	World();
	~World();

	void Run();
};

