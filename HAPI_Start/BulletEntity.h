#pragma once
#include "Entity.h"
class BulletEntity : public Entity
{
public:
	BulletEntity(std::string spriteName);
	~BulletEntity();

	void Update() override final;
	ESide GetSide() const override final { return ESide::ePlayer; };
	int GetDamage() const override final { return 20; };
	void Collision(int damage, string collider) override final;
};

