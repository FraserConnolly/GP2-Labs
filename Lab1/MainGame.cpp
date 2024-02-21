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
	
	_keyboardInput.registerKey ( SDLK_LEFT );
	_keyboardInput.registerKey ( SDLK_RIGHT );
	_keyboardInput.registerKey ( SDLK_UP );
	_keyboardInput.registerKey ( SDLK_DOWN );

#pragma region Vertices for a triangle

	_triangleVertices [ 0 ] = Vertex1P1D1U ( -0.5f, -0.5f, 0.0f );
	_triangleVertices [ 1 ] = Vertex1P1D1U ( 0.5f, -0.5f, 0.0f );
	_triangleVertices [ 2 ] = Vertex1P1D1U ( 0.0f, 0.5f, 0.0f );

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
	//_mesh.SetMesh ( _cubeVertices, 36, nullptr, 0 );
	_mesh.loadObjModel ( "monkey3.obj" );

	_texture.LoadTexture ( "bricks.jpg" );

	_mainCamera.GetTransform ( ).SetPosition ( glm::vec3 ( 0.5f, 0.5f, 5.0f ) );
	_mainCamera.SetCameraTarget ( glm::vec3 ( 0.0f, 0.0f, 0.0f ) );

	_shaderProgram.LoadDefaultShaders ( );
	_shaderProgram.SetCamera ( &_mainCamera );
}

void MainGame::gameLoop()
{
	while (_gameState != GameState::EXIT)
	{
		float newTime = _gameDisplay.getTime ( );
		_deltaTime = newTime - _time;
		_time = newTime;

		// If delta time is too large (more than 1 second), we must have resumed from a breakpoint.
		// Frame-lock to the target rate of 30fps.
		// From Game Engine Architecture 3rd Edition by Jason Gregory 8.5.5 
		if ( _deltaTime > 1.0f )
		{
			_deltaTime = 1.0f / 30.0f;
		}

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
			case SDL_KEYUP:
				_keyboardInput.processKeyEvent ( test_event.key.keysym.sym, ( test_event.key.state == SDL_PRESSED ) , _deltaTime );
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
	
#pragma region Camera controls

	const float cameraSpeed = 2.0f; // adjust accordingly

	glm::vec3 newCameraPos = _mainCamera.GetTransform ( ).GetPosition ( );

	if ( _keyboardInput.isPressed ( SDLK_LEFT ) )
	{
		newCameraPos -= glm::normalize ( glm::cross ( _mainCamera.GetCameraFront( ), _mainCamera.GetCameraUp( ) ) ) * cameraSpeed * _deltaTime;
	}
	if ( _keyboardInput.isPressed ( SDLK_RIGHT ) )
	{
		newCameraPos += glm::normalize ( glm::cross ( _mainCamera.GetCameraFront ( ), _mainCamera.GetCameraUp ( ) ) ) * cameraSpeed * _deltaTime;
	}
	if ( _keyboardInput.isPressed ( SDLK_UP ) )
	{
		newCameraPos += _mainCamera.GetCameraFront ( ) * cameraSpeed * _deltaTime;
	}
	if ( _keyboardInput.isPressed ( SDLK_DOWN ) )
	{
		newCameraPos -= _mainCamera.GetCameraFront ( ) * cameraSpeed * _deltaTime;
	}

	if ( newCameraPos != _mainCamera.GetTransform ( ).GetPosition ( ) )
	{
		_mainCamera.GetTransform ( ).SetPosition ( newCameraPos );
	}

#pragma endregion


	float sinTime = sinf ( getTime ( ) * 0.5f );
	//_transform.SetPos ( glm::vec3 ( sinTime, 0.0f, 0.0f ) );
	//_transform.SetRotation ( 0.0f, getTime(), getTime ( ) ) ;
	//_transform.SetScale ( glm::vec3 ( sinTime , sinTime , sinTime ) );
	//_transform.SetScale ( 2.0f );

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