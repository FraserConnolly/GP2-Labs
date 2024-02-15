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

void MainGame::initSystems ( )
{
	_gameDisplay.initDisplay ( );

	// enable depth testing
	glEnable ( GL_DEPTH_TEST );

#pragma region Vertices for a triangle


	_triangleVertices [ 0 ] = Vertex ( -0.5f, -0.5f, 0.0f );
	_triangleVertices [ 1 ] = Vertex ( 0.5f, -0.5f, 0.0f );
	_triangleVertices [ 2 ] = Vertex ( 0.0f, 0.5f, 0.0f );

	_triangleVertices [ 0 ].SetPosition ( 0.0f, 0.0f, 0.0f );
	_triangleVertices [ 1 ].SetPosition ( 0.5f, 0.0f, 0.0f );
	_triangleVertices [ 2 ].SetPosition( 0.25f, 0.5f, 0.0f );

	// Rainbow vertex colours
	//_vertices [ 0 ].SetColour ( 1.0f, 0.0f, 0.0f );
	//_vertices [ 1 ].SetColour ( 0.0f, 1.0f, 0.0f );
	//_vertices [ 2 ].SetColour ( 0.0f, 0.0f, 1.0f );

	_triangleVertices [ 0 ].SetTexture ( 0.0f, 0.0f );
	_triangleVertices [ 1 ].SetTexture ( 1.0f, 0.0f );
	_triangleVertices [ 2 ].SetTexture ( 0.5f, 1.0f );

	_triangleIndices [ 0 ] = 0;
	_triangleIndices [ 1 ] = 1;
	_triangleIndices [ 2 ] = 2;

#pragma endregion

#pragma region vertices for a cube

	// raw vertices for a cube with texture coordinates
	float vertices[ ] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	for ( size_t i = 0, j = 0; j < 36; j++ )
	{
		float x, y, z, u, v;
		x = vertices [ i++ ];
		y = vertices [ i++ ];
		z = vertices [ i++ ];
		u = vertices [ i++ ];
		v = vertices [ i++ ];
		_cubeVertices [ j ].SetPosition ( x, y, z );
		_cubeVertices [ j ].SetTexture ( u, v );
	}

#pragma endregion

	// create a mesh object
	//_mesh.SetMesh ( _vertices, 3, nullptr, 0 );
	//_mesh.SetMesh( _triangleVertices, 3, _triangleIndices, 3 );
	_mesh.SetMesh ( _cubeVertices, 36, nullptr, 0 );

	_texture.LoadTexture ( "bricks.jpg" );

	_mainCamera.GetTransform ( ).SetPosition ( glm::vec3 ( 0.5f, 0.5f, 5.0f ) );
	
	_shaderProgram.LoadDefaultShaders ( );
	_shaderProgram.SetCamera ( &_mainCamera );
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
	//_transform.SetPos ( glm::vec3 ( sinTime, 0.0f, 0.0f ) );
	_transform.SetRotation ( 0.0f, getTime(), getTime ( ) ) ;
	//_transform.SetScale ( glm::vec3 ( sinTime , sinTime , sinTime ) );
	_transform.SetScale ( 2.0f );

	float t = glm::clamp ( ( sinf ( getTime ( ) * 0.5f ) + 1 ) /2, 0.0f, 1.0f );
	//float fov = 20 * ( 1.f - t ) + 60 * t;
	//_mainCamera.SetFoV ( fov );

	float z = 2.0f * ( 1.f - t ) + 10.0f * t;
	//_mainCamera.GetTransform ( ).SetPosition ( 0.0f, 0.0f, z );
	//_mainCamera.GetTransform ( ).SetPosition ( 0.0f, 0.0f, z );

	// bind and update the shader
	_shaderProgram.Bind ( );
	_shaderProgram.Update ( _transform );
	_texture.Bind ( 0u );

	// draw the mesh
	_mesh.Draw ( );

	_gameDisplay.swapBuffer();
}