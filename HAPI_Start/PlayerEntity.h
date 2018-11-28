#pragma once
#include "Entity.h"

class PlayerEntity : public Entity
{
public:
	PlayerEntity(std::string spriteName);
	~PlayerEntity();

	void Update() override final;
	ESide GetSide() const override final { return ESide::ePlayer; };
	void Collision(int damage, string collider) override final;

private:
	int m_health{ 100 };

};

