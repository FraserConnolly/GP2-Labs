#pragma once
#include <SDL/SDL.h>
#include <GL\glew.h>
#include <iostream>
#include <string>
using namespace std;


class Display
{
public:
	Display();
	~Display();
	void initDisplay ( );
	void initDisplay ( const float width, const float height );
	void clearDisplay ( );
	void clearDisplay ( const float r, const float g, const float b, const float a);
	void swapBuffer();
	float getTime ( );

	float getWidth  ( ) const;
	float getHeight ( ) const;

private:

	void returnError(std::string errorString);

	SDL_Window* _window; //holds pointer to out window
	SDL_GLContext _glContext;
	int _screenWidth;
	int _screenHeight;
};

