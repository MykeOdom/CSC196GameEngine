#pragma once
#include "Renderer.h"
#include "Audio.h"
#include "Input.h"

#include "ETime.h"

#include "Vector2.h"
#include "Input.cpp"

#include "Particle.h"
#include "ParticleSystem.h"

#include "Random.h"
#include "MathUtil.h"

#include "Model.h"
#include "Transform.h"

#include <fmod.hpp>
#include <SDL.h>
#include <memory>


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
	ParticleSystem& GetPS() { return *m_particleSystem; }

	Time& GetTime(){ return *m_time; }

	bool IsQuit(){ return false; }

private:

	bool quit = false;

	std::unique_ptr<Time> m_time{ nullptr };
	std::unique_ptr<Renderer> m_renderer{ nullptr };
	std::unique_ptr<Input> m_input{ nullptr };
	std::unique_ptr<Audio> m_audio{ nullptr };
	std::unique_ptr<ParticleSystem> m_particleSystem{ nullptr };
};

extern Engine g_engine;