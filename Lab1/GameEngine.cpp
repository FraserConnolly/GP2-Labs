#include "GameEngine.h"

#include <iostream>
#include <string>
#include "GameObject.h"
#include "Time.h"
#include "Input.h"
#include "Rotator.h"
#include "Renderer.h"

GameEngine::GameEngine() :
	_gameState(GameState::PLAY),
	_triangleIndices( )
{
}

GameEngine::~GameEngine()
{
}

void GameEngine::run()
{
	initSystems();
	gameLoop();
	shutdown();
}

void GameEngine::initSystems ( )
{
	_gameDisplay.initDisplay ( );

	Time::StartUp ( );
	Input::StartUp ( );
	Renderer::Startup ( );

	Input::RegisterKey ( SDLK_ESCAPE ); // escape

	SDL_SetRelativeMouseMode ( SDL_TRUE );

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

	m_monkey = _gameObjectManager.CreateObject ( );
	_mesh = (MeshRenderer *) m_monkey->AddComponent ( ComponentTypes::MESH_RENDERER );
	Rotator * r = (Rotator *) m_monkey->AddComponent ( ComponentTypes::ROTATOR );
	r -> SetRotationAxis ( false, true, false );

	m_mainCamera = _gameObjectManager.CreateObject ( );
	_mainCamera = ( Camera * ) m_mainCamera->AddComponent ( ComponentTypes::CAMERA );

	_flyController = ( CameraFlyController * ) m_mainCamera->AddComponent ( ComponentTypes::CAMERA_FLY_CONTROLLER );
	_flyController->SetCamera ( *_mainCamera );

	_mainCamera->GetGameObject ( ).GetTransform ( ).SetPosition ( glm::vec3 ( 0.5f, 0.5f, 5.0f ) );
	_mainCamera->SetCameraTarget ( glm::vec3 ( 0.0f, 0.0f, 0.0f ) );

	_shaderProgram = new Shader ( );
	_shaderProgram->LoadDefaultShaders ( );
	_shaderProgram->SetCamera ( _mainCamera );

	// create a mesh object
	//_mesh.SetMesh ( _vertices, 3, nullptr, 0 );
	//_mesh.SetMesh( _triangleVertices, 3, _triangleIndices, 3 );
	//_mesh.SetMesh ( _cubeVertices, 36, nullptr, 0 );
	_mesh->loadObjModel ( "monkey3.obj" );

	_texture = new Texture ( );
	_texture->LoadTexture ( "bricks.jpg" );

	_material = new Material ( _shaderProgram );
	_material->SetTexture ( "diffuse", _texture );

	_mesh->SetMaterial ( _material );

	_debugScene.initaliseScene ( 0 );
	//_debugScene.SetTransformToMonitor ( _mainCamera->GetTransform ( ) );
	_debugScene.SetTransformToMonitor ( m_monkey->GetTransform( ) );
}

void GameEngine::gameLoop()
{
	while (_gameState != GameState::EXIT)
	{
		float newTime = _gameDisplay.getTime ( );
		Time::s_instance->m_deltaTime = newTime - Time::s_instance->m_time;
		Time::s_instance->m_time = newTime;

		// If delta time is too large (more than 1 second), we must have resumed from a breakpoint.
		// Frame-lock to the target rate of 30fps.
		// From Game Engine Architecture 3rd Edition by Jason Gregory 8.5.5 
		if ( Time::s_instance->m_deltaTime > 1.0f )
		{
			Time::s_instance->m_deltaTime = 1.0f / 30.0f;
		}

		processInput();
		_gameObjectManager.UpdateObjects ( );
		drawGame();
		_debugScene.processFrame ( );
	}
}

void GameEngine::shutdown ( )
{ 
	_gameObjectManager.DeleteAllObjects ( );
	Time::Shutdown ( );
	Input::Shutdown ( );
	Renderer::Shutdown ( );
	SDL_SetRelativeMouseMode ( SDL_FALSE );
}

void GameEngine::processInput()
{
	Input::Service ( );

	SDL_Event eventData;
	
	while (SDL_PollEvent(&eventData)) {
		switch (eventData.type) {
			case SDL_KEYDOWN:
			case SDL_KEYUP:
				Input::ProcessKeyEvent( eventData.key.keysym.sym, ( eventData.key.state == SDL_PRESSED ) );
				break;
			case SDL_MOUSEWHEEL:
				// note that in later version of SDL a float precision version of this data is available.
				Input::ProcessWheel ( eventData.wheel.x, eventData.wheel.y );
				break;
			case SDL_QUIT:
				_gameState = GameState::EXIT;
				break;
		}
	}

	if ( Input::IsKeyPressed ( SDLK_ESCAPE ) )
	{
		_gameState = GameState::EXIT;
	}
}

void GameEngine::drawGame()
{
	_gameDisplay.clearDisplay ( );
	
	Renderer::Service ( );

	_gameDisplay.swapBuffer();
}

