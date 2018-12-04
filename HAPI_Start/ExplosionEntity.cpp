#include "ExplosionEntity.h"
#include "Visualisation.h"

ExplosionEntity::ExplosionEntity(std::string spriteName) : Entity(spriteName)
{
}


ExplosionEntity::~ExplosionEntity()
{
}

void ExplosionEntity::Update(Visualisation &viz)
{
	m_frameNo = viz.GetSpriteCollection().at("explosion")->GetFrameNo();
	if (m_frameNo == 11)
	{
		m_alive = false;
		viz.GetSpriteCollection().at("explosion")->SetFrameNo(0);
		
	}
}
