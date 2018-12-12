#pragma once
#include "Entity.h"
class BulletEntity : public Entity
{
public:
	BulletEntity(std::string spriteName, int noOfFrames, float speed);
	~BulletEntity();

	void Update(Visualisation &viz) override final;
	ESide GetSide() const override final { return m_side; }
	int GetDamage() const override final { return 20; }
	void Collision(int damage, string collider) override final;

	void SetSide(ESide side) { m_side = side; }

private:
	ESide m_side{ ESide::ePlayer };

};

