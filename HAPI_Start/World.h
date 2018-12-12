#pragma once
#include <vector>
#include "Vector2.h"
#include <HAPI_lib.h>
#include "AI.h"

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
	AI m_AI;

	bool LoadLevel();
	void Update();
	int lastPlayerBullet{ 0 };
	//DWORD timeSinceLastTick{ 0 };
	const DWORD tickTime{ 50 };

public:
	World();
	~World();

	void Run();
	void FireBullet();
	void Collision();
	void Explosion(Vector2 pos);
	void CreateEnemy(int noOfEnemies, std::string enemyName, std::vector<EnemyEntity*> *enemyVector, float speed, float fireRate);
};

