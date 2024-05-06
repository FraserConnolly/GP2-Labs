#pragma once

#include <SDL\SDL.h>
#include <GL\glew.h>

#include "Display.h"
#include "GameObjectManager.h"

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

	GameObjectManager _gameObjectManager;
	Material * _material = nullptr;
	Texture * _texture = nullptr;
	Display _gameDisplay;
	GameState _gameState = GameState::PLAY;
	Shader * _shaderProgram = nullptr;

#if _DEBUG
	ConsoleDebugScene _debugScene;
#endif
};

