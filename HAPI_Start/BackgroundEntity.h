#pragma once
#include "Entity.h"

class BackgroundEntity : public Entity
{
public:
	BackgroundEntity(std::string spriteName);
	~BackgroundEntity();

	void Update() override final;
	ESide GetSide() const override final { return ESide::eNeutral; };
};
