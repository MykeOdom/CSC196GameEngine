#pragma once
#include "Actor.h"

class Player : public Actor
{
public:
	Player() = default;
	Player(const Transform& transform) : Actor{ transform } {}
	Player(const Transform& transform, Model* model) :
		Actor{ transform, model } {}
	Player(const float speed, Transform& transform, Model* model) :
		Actor{ transform, model },
		m_speed {speed}
	{}

	virtual void OnCollision(Actor* actor);

	void SetFireModifier(float modifier) { m_fireModifier = modifier; }

	void Update(float dt);

private:
	float m_speed = 0;
	float m_fireTimer{ 0 };
	float m_fireModifier{ 1 };
};