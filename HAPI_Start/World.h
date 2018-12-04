#pragma once
#include <vector>
#include "Vector2.h"

class Visualisation;
class Entity;
class BulletEntity;
class ExplosionEntity;
class Sound;

class World
{
private:
	Visualisation *m_viz{ nullptr };

	std::vector<Entity*> m_entityVector;
	std::vector<ExplosionEntity*> m_explosionVector;

	bool LoadLevel();
	void Update();
	int lastPlayerBullet{ 0 };

public:
	World();
	~World();

	void Run();
	void FireBullet();
	void Collision();
	void Explosion(Vector2 pos);

};

