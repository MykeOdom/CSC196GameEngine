#include "Engine.h"

Engine g_engine;

bool Engine::Initialize()
{
    m_renderer = new Renderer();
    m_input = new Input();
    m_audio = new Audio();

    m_renderer->Initialize();
    m_renderer->CreateWindow("Game Engine", 800, 600);
    m_input->Initialize();
    m_audio->Initialize();

    return true;
}

void Engine::shutDown()
{
    m_renderer->Shutdown();
    m_input->Shutdown();
    m_audio->Shutdown();
}

void Engine::update()
{
    m_input->Update();
    m_audio->Update();
}
