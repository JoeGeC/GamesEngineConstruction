#pragma once
#include "Entity.h"

enum class EType
{
	eShooter,
	eKamikaze
};

class EnemyEntity : public Entity
{
public:
	EnemyEntity(std::string spriteName, int noOfFrames, Vector2 startPos, float speed, int score, int health, EType type);
	~EnemyEntity();

	void Update(Visualisation &viz) override final;
	ESide GetSide() const override final { return ESide::eEnemy; };
	int GetDamage() const override final { return 20; };
	int Collision(int damage, string collider);
	
	int GetNextDestId() const { return m_nextDestId; }
	float GetFireRate() const { return m_fireRate; }
	DWORD GetTimeSinceLastBulletFired() const { return m_timeSinceLastBulletFired; }
	int GetScore() const { return m_score; }
	EType GetType() const { return m_type; }
	
	void SetNextDestId(int i) { m_nextDestId = i; }
	void IncrementNextDestId(int i) { m_nextDestId += i; }
	void SetNextDest(Vector2 nextDest) { m_nextDest = nextDest; }
	void SetTimeSinceLastBulletFired(DWORD time) { m_timeSinceLastBulletFired = time; }
	void SetFireRate(float fireRate) { m_fireRate = fireRate; }

private:
	Vector2 m_nextDest;
	int m_nextDestId{ 0 };
	DWORD m_timeSinceLastBulletFired{ 0 };
	float m_fireRate{ 0 };
	int m_score{ 10 };
	EType m_type{ EType::eShooter };
};

