#include "ExplosionEntity.h"
#include "Visualisation.h"

ExplosionEntity::ExplosionEntity(std::string spriteName, int noOfFrames, float speed) : Entity(spriteName, noOfFrames, speed)
{
}


ExplosionEntity::~ExplosionEntity()
{
}

void ExplosionEntity::Update(Visualisation &viz)
{
	if (m_frameNo == 11)
	{
		m_alive = false;
		m_frameNo = 0;
	}
}
