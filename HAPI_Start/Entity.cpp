#include "Entity.h"
#include "Visualisation.h"
#include "Rectangle.h"


Entity::Entity(std::string spriteName, int noOfFrames, float speed) : m_spriteName(spriteName), m_noOfFrames(noOfFrames), m_speed(speed)
{
}


Entity::~Entity()
{
}

void Entity::Render(Visualisation &viz, float s)
{
	Animate();
	m_entityRect = viz.GetSpriteCollection().at(m_spriteName)->CreateRectangle();

	Vector2 interPos(m_oldPosition + (m_position - m_oldPosition) * s);

	viz.RenderSprite(m_spriteName, (int)interPos.x, (int)interPos.y, true, m_frameNo);
}

void Entity::MoveToDest(Vector2 dest)
{


	Vector2 distTemp = (m_position - dest);
	//float distance = sqrt(distTemp.x * distTemp.x + distTemp.y * distTemp.y);

	Vector2 dirTemp = (dest - m_position);
	float magnitude = sqrt(dirTemp.x * dirTemp.x + distTemp.y * distTemp.y);
	Vector2 direction = dirTemp / magnitude;

	m_position += direction * m_speed;

	SetPosition(m_position);
}

void Entity::Animate()
{
	//animation time
	DWORD time = HAPI.GetTime();
	if (time - m_lastFrameUpdateTime > 150)
	{
		m_frameNo++;
		m_lastFrameUpdateTime = time;
	}
	if (m_frameNo > m_noOfFrames - 1)
		m_frameNo = 0;
}