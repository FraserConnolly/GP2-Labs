#include "Display.h"


Display::Display()
{
	_window = nullptr; //initialise to generate null access violation for debugging. 
	_screenWidth = 1024;
	_screenHeight = 768; 
}

Display::~Display()
{
}

void Display::returnError(std::string errorString)
{
	cout << errorString << '\n';
	cout << "Press any key to quit.";
	char c;
	cin >> c;

	SDL_Quit();
}

void Display::swapBuffer()
{
	SDL_GL_SwapWindow(_window);
}

void Display::initDisplay()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	_window = SDL_CreateWindow("Offstage Controls",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		_screenWidth,
		_screenHeight, SDL_WINDOW_OPENGL);

	if (_window == nullptr)
	{
		returnError("Failed to create window.");
		return;
	}

	SDL_GLContext glContext = SDL_GL_CreateContext(_window);

	if (glContext == nullptr)
	{
		returnError("Failed to OpenGL context.");
		return;
	}

	GLenum error = glewInit();

	if (error != GLEW_OK)
	{
		returnError("GLEW failed to initialise.");
		return;
	}

	glClearColor(0.0f, 1.0f, 1.0f, 1.0f);

}