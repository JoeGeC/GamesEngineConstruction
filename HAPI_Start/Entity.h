#pragma once

#include "Vector2.h"
#include <string>
#include "HAPI_lib.h"

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
	bool m_alive{ true };
	float speed{ 1.0f };
	float dSpeed = sqrt((speed * speed) * 2.0f) / 2.0f;

public:
	Entity(std::string spriteName);
	virtual ~Entity();
	virtual void Update() = 0;
	virtual ESide GetSide() const = 0;

	void Render(Visualisation &viz);

	void SetPosition(Vector2 newPos) { m_position = newPos; }
	void SetAlive(bool isAlive) { m_alive = isAlive; }

	std::string GetSpriteName() const { return m_spriteName; };
	bool IsAlive() const { return m_alive; };
	Vector2 GetPosition() const { return m_position; };
};

