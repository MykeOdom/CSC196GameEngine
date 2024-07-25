#pragma once
#include "Game.h"
#include "Font.h"
#include "Text.h"

class SpaceGame : public Game
{
public:
	enum class eState
	{
		TITLE,
		STARTGAME,
		STARTLEVEL,
		GAME,
		PLAYERDEAD,
		GAMEOVER
	};
public:
	SpaceGame(Engine* engine) : Game{ engine } {}
	bool Initialize() override;
	void ShutDown() override;
	void Update(float dt) override;

	void Draw(Renderer& renderer) override;

	void OnPlayerDeath();
protected:
	eState m_state{ eState::TITLE };
	float m_stateTimer{ 0 };

	float m_spawnTimer{ 0 };
	float m_spawnTime{ 0 };


	Font* m_font{ nullptr };
	Text* m_textScore{ nullptr };
	Text* m_textLives{ nullptr };
};