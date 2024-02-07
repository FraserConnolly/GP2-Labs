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

	// create an array of vertices
	_vertices [ 0 ] = Vertex ( -0.5f, -0.5f, 0.0f );
	_vertices [ 1 ] = Vertex ( 0.5f, -0.5f, 0.0f );
	_vertices [ 2 ] = Vertex ( 0.0f, 0.5f, 0.0f );

	_vertices [ 0 ].SetColour ( 1.0f, 0.0f, 0.0f );
	_vertices [ 1 ].SetColour ( 0.0f, 1.0f, 0.0f );
	_vertices [ 2 ].SetColour ( 0.0f, 0.0f, 1.0f );

	// create a mesh object
	_mesh.SetMesh( _vertices, 3 );

	_shaderProgram.LoadDefaultShaders ( );
}

void MainGame::gameLoop()
{
	while (_gameState != GameState::EXIT)
	{
		float newTime = _gameDisplay.getTime ( );
		_deltaTime = _time - newTime;
		_time = newTime;
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
	_gameDisplay.clearDisplay ( );
	
	// bind the shader
	_shaderProgram.Bind ( );

	//GLfloat greenValue = ( sin ( _time ) / 2.0f ) + 0.5f;
	//_shaderProgram.SetUniform ( "ourColor", 0.0f, greenValue, 0.0f, 1.0f );

	// draw the mesh
	_mesh.Draw ( );

	_gameDisplay.swapBuffer();
}