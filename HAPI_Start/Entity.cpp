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

void Entity::MoveToDest(Vector2 dest)
{
	Vector2 distTemp = (m_position - dest);
	//float distance = sqrt(distTemp.x * distTemp.x + distTemp.y * distTemp.y);

	Vector2 dirTemp = (dest - m_position);
	float magnitude = sqrt(dirTemp.x * dirTemp.x + distTemp.y * distTemp.y);
	Vector2 direction = dirTemp / magnitude;

	m_position += direction * m_speed;
}