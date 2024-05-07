#include "GameObjectManager.h"

void GameObjectManager::Startup ( )
{ 
	s_instance = new GameObjectManager ( );
}

GameObjectManager::GameObjectManager ( )
{
	m_gameObjects.reserve ( GAME_OBJECT_MANAGER_CAPACITY );
	m_gameObjectsToBeDeleted.reserve ( GAME_OBJECT_MANAGER_CAPACITY );
}

void GameObjectManager::Shutdown ( )
{
	s_instance->CleanUpObjects ( );

	for ( auto & object : s_instance->m_gameObjects )
	{
		delete object;
	}

	s_instance->m_gameObjects.clear ( );
}

void GameObjectManager::Service ( )
{
	for ( auto & object : s_instance->m_gameObjects )
	{
		object->Update ( );

		if ( object->GetIsDestroyed ( ) )
		{
			s_instance->m_gameObjectsToBeDeleted.push_back ( object );
		}
	}
}

GameObject * GameObjectManager::CreateObject ( )
{
	GameObject* object = new GameObject ( );
	s_instance->m_gameObjects.push_back ( object );
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

GameObjectManager * GameObjectManager::s_instance = nullptr;
