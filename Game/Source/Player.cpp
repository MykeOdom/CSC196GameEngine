#include "Player.h"
#include "Bullet.h"
#include "Scene.h"
#include "Engine.h"

void Player::OnCollision(Actor* actor)
{
	if (actor->GetTag() == "Enemy")
	{
		//std::cout << "collison\n";
		m_destroy = true;
	}

}

void Player::Update(float dt)
{

	//
	float thrust = 0;
	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_UP))   thrust = m_speed;
	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_DOWN)) thrust = m_speed;

	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_LEFT))  m_transform.rotation -= Math::DegtToRad(100) * dt;
	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_RIGHT)) m_transform.rotation += Math::DegtToRad(100) *dt;

	Vector2 acceleration = Vector2{ thrust, 0.0f }.Rotate(m_transform.rotation);

	m_velocity += acceleration * dt;

	m_transform.postion.x = Math::Wrap(m_transform.postion.x, (float)g_engine.GetRenderer().getWidth());
	m_transform.postion.y = Math::Wrap(m_transform.postion.y, (float)g_engine.GetRenderer().getHeight());

	//fire
	m_fireTimer -= dt;
	if (INPUT.GetKeyDown(SDL_SCANCODE_SPACE) && m_fireTimer <= 0)
	{
		Color color{ 1,1,0 };
		std::vector<Vector2> points;
		points.push_back(Vector2{ 5, 0 });
		points.push_back(Vector2{ -5 , -5 });
		points.push_back(Vector2{ -5 , 5 });
		points.push_back(Vector2{ 5 , 0 });

		Model* model = new Model{ points, color };
		Transform transform{ m_transform.position, m_transform.rotation, 1 };

		Bullet* bullet = new Bullet{ 400.f, transform, model };
		bullet->SetLifespan(1);
		bullet->SetTag("Player");
		m_scene->AddActor(bullet);
	}

	Actor::Update(dt);

}
