#pragma once
#include "Entity.h"

class BackgroundEntity : public Entity
{
public:
	BackgroundEntity(std::string spriteName, int noOfFrames);
	~BackgroundEntity();

	void Update(Visualisation &viz) override final;
	ESide GetSide() const override final { return ESide::eNeutral; };
};

