#pragma once
#include <vector>
#include "GameObject.h"

#define GAME_OBJECT_MANAGER_CAPACITY 100

class GameObjectManager
{ 
public:
	GameObjectManager( );
	~GameObjectManager( );

	void UpdateObjects( );

	GameObject * CreateObject( );

	void CleanUpObjects( );

private:

	std::vector<GameObject *> m_gameObjects;
	std::vector<GameObject*> m_gameObjectsToBeDeleted;

};

