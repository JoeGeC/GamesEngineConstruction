#include "Entity.h"
#include "Visualisation.h"


Entity::Entity(std::string spriteName) : m_spriteName(spriteName)
{
}


Entity::~Entity()
{
}

void Entity::Render(Visualisation &viz)
{
	viz.RenderSprite(m_spriteName, (int)m_position.x, (int)m_position.y, true);
}