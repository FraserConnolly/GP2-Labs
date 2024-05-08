#include "GameEngine.h"

#include <iostream>
#include <string>
#include "GameObjectManager.h"
#include "GameObject.h"

#include "Time.h"
#include "Input.h"
#include "Rotator.h"
#include "Renderer.h"
#include "CameraFlyController.h"
#include "Audio Event Emitter.h"
#include "Audio Listener.h"
#include "Audio.h"

GameEngine::GameEngine ( ) { }

GameEngine::~GameEngine ( ) { }

void GameEngine::run ( )
{
	initSystems ( );
	gameLoop ( );
	shutdown ( );
}

void GameEngine::initSystems ( )
{
	_gameDisplay.initDisplay ( );

	SDL_SetRelativeMouseMode ( SDL_TRUE );

	Time::StartUp ( );
	Input::StartUp ( );
	Renderer::Startup ( );
	Audio::Startup ( );
	GameObjectManager::Startup ( );

	Input::RegisterKey ( SDLK_ESCAPE ); // escape

#pragma region Audio

	Audio::LoadBank ( "Master.bank", FMOD_STUDIO_LOAD_BANK_NORMAL );
	Audio::LoadBank ( "Master.strings.bank", FMOD_STUDIO_LOAD_BANK_NORMAL );
	//Audio::LoadEvent ( "event:/Lighthearted LOOP SHORT" );
	//Audio::SetEvent3dAttributes ( "event:/Lighthearted LOOP SHORT", glm::vec3 ( 0 ) );
	//Audio::PlayEvent ( "event:/Lighthearted LOOP SHORT" );

#pragma endregion

//#pragma region Vertices for a triangle
//
//	_triangleVertices [ 0 ] = Vertex1P1D1U ( -0.5f, -0.5f, 0.0f );
//	_triangleVertices [ 1 ] = Vertex1P1D1U ( 0.5f, -0.5f, 0.0f );
//	_triangleVertices [ 2 ] = Vertex1P1D1U ( 0.0f, 0.5f, 0.0f );
//
//	_triangleVertices [ 0 ].SetPosition ( 0.0f, 0.0f, 0.0f );
//	_triangleVertices [ 1 ].SetPosition ( 0.5f, 0.0f, 0.0f );
//	_triangleVertices [ 2 ].SetPosition ( 0.25f, 0.5f, 0.0f );
//
//	// Rainbow vertex colours
//	//_vertices [ 0 ].SetColour ( 1.0f, 0.0f, 0.0f );
//	//_vertices [ 1 ].SetColour ( 0.0f, 1.0f, 0.0f );
//	//_vertices [ 2 ].SetColour ( 0.0f, 0.0f, 1.0f );
//
//	_triangleVertices [ 0 ].SetTexture ( 0.0f, 0.0f );
//	_triangleVertices [ 1 ].SetTexture ( 1.0f, 0.0f );
//	_triangleVertices [ 2 ].SetTexture ( 0.5f, 1.0f );
//
//	_triangleIndices [ 0 ] = 0;
//	_triangleIndices [ 1 ] = 1;
//	_triangleIndices [ 2 ] = 2;
//
//#pragma endregion
//
//#pragma region vertices for a cube
//
//	// raw vertices for a cube with texture coordinates
//	float vertices[ ] = {
//	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
//	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
//	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
//
//	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
//	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//
//	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//
//	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//
//	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
//	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//
//	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
//	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
//	};
//
//	for ( size_t i = 0, j = 0; j < 36; j++ )
//	{
//		float x, y, z, u, v;
//		x = vertices [ i++ ];
//		y = vertices [ i++ ];
//		z = vertices [ i++ ];
//		u = vertices [ i++ ];
//		v = vertices [ i++ ];
//		_cubeVertices [ j ].SetPosition ( x, y, z );
//		_cubeVertices [ j ].SetTexture ( u, v );
//	}
//
//#pragma endregion

	auto mainCameraObj = GameObjectManager::CreateObject ( );
	auto mainCamera = ( Camera * ) mainCameraObj->AddComponent ( ComponentTypes::CAMERA );

	auto flyController = ( CameraFlyController * ) mainCameraObj->AddComponent ( ComponentTypes::CAMERA_FLY_CONTROLLER );
	flyController->SetCamera ( *mainCamera );

	mainCameraobj->GetTransform ( ).SetPosition ( glm::vec3 ( 0.5f, 0.5f, 5.0f ) );
	mainCamera->SetCameraTarget ( glm::vec3 ( 0.0f, 0.0f, 0.0f ) );
	mainCameraObj->AddComponent ( ComponentTypes::AUDIO_LISTENER );

	_shaderProgram = new Shader ( );
	_shaderProgram->LoadDefaultShaders ( );
	_shaderProgram->SetCamera ( mainCamera );

	_texture = new Texture ( );
	_texture->LoadTexture ( "bricks.jpg" );

	_material = new Material ( _shaderProgram );
	_material->SetTexture ( "diffuse", _texture );

	for ( size_t i = 0; i < 10; i++ )
	{
		auto obj = GameObjectManager::CreateObject ( );
		obj->GetTransform ( ).SetPosition ( (float) ( i * 3 ) , 0, 0 );

		// create a mesh object
		auto mesh = ( MeshRenderer * ) obj->AddComponent ( ComponentTypes::MESH_RENDERER );
		//mesh.SetMesh ( _vertices, 3, nullptr, 0 );
		//mesh.SetMesh( _triangleVertices, 3, _triangleIndices, 3 );
		//mesh.SetMesh ( _cubeVertices, 36, nullptr, 0 );
		mesh->loadObjModel ( "monkey3.obj" );

		mesh->SetMaterial ( _material );

		auto r = ( Rotator * ) obj->AddComponent ( ComponentTypes::ROTATOR );
		r->SetRotationAxis ( false, true, false );
	}

#pragma region Audio

	Audio::LoadBank ( "Master.bank", FMOD_STUDIO_LOAD_BANK_NORMAL );
	Audio::LoadBank ( "Master.strings.bank", FMOD_STUDIO_LOAD_BANK_NORMAL );
	Audio::LoadEvent ( "event:/Lighthearted LOOP SHORT" );
	Audio::PlayEvent ( "event:/Lighthearted LOOP SHORT" );

#pragma endregion


#if _DEBUG
	_debugScene.initaliseScene ( 0 );
	//_debugScene.SetTransformToMonitor ( _mainCamera->GetTransform ( ) );
	//_debugScene.SetTransformToMonitor ( m_monkey->GetTransform( ) );
#endif
}

