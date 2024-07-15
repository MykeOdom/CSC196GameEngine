#include "Engine.h"

#include <iostream>
#include <cstdlib>
#include <vector>

int main(int argc, char* argv[])
{
	g_engine.Initialize();
	Time time;

	// add audio sounds
	//g_engine.GetAudio()->AddSound("bass.wav");
	//g_engine.GetAudio()->AddSound("snare.wav");
	//g_engine.GetAudio()->AddSound("open-hat.wav");
	//g_engine.GetAudio()->AddSound("close-hat.wav");
	//g_engine.GetAudio()->AddSound("clap.wav");
	//g_engine.GetAudio()->AddSound("cowbell.wav");

	std::vector<Particle> particles;
	float offset = 0.0f;

std::vector<Vector2> points;
	points.push_back(Vector2(5, 0));
	points.push_back(Vector2(-5, -5));
	points.push_back(Vector2(-5, 5));
	points.push_back(Vector2(5, 0));
	Model model{ points, Color{1,0,0} };

	Transform transform{ {g_engine.GetRenderer()->getWidth() >> 1, g_engine.GetRenderer()->getHeight() >> 1}, 0, 5 };

	std::vector<Vector2> rock;
	rock.push_back(Vector2(5, 0));
	rock.push_back(Vector2(-5, 3));
	rock.push_back(Vector2(-5, 0));
	rock.push_back(Vector2(-5, -2));
	rock.push_back(Vector2(5, 2));
	rock.push_back(Vector2(5, 0));
	Model modelRock{ rock, Color{1,0,1} };
	
	Transform transformRock{ {g_engine.GetRenderer()->getWidth() >> 1, g_engine.GetRenderer()->getHeight() >> 1}, 0, 5 };

	// main loop
	bool quit = false;
	while (!quit)
	{
		time.Tick();
		//std::cout << time.GetTime() << std::endl;

		//INPUT
		g_engine.GetInput()->Update();
		g_engine.GetAudio()->Update();

		if (g_engine.GetInput()->GetKeyDown(SDL_SCANCODE_ESCAPE))
		{quit = true;}
		if (g_engine.GetInput()->GetKeyDown(SDL_SCANCODE_Q) && !g_engine.GetInput()->GetPreviousKeyDown(SDL_SCANCODE_Q)) {g_engine.GetAudio()->AddSound("bass.wav");}
		if (g_engine.GetInput()->GetKeyDown(SDL_SCANCODE_W) && !g_engine.GetInput()->GetPreviousKeyDown(SDL_SCANCODE_W)){g_engine.GetAudio()->AddSound("snare.wav");}
		if (g_engine.GetInput()->GetKeyDown(SDL_SCANCODE_E) && !g_engine.GetInput()->GetPreviousKeyDown(SDL_SCANCODE_E)){g_engine.GetAudio()->AddSound("open-hat.wav");}
		if (g_engine.GetInput()->GetKeyDown(SDL_SCANCODE_A) && !g_engine.GetInput()->GetPreviousKeyDown(SDL_SCANCODE_E)){g_engine.GetAudio()->AddSound("close-hat.wav");}
		if (g_engine.GetInput()->GetKeyDown(SDL_SCANCODE_S) && !g_engine.GetInput()->GetPreviousKeyDown(SDL_SCANCODE_E)){g_engine.GetAudio()->AddSound("clap.wav");}
		if (g_engine.GetInput()->GetKeyDown(SDL_SCANCODE_D) && !g_engine.GetInput()->GetPreviousKeyDown(SDL_SCANCODE_E)){g_engine.GetAudio()->AddSound("cowbell.wav");}


		float thrust = 0;
		if (g_engine.GetInput()->GetKeyDown(SDL_SCANCODE_UP)) thrust = 400;
		if (g_engine.GetInput()->GetKeyDown(SDL_SCANCODE_DOWN)) thrust = -400;

		if (g_engine.GetInput()->GetKeyDown(SDL_SCANCODE_LEFT)) transform.rotation -= Math::DegtToRad(100) * time.GetDeltaTime();
		if (g_engine.GetInput()->GetKeyDown(SDL_SCANCODE_RIGHT)) transform.rotation += Math::DegtToRad(100) * time.GetDeltaTime();


		Vector2 velocity = Vector2{ thrust, 0.0f }.Rotate(transform.rotation);
		transform.postion += velocity * time.GetDeltaTime();
		transform.postion.x = Math::Wrap(transform.postion.x, (float)g_engine.GetRenderer()->getWidth());
		transform.postion.y = Math::Wrap(transform.postion.y, (float)g_engine.GetRenderer()->getHeight());

		//transform.rotation = velocity.Angle(); //trandsform.rotation + time.GetDeltaTime();

		// UPDATE
		Vector2 mousePosition = g_engine.GetInput()->GetMousePosition();
		if (g_engine.GetInput()->GetMouseuttonDown(0))
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
		g_engine.GetRenderer()->SetColor(0, 0, 0, 0);
		g_engine.GetRenderer()->BeginFrame();

		// draw shape
		g_engine.GetRenderer()->SetColor(255, 255, 255, 0);
		for (Particle particle : particles)
		{
			particle.Update(time.GetDeltaTime());
			particle.Draw(*g_engine.GetRenderer());
		}

		float radius = 30.0f;
		offset += (90 + time.GetDeltaTime());
		for (float angle = 0; angle < 360; angle += 360 / 30)
		{

			float x = Math::Cos(Math::DegtToRad(angle + offset)) * Math::Sin(offset) * radius;
			float y = Math::Sin(Math::DegtToRad(angle + offset)) * Math::Sin(offset) * radius;

			//renderer.DrawRect(800 + x, 300 + y, 4.0f, 4.0f);
		}

		model.Draw(*g_engine.GetRenderer(), transform);
		modelRock.Draw(*g_engine.GetRenderer(), transformRock);

		// show screen
		g_engine.GetRenderer()->EndFrame();
	}

	return 0;
}
