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

	// Rainbow vertex colours
	//_vertices [ 0 ].SetColour ( 1.0f, 0.0f, 0.0f );
	//_vertices [ 1 ].SetColour ( 0.0f, 1.0f, 0.0f );
	//_vertices [ 2 ].SetColour ( 0.0f, 0.0f, 1.0f );

	_vertices [ 0 ].SetTexture ( 0.0f, 0.0f );
	_vertices [ 1 ].SetTexture ( 1.0f, 0.0f );
	_vertices [ 2 ].SetTexture ( 0.5f, 1.0f );

	_indices [ 0 ] = 0;
	_indices [ 1 ] = 1;
	_indices [ 2 ] = 2;

	// create a mesh object
	//_mesh.SetMesh ( _vertices, 3, nullptr, 0 );
	_mesh.SetMesh( _vertices, 3, _indices, 3 );

	_texture.LoadTexture ( "bricks.jpg" );

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

	float sinTime = sinf ( getTime ( ) * 0.5f );
	_transform.SetPos ( glm::vec3 ( sinTime, 0.0f, 0.0f ) );
	_transform.SetRot ( glm::vec3 ( 0.0f, 0.0f, getTime ( ) * 5 ) );
	_transform.SetScale ( glm::vec3 ( sinTime , sinTime , sinTime ) );

	// bind and update the shader
	_shaderProgram.Bind ( );
	_shaderProgram.Update ( _transform );
	_texture.Bind ( 0u );

	// draw the mesh
	_mesh.Draw ( );

	_gameDisplay.swapBuffer();
}