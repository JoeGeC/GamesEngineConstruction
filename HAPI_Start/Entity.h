#pragma once

#include "Vector2.h"
#include <string>
#include "HAPI_lib.h"
#include "Rectangle.h"

using namespace HAPISPACE;

enum class ESide
{
	ePlayer,
	eEnemy,
	eNeutral
};

class Visualisation;

class Entity
{
protected:
	Vector2 m_position;
	std::string m_spriteName;
	Rectangle m_entityRect;
	bool m_alive{ true };
	bool m_exploded{ false };
	float m_speed{ 10.0f };
	float m_dSpeed = sqrt((m_speed * m_speed) * 2.0f) / 2.0f;
	int m_frameNo{ 0 };
	int m_noOfFrames{ 0 };
	DWORD lastFrameUpdateTime{ 0 };

public:
	Entity(std::string spriteName, int noOfFrames);
	virtual ~Entity();
	virtual void Update(Visualisation &viz) = 0;
	virtual ESide GetSide() const = 0;
	virtual int GetDamage() const { return 0; };
	virtual void Collision(int damage, string collider) {};
	void MoveToDest(Vector2 dest);
	void Animate();

	void Render(Visualisation &viz);

	void SetPosition(Vector2 newPos) { m_position.x = newPos.x; m_position.y = newPos.y; }
	void SetAlive(bool isAlive) { m_alive = isAlive; }
	void SetExploded(bool exploded) { m_exploded = exploded; }

	std::string GetSpriteName() const { return m_spriteName; };
	bool IsAlive() const { return m_alive; };
	bool HasExploded() const { return m_exploded; };
	Vector2 GetPosition() const { return m_position; };
	Rectangle GetRect() const { return m_entityRect; };
	float GetSpeed() const { return m_speed; };
};

