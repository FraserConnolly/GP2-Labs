#pragma once

#include <SDL\SDL.h>
#include <GL\glew.h>

#include "Display.h" 
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Transform.h"

enum class GameState{PLAY, EXIT};

class MainGame
{
public:

	MainGame();
	~MainGame();

	void run();

	float getTime ( )
	{
		return _time;
	}

	float getDeltaTime ( )
	{
		return _deltaTime;
	}

private:

	void initSystems();
	void processInput();
	void gameLoop();
	void drawGame();

	// in seconds
	float _time = 0.0f;
	float _deltaTime = 0.0f;
	Vertex _vertices[ 3 ];
	unsigned int _indices [ 3 ];
	Mesh _mesh;
	Texture _texture;
	Transform _transform;
	Display _gameDisplay;
	GameState _gameState;
	Shader _shaderProgram ;

};

