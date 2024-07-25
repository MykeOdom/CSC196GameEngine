#include "Particle.h"

void Particle::Initialize(const Data& data)
{
	isActive = true;
	position = data.position;
	velocity = data.velocity;
	lifespan = data.lifespan;
	//add the colors line by line
}

void Particle::Update(float dt)
{
	position = position + (velocity) * dt;
	if (lifespan != 0) 
	{
		lifespan -= dt;
	}
	if (lifespan <= 0) isActive = false;
}

//void Particle::Draw(Renderer renderer)
//{
//	if (lifespan >= 0) 
//	{
//		renderer.DrawPoint(position.x, position.y);
//	}
//	
//
//}

void Particle::Draw(Renderer& renderer)
{
	if (lifespan >= 0)
	{
		renderer.SetColor(rand() % 256, rand() % 256, rand() % 256, 0);
		renderer.DrawPoint(position.x, position.y);
		renderer.DrawRect(position.x, position.y, 4.0f, 4.0f);
	}
}
