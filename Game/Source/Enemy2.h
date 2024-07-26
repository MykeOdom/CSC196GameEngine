#pragma once
#include "Actor.h"

class Enemy2 : public Actor
{
public:
	Enemy2() = default;
	Enemy2(const Transform transform) : Actor{ transform } {}
	Enemy2(const Transform transform, Model* model) :
		Actor{ transform , model }
	{}
	Enemy2(float speed, const Transform transform, Model* model) :
		Actor{ transform , model },
		m_speed{ speed }
	{}
	virtual void OnCollision(Actor* actor);

	void Update(float dt);
private:
	float m_heath = 2;

	float m_speed{ 0 };
	float m_fireTimer{ 0 };

};