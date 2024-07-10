#pragma once
#include "Vector2.h"

struct Transform
{
	Vector2 postion;
	float rotation;
	float scale;

	Transform() = default;
	Transform(Vector2 postion, float rotation = 0, float scale = 1) :
		postion{ postion },
		rotation{ rotation },
		scale{ scale }
	{}

};