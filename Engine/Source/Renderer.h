#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

using namespace std;

class Renderer
{
public:
	Renderer() = default;

	bool Initialize();
	void Shutdown();

	bool CreateWindow(std::string title, int width, int height);

	void BeginFrame();

	void EndFrame();

	int GetWidth() const { return m_width; }
	int GetHeight() const { return m_height; }

	void SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

	void DrawLine(float x1, float y1, float x2, float y2);
	void DrawPoint(int x, int y);
	void DrawPoint(float x, float y);
	void DrawRect(int x, int y, int w, int h);
	void DrawRect(float x, float y, float w, float h);

	friend class Text;

private:
	SDL_Window* m_window{ nullptr };
	SDL_Renderer* m_renderer{ nullptr };

	int m_width{ 0 };
	int m_height{ 0 };
};