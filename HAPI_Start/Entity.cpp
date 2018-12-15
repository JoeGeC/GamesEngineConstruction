#include "Entity.h"
#include "Visualisation.h"
#include "Rectangle.h"


Entity::Entity(std::string spriteName, int noOfFrames, Vector2 startPos, float speed) : m_spriteName(spriteName), m_noOfFrames(noOfFrames), m_startPos(startPos), m_position(startPos), m_speed(speed)
{
}


Entity::~Entity()
{
}

void Entity::PreUpdate(Visualisation &viz)
{
	//rectangles
	m_entityRect = viz.GetSpriteCollection().at(m_spriteName)->CreateRectangle();

	Update(viz);
}

void Entity::Render(Visualisation &viz, float s)
{
	Animate();

	Vector2 interPos(m_oldPosition + (m_position - m_oldPosition) * s);

	viz.RenderSprite(m_spriteName, (int)interPos.x, (int)interPos.y, true, m_frameNo);
}

void Entity::MoveToDest(Vector2 dest)
{
	Vector2 pos{ GetPosition() };

	Vector2 distTemp = (pos - dest);
	//float distance = sqrt(distTemp.x * distTemp.x + distTemp.y * distTemp.y);

	Vector2 dirTemp = (dest - pos);
	float magnitude = sqrt(dirTemp.x * dirTemp.x + distTemp.y * distTemp.y);
	Vector2 direction = dirTemp / magnitude;

	pos += direction * m_speed;

	SetPosition(pos);
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

void Entity::Reset()
{
	m_alive = false;
	m_exploded = false;
	m_frameNo = 0;
	m_currentHealth = m_maxHealth;
	m_position = m_startPos;
}