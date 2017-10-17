#pragma once
#include<string>
#include<SDL2/SDL.h>
using namespace std;

class Display
{
public:
	Display(int witdh, int height, const string& title);

	void Update();
	bool isClosed();
	void Clear(float r, float g, float b, float a);
	~Display();
private:
	SDL_Window* m_window;
	SDL_GLContext m_glContext;
	bool m_isClosed;

};
