#pragma once
#include "Vector2.h"
#include "Renderer.h"

struct Particle
{
	Vector2 position{ 0,0 };
	Vector2 velocity{ 0,0 };
	float lifespan{ 0 };

	Particle() = default;

	Particle(Vector2 postition, Vector2 velocity) :
		position {postition}, 
		velocity {velocity} 
	{}
	Particle(Vector2 postition, Vector2 velocity, float life) :
		position {postition}, 
		velocity {velocity}, 
		lifespan {life} 
	{} 

	void Update(float dt); // delta time (how much time has gone by)
	void Draw(Renderer& renderer);

};