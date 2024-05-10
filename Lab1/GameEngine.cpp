#include "GameEngine.h"

#include <iostream>
#include <string>

// Sub systems
#include "GameObjectManager.h"
#include "Time.h"
#include "Input.h"
#include "Renderer.h"
#include "CollisionManager.h"

#include "GameObject.h"

// Components
#include "Rotator.h"
#include "CameraFlyController.h"
#include "Audio Event Emitter.h"
#include "Audio Listener.h"
#include "Audio.h"
#include "Path Follow.h"

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
	CollisionManager::Startup ( );
	GameObjectManager::Startup ( );

	Input::RegisterKey ( SDLK_ESCAPE ); // escape

#pragma region Audio

	Audio::LoadBank ( "Master.bank", FMOD_STUDIO_LOAD_BANK_NORMAL );
	Audio::LoadBank ( "Master.strings.bank", FMOD_STUDIO_LOAD_BANK_NORMAL );

	// load and play background music - this event is set to loop in FMOD.
	// note that I am note setting 3D attributes for this event so it will 
	// essentially follow the listener.
	Audio::LoadEvent ( "event:/Lighthearted LOOP SHORT" );
	Audio::PlayEvent ( "event:/Lighthearted LOOP SHORT" );

#pragma endregion

	auto mainCameraObj = GameObjectManager::CreateObject ( );
	auto mainCamera = ( Camera * ) mainCameraObj->AddComponent ( ComponentTypes::CAMERA );

	auto flyController = ( CameraFlyController * ) mainCameraObj->AddComponent ( ComponentTypes::CAMERA_FLY_CONTROLLER );
	flyController->SetCamera ( *mainCamera );

	mainCameraObj->GetTransform ( ).SetPosition ( glm::vec3 ( 2.5f, 7.5f, 10.0f ) );
	mainCameraObj->GetTransform ( ).SetRotationEulerInDegrees ( -29, 0, 0 );
	mainCameraObj->AddComponent ( ComponentTypes::AUDIO_LISTENER );

	_shaderProgram = new Shader ( );
	_shaderProgram->LoadDefaultShaders ( );
	_shaderProgram->SetCamera ( mainCamera );

	_texture = new Texture ( );
	_texture->LoadTexture ( "bricks.jpg" );
	//_texture->LoadTexture ( "PolygonPrototype_Texture_01.png" );

	_material = new Material ( _shaderProgram );
	_material->SetTexture ( "diffuse", _texture );

	Transform * toFollow = nullptr;

	std::vector<glm::vec3> points;

	points.push_back ( glm::vec3 ( -2.5, 0, -2.5 ) );
	points.push_back ( glm::vec3 ( +2.5, 5, -2.5 ) );
	points.push_back ( glm::vec3 ( +2.5, 0, +2.5 ) );
	points.push_back ( glm::vec3 ( -2.5, 0, +2.5 ) );

	for ( size_t i = 0; i < points.size ( ) + 1; i++ )
	{
		auto obj = GameObjectManager::CreateObject ( );

		auto emitter = ( AudioEventEmitter * ) obj->AddComponent ( ComponentTypes::AUDIO_EVENT_EMITTER );
		emitter->SetCollisionBehaviour ( true, false );

		if ( i != points.size ( ) )
		{
			obj->GetTransform ( ).SetPosition ( points [ i ] );
			obj->GetTransform ( ).SetScale ( 1.0f );
			obj->AddComponent ( SPHERE_COLIDER );
		}
		else
		{
			// arrow
			obj->AddComponent ( SPHERE_COLIDER );
		}

		// create a mesh object
		auto mesh = ( MeshRenderer * ) obj->AddComponent ( ComponentTypes::MESH_RENDERER );
		//mesh.SetMesh ( _vertices, 3, nullptr, 0 );
		//mesh.SetMesh( _triangleVertices, 3, _triangleIndices, 3 );
		//mesh.SetMesh ( _cubeVertices, 36, nullptr, 0 );
		mesh->loadObjModel ( "monkey3.obj" );

		mesh->SetMaterial ( _material );

		auto r = ( Rotator * ) obj->AddComponent ( ComponentTypes::ROTATOR );

		if ( i != points.size ( ) )
		{
			switch ( i % 4 )
			{
				case 0:
					r->SetRotationAxis ( true, !true, !true );
					emitter->LoadEvent ( "event:/Orchestra 1st Star" );
					break;
				case 1:
					r->SetRotationAxis ( !true, true, !true );
					emitter->LoadEvent ( "event:/Orchestra 2nd Star" );
					break;
				case 2:
					r->SetRotationAxis ( !true, !true, true );
					emitter->LoadEvent ( "event:/Orchestra 3rd Star" );
					break;
				case 3:
					r->SetRotationAxis ( !true, !true, !true );
					emitter->LoadEvent ( "event:/Casual Win 1" );
					break;
			}
		}
		
		if ( i == points.size( ) )
		{
			mesh->loadObjModel ( "ArrowNegZ.obj" );
			obj->GetTransform ( ).SetPosition ( ( float ) ( 0 ), 0, 0 );
			r->SetRotationAxis ( !true, !true, !true );
			r->SetActive ( false );

			auto path = ( PathFollow * ) obj->AddComponent ( PATH_FOLLOW );
			
			for ( auto & point : points )
			{
				path->AddWayPoint ( point );
			}
			
			path->SetSpeed ( 2.5f );

			//toFollow = &obj->GetTransform ( );
		}
	}

#if _DEBUG
	_debugScene.initaliseScene ( 0 );
	_debugScene.SetTransformToMonitor ( mainCameraObj->GetTransform ( ) );
	if ( toFollow != nullptr )
	{
		_debugScene.SetTransformToMonitor ( *toFollow );
	}
#endif
}

void GameEngine::gameLoop ( )
{
	while ( _gameState != GameState::EXIT )
	{
		Time::Service ( _gameDisplay.getTime ( ) );

		processInput ( );
		CollisionManager::Service ( );
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
	CollisionManager::Shutdown ( );
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

