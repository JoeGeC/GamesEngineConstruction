#include "ExplosionEntity.h"
#include "Visualisation.h"

ExplosionEntity::ExplosionEntity(std::string spriteName, int noOfFrames, Vector2 startPos, float speed) : Entity(spriteName, noOfFrames, startPos, speed)
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
