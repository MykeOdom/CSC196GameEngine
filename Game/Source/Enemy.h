#pragma once
#include "Actor.h"

class Enemy : public Actor
{
public:
	Enemy() = default;
	Enemy(const Transform transform) : Actor{ transform } {}
	Enemy(const Transform transform, Model* model) :
		Actor{ transform , model }
	{}
	Enemy(float speed, const Transform transform, Model* model) :
		Actor{ transform , model },
		m_speed{ speed }
	{}
	virtual void OnCollision(Actor* actor);

	void Update(float dt);
private:
	float m_heath = 1;

	float m_speed{ 0 };
	float m_fireTimer{ 0 };

};