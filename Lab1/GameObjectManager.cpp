#include "GameObjectManager.h"

GameObjectManager::GameObjectManager ( )
{
	m_gameObjects.reserve ( GAME_OBJECT_MANAGER_CAPACITY );
	m_gameObjectsToBeDeleted.reserve ( GAME_OBJECT_MANAGER_CAPACITY );
}

GameObjectManager::~GameObjectManager ( )
{ 
	CleanUpObjects ( );

	for ( auto & object : m_gameObjects )
	{
		delete object;
	}

	m_gameObjects.clear ( );
}

void GameObjectManager::UpdateObjects ( )
{ 
	for ( auto& object : m_gameObjects )
	{
		object->Update ( );

		if ( object->GetIsDestroyed ( ) )
		{
			m_gameObjectsToBeDeleted.push_back ( object );
		}
	}
}

GameObject * GameObjectManager::CreateObject ( )
{
	GameObject* object = new GameObject ( );
	m_gameObjects.push_back ( object );
	return object;
}

void GameObjectManager::CleanUpObjects ( )
{
	for ( auto& object : m_gameObjectsToBeDeleted )
	{
		m_gameObjects.erase ( std::remove ( m_gameObjects.begin ( ), m_gameObjects.end ( ), object ), m_gameObjects.end ( ) );
		delete object;
	}
	
	m_gameObjectsToBeDeleted.clear ( );
}

void GameObjectManager::DeleteAllObjects ( )
{ 
	for ( auto & object : m_gameObjects )
	{
		delete object;
	}

	m_gameObjects.clear ( );
	m_gameObjectsToBeDeleted.clear ( );
}
