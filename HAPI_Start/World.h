#pragma once
#include <vector>

class Visualisation;
class Entity;
class BulletEntity;

class World
{
private:
	Visualisation *m_viz{ nullptr };

	std::vector<Entity*> m_entityVector;

	bool LoadLevel();
	void Update();
	int lastPlayerBullet{ 0 };

public:
	World();
	~World();

	void Run();
	void FireBullet();

};

