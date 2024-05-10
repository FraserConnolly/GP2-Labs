#pragma once

#include <SDL\SDL.h>
#include <GL\glew.h>

#include "Display.h"

#if _DEBUG
#include "ConsoleDebugScene.h"
#endif

enum class GameState
{
	PLAY, EXIT
};

class Texture;
class Shader;
class Material;
class CubeMap;

class GameEngine
{
public:

	GameEngine ( );
	~GameEngine ( );

	void run ( );

private:

	void initSystems ( );
	void processInput ( );
	void gameLoop ( );
	void shutdown ( );
	void drawGame ( );

	GameState _gameState = GameState::PLAY;
	Display _gameDisplay;

	Material * _material = nullptr;
	Texture * _texture = nullptr;
	Shader * _shaderProgram = nullptr;
	CubeMap * _skyBox = nullptr;

#if _DEBUG
	ConsoleDebugScene _debugScene;
#endif
};

