#pragma once
#include "Entity.h"

class ExplosionEntity : public Entity
{
public:
	ExplosionEntity(std::string spriteName);
	~ExplosionEntity();

	void Update(Visualisation &viz) override final;
	ESide GetSide() const override final { return ESide::eNeutral; };
	int GetDamage() const override final { return 0; };
};

