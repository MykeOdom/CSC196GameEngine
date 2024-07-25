#include "Player.h"
#include "Bullet.h"
#include "Scene.h"
#include "Engine.h"
#include "Transform.h"
#include "GameData.h"
#include "SpaceGame.h"
#include <memory>

void Player::OnCollision(Actor* actor)
{
	if (actor->GetTag() == "Enemy")
	{
		m_destroy = true;
		dynamic_cast<SpaceGame*>(m_scene->GetGame())->OnPlayerDeath();
	}
}

void Player::Update(float dt)
{
	float thrust = 0;

	Vector2 direction{ 0,0 };
	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_W)) direction.x = 1;
	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_S)) direction.x = -1;

	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_Q)) direction.y = -1;
	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_E)) direction.y = 1;

	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_A)) m_transform.rotation += Math::DegtToRad(100) * dt;
	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_D)) m_transform.rotation -= Math::DegtToRad(100) * dt;

	Vector2 acceleration = direction.Rotate(m_transform.rotation) * m_speed;

	m_velocity += acceleration * dt;

	m_transform.position.x = Math::Wrap(m_transform.position.x, (float)g_engine.GetRenderer().GetWidth());
	m_transform.position.y = Math::Wrap(m_transform.position.y, (float)g_engine.GetRenderer().GetHeight());

	//fire
	m_fireTimer -= dt;
	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_SPACE) && m_fireTimer <= 0)
	{
		m_fireTimer = 0.2f * m_fireModifier;

		Vector2 direction = g_engine.GetInput().GetMousePosition() - m_transform.position;
		float angle = direction.Angle();

		//actor
		Color color{ 1,1,0 };
		std::vector<Vector2> points;
		points.push_back(Vector2{ 5, 0 });
		points.push_back(Vector2{ -5 , -5 });
		points.push_back(Vector2{ -5 , 5 });
		points.push_back(Vector2{ 5 , 0 });

		Model* model = new Model{ points, color };
		Transform transform{ m_transform.position, angle, 1 };

		auto bullet = std::make_unique<Bullet>( 400.f, transform, model );
		bullet->SetLifespan(1);
		bullet->SetTag("PlayerBullet");
		m_scene->AddActor(std::move(bullet));
	}

	Actor::Update(dt);

}
