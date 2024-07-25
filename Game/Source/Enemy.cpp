#include "Enemy.h"
#include "Scene.h"
#include "../../Game/Source/Player.h"
#include "Player.h"
#include "Game.h"

void Enemy::OnCollision(Actor* actor)
{
	if (actor->GetTag() == "Player")
	{
		m_scene->GetGame()->AddPoints(100);
		m_destroy = true;
	}
}

void Enemy::Update(float dt)
{
	Player* player = m_scene->GetActor<Player>();
	if (player)
	{
		Vector2 direction = player->GetTransform().position - m_transform.position;
		m_velocity += direction.Normalize() * m_speed * dt;
		m_transform.rotation = direction.Angle();
	}

	Actor::Update(dt);
}