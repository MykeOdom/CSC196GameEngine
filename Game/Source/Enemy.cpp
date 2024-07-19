#include "Enemy.h"
#include "Scene.h"
#include "../../Game/Source/Player.h"

void Enemy::OnCollision(Actor* actor)
{
	if (actor->GetTag() == "Player")
	{
		//std::cout << "collison\n";
		m_destroy = true;
	}
}

void Enemy::Update(float dt)
{
	Player* player = m_scene->GetActor<Player>();
	if (player)
	{
		Vector2 direction = player->GetTransform().position - m_transform.position;
		m_velocity = direction.Normalize() * m_speed * dt;
		m_transform.rotation = direction.Angle();
	}

	Actor::Update(dt);
}