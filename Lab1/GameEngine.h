#pragma once

#include <SDL\SDL.h>
#include <GL\glew.h>

#include "Display.h" 
#include "GameObjectManager.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "GameObject.h"
#include "Camera.h"
#include "CameraFlyController.h"

#include "ConsoleDebugScene.h"

enum class GameState{PLAY, EXIT};

class GameEngine
{
public:

	GameEngine();
	~GameEngine();

	void run();

private:

	void initSystems();
	void processInput();
	void gameLoop();
	void shutdown ();
	void drawGame();

	Vertex1P1D1U _triangleVertices[ 3 ];
	unsigned int _triangleIndices [ 3 ];
	
	Vertex1P1D1U _cubeVertices [ 36 ];
	GameObjectManager _gameObjectManager;
	MeshRenderer _mesh;
	Texture _texture;
	GameObject * m_monkey;
	GameObject * m_mainCamera;
	Display _gameDisplay;
	GameState _gameState;
	Shader _shaderProgram;
	Camera * _mainCamera;
	CameraFlyController * _flyController;

	ConsoleDebugScene _debugScene;

};

