#include "MainGame.h"

#include <iostream>
#include <string>

MainGame::MainGame() :
	_gameState(GameState::PLAY),
	_triangleIndices( )
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
	
	_keyboardInput.registerKey ( SDLK_a ); // left
	_keyboardInput.registerKey ( SDLK_d ); // right
	_keyboardInput.registerKey ( SDLK_w ); // forward
	_keyboardInput.registerKey ( SDLK_s ); // back
	_keyboardInput.registerKey ( SDLK_q ); // down
	_keyboardInput.registerKey ( SDLK_e ); // up

	_flyController.SetCamera ( _mainCamera );

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

	_debugScene.initaliseScene ( 0 );
	_debugScene.SetTransformToMonitor ( _mainCamera.GetTransform( ) );
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
		_debugScene.processFrame ( );
	}
}

void MainGame::processInput()
{
	_mouseInput.ResetMouseOffsets ( );

	SDL_Event eventData;
	while (SDL_PollEvent(&eventData)) {
		switch (eventData.type) {
			case SDL_KEYDOWN:
			case SDL_KEYUP:
				_keyboardInput.processKeyEvent ( eventData.key.keysym.sym, ( eventData.key.state == SDL_PRESSED ) , _deltaTime );
				break;
				
			case SDL_MOUSEMOTION:
				_mouseInput.ProcessMouseRelativePosition ( eventData.motion.xrel, eventData.motion.yrel );
				break;

			case SDL_MOUSEWHEEL:
				// note that in later version of SDL a float precision version of this data is avilable.
				_mouseInput.ProcessWheel ( eventData.wheel.x, eventData.wheel.y );
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

	if ( _keyboardInput.isPressed ( SDLK_a ) )
	{
		_flyController.ProcessKeyboard ( Camera_Movement::LEFT, _deltaTime );
	}
	if ( _keyboardInput.isPressed ( SDLK_d ) )
	{
		_flyController.ProcessKeyboard ( Camera_Movement::RIGHT, _deltaTime );
	}
	if ( _keyboardInput.isPressed ( SDLK_w ) )
	{
		_flyController.ProcessKeyboard ( Camera_Movement::FORWARD, _deltaTime );
	}
	if ( _keyboardInput.isPressed ( SDLK_s ) )
	{
		_flyController.ProcessKeyboard ( Camera_Movement::BACKWARD, _deltaTime );
	}
	if ( _keyboardInput.isPressed ( SDLK_e ) )
	{
		_flyController.ProcessKeyboard ( Camera_Movement::UP, _deltaTime );
	}
	if ( _keyboardInput.isPressed ( SDLK_q ) )
	{
		_flyController.ProcessKeyboard ( Camera_Movement::DOWN, _deltaTime );
	}

	_flyController.ProcessMouseMovement ( _mouseInput.GetXOffset ( ), _mouseInput.GetYOffset ( ) );
	_flyController.ProcessMouseScroll ( _mouseInput.GetVerticalWheelOffset ( ) );
	_flyController.UpdateCamera ( );

#pragma endregion

	float sinTime = sinf ( getTime ( ) * 0.5f );
	//_transform.SetPos ( glm::vec3 ( sinTime, 0.0f, 0.0f ) );
	_transform.SetRotation ( 0.0f, getTime ( ), 0.0f ) ;
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

//// glfw: whenever the mouse moves, this callback is called
//// -------------------------------------------------------
//void mouse_callback ( GLFWwindow * window, double xposIn, double yposIn )
//{
//	float xpos = static_cast< float >( xposIn );
//	float ypos = static_cast< float >( yposIn );
//
//	if ( firstMouse )
//	{
//		lastX = xpos;
//		lastY = ypos;
//		firstMouse = false;
//	}
//
//	float xoffset = xpos - lastX;
//	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
//
//	lastX = xpos;
//	lastY = ypos;
//
//	camera.ProcessMouseMovement ( xoffset, yoffset );
//}
