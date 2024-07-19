#pragma once
#include "Game.h"

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
	SpaceGame(Engine* engine) : Game{engine} {}

	bool Initialize() override;
	void ShutDown() override;
	void Update(float dt) override;
	void Draw(Renderer& renderer) override;

private:
	eState m_state{ eState::TITLE };
	float m_spawnTimer{ 0 };
	float m_spawnTime{ 0 };

};