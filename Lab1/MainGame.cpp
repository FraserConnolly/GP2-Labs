#include "MainGame.h"
#include <iostream>
#include <string>

MainGame::MainGame()
	:_gameState(GameState::PLAY)
{
}

MainGame::~MainGame()
{
}

void MainGame::run()
{
	initSystems();
	gameLoop();
}

void MainGame::initSystems()
{
	_gameDisplay.initDisplay();
}

void MainGame::gameLoop()
{
	while (_gameState != GameState::EXIT)
	{
		processInput();
		drawGame();
	}
}

void MainGame::processInput()
{
	SDL_Event test_event;

	while (SDL_PollEvent(&test_event)) {
		switch (test_event.type) {
			case SDL_KEYDOWN:
				break;

			case SDL_KEYUP:
				break;
			case SDL_QUIT:
				_gameState = GameState::EXIT;
				break;
		}
	}
}

void MainGame::drawGame()
{
	glClearDepth(1.0); 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear colour and depth buffer - set colour to colour defined in glClearColor

	
	// old code for testing only 
	glEnableClientState(GL_COLOR_ARRAY); 
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f);	
	glVertex2f(0, 0);
	glVertex2f(0, 500);
	glVertex2f(500, 500);
	glEnd();

	_gameDisplay.swapBuffer();
}