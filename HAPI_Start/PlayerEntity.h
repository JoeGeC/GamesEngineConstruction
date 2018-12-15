#pragma once
#include "Entity.h"

class PlayerEntity : public Entity
{
public:
	PlayerEntity(std::string spriteName, int noOfFrames, Vector2 startPos, float speed);
	~PlayerEntity();

	void Update(Visualisation &viz) override final;
	ESide GetSide() const override final { return ESide::ePlayer; };
	int Collision(int damage, string collider) override final;

};

