#include "..\..\Game\Source\Bullet.h"
#include "Engine.h"

void Bullet::Update(float dt)
{
	Particle::Data data
	{
		m_transform.position,
		Vector2{1,0}.Rotate(randomf(Math::TwoPi)),
		randomf(0.5f, 2.0f)
	};
	g_engine.GetPS().AddParticle(data);

	m_velocity = Vector2{ 1,0 }.Rotate(m_transform.rotation) * m_speed;

	m_transform.position.x = Math::Wrap(m_transform.position.x, (float)g_engine.GetRenderer().GetWidth());
	m_transform.position.y = Math::Wrap(m_transform.position.y, (float)g_engine.GetRenderer().GetHeight());

	Actor::Update(dt);
}