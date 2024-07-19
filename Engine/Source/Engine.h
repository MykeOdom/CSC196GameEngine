#pragma once
#include "Renderer.h"
#include "Audio.h"
#include "Input.h"

#include "ETime.h"

#include "Vector2.h"
#include "Input.cpp"
#include "Particle.h"
#include "Random.h"
#include "MathUtil.h"
#include "Model.h"
#include "Transform.h"
#include <fmod.hpp>
#include <SDL.h>

#define RENDERER g_engine.GetRenderer()


class Engine
{
public:
	Engine() = default;
	~Engine() = default;

	bool Initialize();
	void shutDown();

	void update();

	Renderer& GetRenderer() { return *m_renderer; }
	Input& GetInput() { return *m_input; }
	Audio& GetAudio() { return *m_audio; }

	Time& GetTime(){ return *m_time; }

	bool IsQuit(){ return true; }

private:

	bool quit = false;

	Time* m_time{ nullptr };

	Renderer* m_renderer{ nullptr };
	Input* m_input{ nullptr };
	Audio* m_audio{ nullptr };
};

extern Engine g_engine;