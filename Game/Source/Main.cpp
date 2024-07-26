#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "Scene.h"
#include "GameData.h"
#include "SpaceGame.h"
#include "Font.h"
#include "Text.h"

#include <iostream>
#include <cstdlib>
#include <vector>

int main(int argc, char* argv[])
{
	g_engine.Initialize();
	SpaceGame* game = new SpaceGame(&g_engine);
	game->Initialize();

	g_engine.GetAudio().AddSound("cowbell.wav");


	while (!g_engine.IsQuit())
	{
		
		g_engine.update();
		game->Update(g_engine.GetTime().GetDeltaTime());
		
		g_engine.GetRenderer().SetColor(0, 0, 0, 0);
		g_engine.GetRenderer().BeginFrame();

		game->Draw(g_engine.GetRenderer());
		g_engine.GetPS().Draw(g_engine.GetRenderer());

		g_engine.GetRenderer().EndFrame();

	}
	g_engine.shutDown();

	return 0;
}

/*
float offset = 0.0f;

//actor
Model* model = new Model{ GameData::shipPoints, Color{1,0,0} };

Scene* scene = new Scene();
for (int i = 0; i < 10; i++) {
	Transform transform{ {randomf(rand() % 800) , randomf(rand() % 600) }, 0, randomf(1,5) };
	Player* player = new Player(randomf(100,200), transform, model);
	player->SetDamping(1.5f);
	player->SetTag("Player");
	scene->AddActor(player);
	float spawnTimer = 2.0f;
}


//fish
//std::vector<Vector2> rock;
//rock.push_back(Vector2(5, 0));
//rock.push_back(Vector2(-5, 3));
//rock.push_back(Vector2(-5, 0));
//rock.push_back(Vector2(-5, -2));
//rock.push_back(Vector2(5, 2));
//rock.push_back(Vector2(5, 0));
//Model modelRock{ rock, Color{1,0,1} };
//
//Transform transformRock{ {g_engine.GetRenderer().getWidth() >> 1, g_engine.GetRenderer().getHeight() >> 1}, 0, 5 };

// main loop
while(!g_engine.IsQuit())
{
	g_engine.update();

	//INPUT
	//if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_Q) && !g_engine.GetInput().GetPreviousKeyDown(SDL_SCANCODE_Q)) {g_engine.GetAudio().AddSound("bass.wav");}
	//if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_W) && !g_engine.GetInput().GetPreviousKeyDown(SDL_SCANCODE_W)){g_engine.GetAudio().AddSound("snare.wav");}
	//if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_E) && !g_engine.GetInput().GetPreviousKeyDown(SDL_SCANCODE_E)){g_engine.GetAudio().AddSound("open-hat.wav");}
	//if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_A) && !g_engine.GetInput().GetPreviousKeyDown(SDL_SCANCODE_E)){g_engine.GetAudio().AddSound("close-hat.wav");}
	//if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_S) && !g_engine.GetInput().GetPreviousKeyDown(SDL_SCANCODE_E)){g_engine.GetAudio().AddSound("clap.wav");}
	//if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_D) && !g_engine.GetInput().GetPreviousKeyDown(SDL_SCANCODE_E)){g_engine.GetAudio().AddSound("cowbell.wav");}



	// UPDATE
	scene->Update(g_engine.GetTime().GetDeltaTime());

	//spawnTimer -= time.GetDeltaTime();

	Vector2 mousePosition = g_engine.GetInput().GetMousePosition();
	if (g_engine.GetInput().GetMouseuttonDown(0))
	{
		//std::cout << "mouse pressed" << std::endl;
		for (int i = 0; i < 10; i++) {
			particles.push_back(Particle{ mousePosition, randomOnUnitCirlce() * randomf(10,100), randomf(1.0f, 5.0f) });
		}
	}

	for (Particle& particle : particles)
	{
		particle.Update(time.GetDeltaTime());

		if (particle.position.x > 800) particle.position.x = 0;
		if (particle.position.x < 0) particle.position.x = 800;
	}

	// DRAW
	// clear screen
	g_engine.GetRenderer().SetColor(0, 0, 0, 0);
	g_engine.GetRenderer().BeginFrame();

	// draw shape
	g_engine.GetRenderer().SetColor(255, 255, 255, 0);
	for (Particle particle : particles)
	{
		particle.Update(g_engine.GetTime().GetDeltaTime());
		particle.Draw(g_engine.GetRenderer());
	}

	float radius = 30.0f;
	offset += (90 + g_engine.GetTime().GetDeltaTime());
	for (float angle = 0; angle < 360; angle += 360 / 30)
	{

		float x = Math::Cos(Math::DegtToRad(angle + offset)) * Math::Sin(offset) * radius;
		float y = Math::Sin(Math::DegtToRad(angle + offset)) * Math::Sin(offset) * radius;

		//renderer.DrawRect(800 + x, 300 + y, 4.0f, 4.0f);
	}

	scene->Draw(g_engine.GetRenderer());
	//modelRock.Draw(g_engine.GetRenderer(), transformRock);

	// show screen
	g_engine.GetRenderer().EndFrame();
}
*/