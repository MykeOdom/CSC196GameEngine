#include "SpaceGame.h"
#include "Scene.h"
#include "Game.h"
#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "GameData.h"

bool SpaceGame::Initialize()
{
    m_scene = new Scene();

    return true;
}

void SpaceGame::ShutDown()
{
}

void SpaceGame::Update(float dt)
{
	switch (m_state)
	{
	case eState::TITLE:
		if (m_engine->GetInput().GetKeyDown(SDL_SCANCODE_SPACE))
		{
			m_state = eState::STARTGAME;
		}
		break;
	case eState::STARTGAME:
		m_score = 0;
		m_state = eState::STARTGAME;
		break;
	case eState::STARTLEVEL:
		{
		Transform transform{ {randomf(rand() % 800) , randomf(rand() % 600) }, 0, randomf(1,5) };
		Model* model = new Model{ GameData::shipPoints, Color(1,0,0) };
		Player* player = new Player(randomf(100, 200), transform, model);
		player->SetDamping(1.5f);
		player->SetTag("Player");
		m_scene->AddActor(player);
		}
		m_spawnTime = 3;
		m_spawnTimer = m_spawnTime;
		m_state = eState::STARTLEVEL;
		break;
	case eState::GAME:
		m_spawnTimer -= dt;
		if (m_spawnTimer <= 0)
		{
			m_spawnTimer;
		}
		break;
	case eState::PLAYERDEAD:
		break;
	case eState::GAMEOVER:
		break;
	default:
		break;
	}

    m_scene->Update(dt);
}

void SpaceGame::Draw(Renderer& renderer)
{
	switch (m_state)
	{
	case SpaceGame::eState::TITLE:
		//Draw text "Game Title"
		break;
	case SpaceGame::eState::GAMEOVER:
		//Draw text "Game Title"
		break;
	default:
		break;
	}

	//draw score
	//draw lives

    m_scene->Draw(renderer);
}
