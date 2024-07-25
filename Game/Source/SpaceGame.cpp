#include "SpaceGame.h"
#include "Scene.h"
#include "Game.h"
#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "Pickup.h"
#include "GameData.h"

using namespace GameData;

bool SpaceGame::Initialize()
{
    m_scene = new Scene(this);

    m_font = new Font();
    m_font->Load("Begok.ttf", 20);
    m_textScore = new Text(m_font);
    m_textLives = new Text(m_font);
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
        m_state = eState::STARTLEVEL;
        break;
    case eState::STARTLEVEL:
        m_scene->RemoveAll();
        {
            Color color{ 1,1,1,0 };
            Model* model = new Model{ GameData::shipPoints, color };
            Transform transform{ {m_engine->GetRenderer().GetWidth() >> 1, m_engine->GetRenderer().GetHeight() >> 1}, 0, 5};
            auto player = std::make_unique<Player>(200.0f, transform, model);
            player->SetDamping(2.1f);
            player->SetTag("Player");
            m_scene->AddActor(std::move(player));
        }
        m_spawnTime = 3;
        m_spawnTimer = m_spawnTimer;
        m_state = eState::GAME;
        break;
    case eState::GAME:
        m_spawnTimer -= dt;
        if (m_spawnTimer <= 0)
        {
            m_spawnTime -= 0.2f;
            m_spawnTimer = m_spawnTime;

            //create enemy
            Color color{ 1,0,1,0 };
            Transform enemyTransform{ {(rand() % 800), (rand() % 600)}, 0, randomf(0.1f,0.5f) };
            auto* enemyModel = new Model{ GameData::shipPoints, color };
            auto enemy = std::make_unique<Enemy>( 200.0f, enemyTransform, enemyModel );
            enemy->SetDamping(2.0f);
            enemy->SetTag("Enemy");
            m_scene->AddActor(std::move(enemy));

            //create pickup
            Transform pickTransform{ {(rand() % 800), (rand() % 600)}, 0, randomf(0.1f,0.5f) };
            auto* pickModel = new Model{ GameData::shipPoints, color };
            auto pickup = std::make_unique<Pickup>( pickTransform, pickModel );
            pickup->SetTag("Pickup");
            m_scene->AddActor(std::move(pickup));
        }
        break;
    case eState::PLAYERDEAD:
        m_stateTimer -= dt;
        if (m_stateTimer <= 0)
        {
            m_state = eState::STARTLEVEL;
        }
        break;
    case eState::GAMEOVER:
        m_stateTimer -= dt;
        if (m_stateTimer <= 0)
        {
            m_state = eState::TITLE;
        }
        break;
    default:
        break;
    }
    m_scene->Update(dt);
}

void SpaceGame::Draw(Renderer & renderer)
{
    switch (m_state)
    {
    case SpaceGame::eState::TITLE:
        //draw text
        break;
    case SpaceGame::eState::GAMEOVER:
        //draw text
        break;
    default:
        break;
    }
    //draw score
    std::string text = "Score " + std::to_string(m_score);
    m_textScore->Create(renderer, text, { 0,1,0,1 });
    m_textScore->Draw(renderer, 20, 20);
    // 
    //draw lives
    text = "Lives " + std::to_string(m_score);
    m_textLives->Create(renderer, text, { 0,1,0,1 });
    m_textLives->Draw(renderer, 20, 40);

    m_scene->Draw(renderer);
}

void SpaceGame::OnPlayerDeath()
{
    m_lives--;
    m_state = (m_lives == 0) ? eState::GAMEOVER : eState::PLAYERDEAD;
}