void GameEngine::gameLoop ( )
{
	while ( _gameState != GameState::EXIT )
	{
		Time::Service ( _gameDisplay.getTime ( ) );

		processInput ( );

		GameObjectManager::Service ( );
		Audio::Service ( );

		drawGame ( );

#if _DEBUG
		_debugScene.processFrame ( );
#endif
	}
}

void GameEngine::shutdown ( )
{
	delete _material;
	delete _shaderProgram;
	delete _texture;
	GameObjectManager::Shutdown ( );
	Audio::Shutdown ( );
	Renderer::Shutdown ( );
	Input::Shutdown ( );
	Time::Shutdown ( );
	SDL_SetRelativeMouseMode ( SDL_FALSE );
}

void GameEngine::processInput ( )
{
	Input::Service ( );

	SDL_Event eventData;

	while ( SDL_PollEvent ( &eventData ) )
	{
		switch ( eventData.type )
		{
			case SDL_KEYDOWN:
			case SDL_KEYUP:
				Input::ProcessKeyEvent ( eventData.key.keysym.sym, ( eventData.key.state == SDL_PRESSED ) );
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

void GameEngine::drawGame ( )
{
	_gameDisplay.clearDisplay ( );
	Renderer::Service ( );
	_gameDisplay.swapBuffer ( );
}

