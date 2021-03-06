#pragma once
#include "Entity.h"

class ExplosionEntity : public Entity
{
public:
	ExplosionEntity(std::string spriteName, int noOfFrames, Vector2 startPos, float speed);
	~ExplosionEntity();

	void Update(Visualisation &viz) override final;
	ESide GetSide() const override final { return ESide::eNeutral; };
	int GetDamage() const override final { return 0; };
};

