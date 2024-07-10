#include "Renderer.h"
#include "Vector2.h"
#include "Input.h"
#include "Input.cpp"
#include "Particle.h"
#include "Random.h"
#include "ETime.h"
#include "MathUtil.h"
#include "Model.h"
#include <fmod.hpp>

#include <SDL.h>
#include <iostream>
#include <cstdlib>
#include <vector>

int main(int argc, char* argv[])
{
	// create systems
	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("Game Engine", 800, 600);

	Input input;
	input.Initialize();

	Time time;

	std::vector<Particle> particles;
	float offset = 0.0f;

std::vector<Vector2> points;
	points.push_back(Vector2(-5, 5));
	points.push_back(Vector2(0, -5));
	points.push_back(Vector2(5, 5));
	points.push_back(Vector2(-5, 5));

	Model model{ points, Color{1,1,1,0} };
	Vector2 postion (400, 300);
	float rotation = 0;

	// create audio system
	FMOD::System* audio;
	FMOD::System_Create(&audio);

	std::vector<FMOD::Sound*> sounds;
	FMOD::Sound* sound = nullptr;
	audio->playSound(sound, 0, false, nullptr);

	void* extradriverdata = nullptr;
	audio->init(32, FMOD_INIT_NORMAL, extradriverdata);

	audio->createSound("test.wav", FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);

	audio->createSound("bass.wav", FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);

	audio->createSound("snare.wav", FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);

	audio->createSound("open-hat.wav", FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);
	

	// main loop
	bool quit = false;
	while (!quit)
	{
		time.Tick();
		//std::cout << time.GetTime() << std::endl;

		//INPUT
		input.Update();
		audio->update();

		if (input.GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}

		if (input.GetKeyDown(SDL_SCANCODE_Q) && !input.GetPreviousKeyDown(SDL_SCANCODE_Q))
		{
		audio->playSound(sounds[1], 0, false, nullptr);
		}
		if (input.GetKeyDown(SDL_SCANCODE_W) && !input.GetPreviousKeyDown(SDL_SCANCODE_W))
		{
			audio->playSound(sounds[2], 0, false, nullptr);
		}
		if (input.GetKeyDown(SDL_SCANCODE_E) && !input.GetPreviousKeyDown(SDL_SCANCODE_E))
		{
			audio->playSound(sounds[3], 0, false, nullptr);
		}

		Vector2 velocity{ 0,0 };
		if (input.GetKeyDown(SDL_SCANCODE_LEFT)) velocity.x = -100;
		if (input.GetKeyDown(SDL_SCANCODE_RIGHT)) velocity.x = 100;
		if (input.GetKeyDown(SDL_SCANCODE_UP)) velocity.y = -100;
		if (input.GetKeyDown(SDL_SCANCODE_DOWN)) velocity.y = 100;

		postion = postion + velocity * time.GetDeltaTime();
		rotation = velocity.Angle(); //rotation + time.GetDeltaTime();

		// UPDATE
		Vector2 mousePosition = input.GetMousePosition();
		//if (input.GetMouseuttonDown(0))
		//{
		//	//std::cout << "mouse pressed" << std::endl;
		//	for (int i = 0; i < 10; i++) {
		//		particles.push_back(Particle{ mousePosition, randomOnUnitCirlce() * randomf(10,100), randomf(1.0f, 5.0f) });
		//	}
		//}

		//for (Particle& particle : particles)
		//{
		//	particle.Update(time.GetDeltaTime());

		//	if (particle.position.x > 800) particle.position.x = 0;
		//	if (particle.position.x < 0) particle.position.x = 800;
		//}

		// DRAW
		// clear screen
		renderer.SetColor(0, 0, 0, 0);
		renderer.BeginFrame();

		// draw shape
		renderer.SetColor(255, 255, 255, 0);
		for (Particle particle : particles)
		{
			particle.Update(time.GetDeltaTime());
			particle.Draw(renderer);
		}

		float radius = 30.0f;
		offset += (90 + time.GetDeltaTime());
		for (float angle = 0; angle < 360; angle += 360 / 30)
		{

			float x = Math::Cos(Math::DegtToRad(angle + offset)) * Math::Sin(offset) * radius;
			float y = Math::Sin(Math::DegtToRad(angle + offset)) * Math::Sin(offset) * radius;

			//renderer.DrawRect(800 + x, 300 + y, 4.0f, 4.0f);
		}

		model.Draw(renderer, postion, 0, 5);

		// show screen
		renderer.EndFrame();
	}

	return 0;
}
