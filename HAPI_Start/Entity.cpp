#include "Entity.h"
#include "Visualisation.h"
#include "Rectangle.h"


Entity::Entity(std::string spriteName) : m_spriteName(spriteName)
{
}


Entity::~Entity()
{
}

void Entity::Render(Visualisation &viz)
{
	m_entityRect = viz.GetSpriteCollection().at(m_spriteName)->CreateRectangle();
	viz.RenderSprite(m_spriteName, (int)m_position.x, (int)m_position.y, true);
}