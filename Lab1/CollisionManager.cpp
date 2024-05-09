#define COLLIDER_DEFAULT_CAPACITY 100

#include "CollisionManager.h"

#include "Transform.h"
#include "GameObject.h"
#include "ColliderBase.h"

#include <glm/glm.hpp> 
#include <glm/gtx/quaternion.hpp>
#include "Time.h"

struct TranslationData
{
	glm::vec3 m_position;
	glm::quat m_rotation;
	glm::vec3 m_scale;

	bool m_checkRotation = true;

	/// <summary>
	/// Applies an update to this translation from transform if the data has changed.
	/// </summary>
	/// <param name="transform"></param>
	/// <returns>True if data has changed. False if the data is the same.</returns>
	bool ApplyUpdate ( const Transform & transform )
	{
		bool changed = false;

		if ( m_position != transform.GetPosition ( ) )
		{
			changed = true;
			m_position = transform.GetPosition ( );
		}

		if ( m_scale != transform.GetScale ( ) )
		{
			changed = true;
			m_scale = transform.GetScale ( );
		}

		if ( m_checkRotation )
		{
			if ( m_rotation != transform.GetRotation ( ) )
			{
				changed = true;
				m_rotation = transform.GetRotation ( );
			}
		}

		return changed;
	}

	bool operator==( const TranslationData & other ) const
	{
		return m_position == other.m_position
			&& m_scale == other.m_scale
			&& m_checkRotation ? m_rotation == other.m_rotation : true;
	}

	bool operator!=( const TranslationData & other ) const
	{
		return !( *this == other );
	}

	bool operator==( const Transform & other ) const
	{
		return m_position == other.GetPosition ( )
			&& m_scale == other.GetScale ( )
			&& m_checkRotation ? m_rotation == other.GetRotation ( ) : true;
	}

	bool operator!=( const Transform & other ) const
	{
		return !( *this == other );
	}
};

struct ColliderData
{
	const Collider & m_collider;
	const Transform & m_transform;
	bool m_isActive;
	TranslationData m_translation;
	unsigned int m_lastFrameMoved;
	std::vector<ColliderData *> m_currentCollisions;

	ColliderData ( const Collider & collider )
		: m_collider ( collider ), m_transform ( collider.GetGameObject ( ).GetTransform ( ) ), m_lastFrameMoved ( 0 )
	{
		m_isActive = m_collider.IsActiveAndEnabled ( );

		switch ( m_collider.GetType ( ) )
		{
			case SPHERE_COLIDER: // these collider don't case about rotation.
				m_translation.m_checkRotation = false;
				break;
			default: // assuming that all other types of collider do care about rotation
				m_translation.m_checkRotation = true;
				break;
		}

		m_translation.ApplyUpdate ( m_transform );
	}

	bool IsCurrentlyCollidingWith ( const ColliderData * pColliderData, std::vector<ColliderData *>::iterator & itorator )
	{
		itorator = std::find (
			m_currentCollisions.begin ( ),
			m_currentCollisions.end ( ),
			pColliderData );

		if ( itorator == m_currentCollisions.end ( ) )
		{
			return false;
		}

		return true;
	}
};


void CollisionManager::Startup ( )
{
	s_instance = new CollisionManager ( );
	s_instance->m_collisionWorld.reserve ( COLLIDER_DEFAULT_CAPACITY );
}

void CollisionManager::Service ( )
{
	const unsigned int currentFrameIndex = Time::GetFrameCount ( );

	// check the state of all collider (have they moved or enabled/disabled)
	for ( auto & pColliderData : s_instance->m_collisionWorld )
	{
		// check if this collider is enabled
		const bool colliderIsEnabled = pColliderData->m_collider.IsActiveAndEnabled ( );

		if ( colliderIsEnabled != pColliderData->m_isActive )
		{
			// a change of state has occurred.

			if ( colliderIsEnabled )
			{
				// has turned on 
				pColliderData->m_lastFrameMoved = currentFrameIndex;
				pColliderData->m_translation.ApplyUpdate ( pColliderData->m_transform );
			}
			else
			{
				// send exit message to any current collisions
				EndAllCollisionsWith ( pColliderData );
			}

			pColliderData->m_isActive = colliderIsEnabled;
		}

		if ( !pColliderData->m_isActive )
		{
			// nothing else to do for this collider
			continue;
		}

		// check if this object has moved since it last changed
		bool updated = pColliderData->m_translation.ApplyUpdate ( pColliderData->m_transform );

		if ( updated )
		{
			pColliderData->m_lastFrameMoved = currentFrameIndex;
		}
		
	}

		// perform a pair wise collision detection.

		auto numberOfColliders = s_instance->m_collisionWorld.size ( );

		for ( int i = 0; i < numberOfColliders - 1; ++i )
		{
			auto & pColliderData = s_instance->m_collisionWorld [ i ];

			// can we skip this collider
			if ( ! pColliderData->m_isActive )
			{
				continue;
			}
		
			// check this collider against the others
			for ( int j = i + 1; j < numberOfColliders; ++j )
			{
				auto pOtherCollider = s_instance->m_collisionWorld [ j ];

				// check to see if neither collider moved this frame.
				if ( pColliderData->m_lastFrameMoved != currentFrameIndex && pOtherCollider->m_lastFrameMoved != currentFrameIndex )
				{
					continue;
				}

				auto collided = AreIntersecting ( &pColliderData->m_collider, &pOtherCollider->m_collider );

				std::vector<ColliderData *>::iterator itorator;
				
				// check if we have previously collided.
				bool previouslyCollided = pColliderData->IsCurrentlyCollidingWith ( pOtherCollider, itorator );

				if ( collided && !previouslyCollided )
				{
					// this is a new collision so raise the enter event
					pColliderData->m_transform.GetGameObject ( ).OnCollisionEnter ( pOtherCollider->m_collider );
					pOtherCollider->m_transform.GetGameObject ( ).OnCollisionEnter ( pColliderData->m_collider );

					pColliderData->m_currentCollisions.push_back ( pOtherCollider );
				}
				else if ( !collided && previouslyCollided )
				{
					// check if we have previously collided.
					if ( pColliderData->IsCurrentlyCollidingWith(pOtherCollider, itorator ) )
					{
						// we had previously collided but aren't now so raise the exit event.
						pColliderData->m_transform.GetGameObject ( ).OnCollisionEnter ( pOtherCollider->m_collider );
						pOtherCollider->m_transform.GetGameObject ( ).OnCollisionEnter ( pColliderData->m_collider );

						pColliderData->m_currentCollisions.erase ( itorator );
					}
				}
				else
				{
					// do nothing the state is the same.
				}
			}
	}
}

void CollisionManager::Shutdown ( )
{
	for ( auto & colliderData : s_instance->m_collisionWorld )
	{
		delete colliderData;
	}

	s_instance->m_collisionWorld.clear ( );
}

void CollisionManager::RegisterCollider ( const Collider * pCollider )
{
	if ( pCollider == nullptr )
	{
		// to do - log this warning.
		return;
	}

	// Make sure this component doesn't already exist in the list
	ColliderData * pColliderData = GetColliderDataFor ( pCollider );

	if ( pColliderData != nullptr )
	{
		// already registered - log this is a warning.
		return;
	}

	auto newDataStore = new ColliderData ( *pCollider );

	s_instance->m_collisionWorld.push_back ( newDataStore );
}

void CollisionManager::DeregisterCollider ( const Collider * pCollider )
{
	// get a pointer to the pColliderData within the vector.
	ColliderData * pColliderData = GetColliderDataFor ( pCollider );

	if ( pColliderData == nullptr )
	{
		return;
	}

	// end any active collisions ( to do this we have to check every collider )

	EndAllCollisionsWith ( pColliderData );

	// find the iterator for this pointer in the vector and remove it.
	auto end = s_instance->m_collisionWorld.end ( );
	auto itor = std::find ( s_instance->m_collisionWorld.begin ( ), end, pColliderData );

	if ( itor == end )
		return;

	s_instance->m_collisionWorld.erase ( itor, end );
}

bool CollisionManager::AreIntersecting ( const Collider * pCollider, const Collider * pOtherCollider )
{
	if ( pCollider == nullptr )
	{
		// log this error.
		return false;
	}

	if ( pOtherCollider == nullptr )
	{
		// log this error.
		return false;
	}

	if ( pCollider == pOtherCollider )
	{
		// log this error.
		return false;
	}

	ComponentTypes typeA, typeB;
	typeA = pCollider->GetType ( );
	typeB = pOtherCollider->GetType ( );

	if ( typeA == SPHERE_COLIDER && typeB == SPHERE_COLIDER )
	{
		return AreIntersecting ( ( ColliderSphere * ) pCollider, ( ColliderSphere * ) pOtherCollider );
	}
	else if ( typeA == BOX_COLIDER && typeB == BOX_COLIDER )
	{
		return AreIntersecting ( ( ColliderBox * ) pCollider, ( ColliderBox * ) pOtherCollider );
	}
	else if ( typeA == SPHERE_COLIDER && typeB == BOX_COLIDER )
	{
		return AreIntersecting ( ( ColliderSphere * ) pCollider, ( ColliderBox * ) pOtherCollider );
	}
	else if ( typeA == BOX_COLIDER && typeB == SPHERE_COLIDER )
	{
		return AreIntersecting ( ( ColliderBox * ) pCollider, ( ColliderSphere * ) pOtherCollider );
	}
	else
	{
		// error state - log this error!
		return false;
	}
}

bool CollisionManager::AreIntersecting ( const ColliderSphere * pCollider, const ColliderSphere * pOtherCollider )
{
	return false;
}

bool CollisionManager::AreIntersecting ( const ColliderBox * pCollider, const ColliderBox * pOtherCollider )
{
	return false;
}

bool CollisionManager::AreIntersecting ( const ColliderSphere * pCollider, const ColliderBox * pOtherCollider )
{
	return false;
}

bool CollisionManager::AreIntersecting ( const ColliderBox * pCollider, const ColliderSphere * pOtherCollider )
{
	return false;
}

ColliderData * CollisionManager::GetColliderDataFor ( const Collider * pCollider )
{
	for ( auto & colliderData : s_instance->m_collisionWorld )
	{
		if ( &colliderData->m_collider == pCollider )
		{
			return colliderData;
		}
	}

	return nullptr;
}

void CollisionManager::EndAllCollisionsWith ( ColliderData * pColliderData )
{
	for ( auto collision : pColliderData->m_currentCollisions )
	{
		collision->m_collider.GetGameObject ( ).OnCollisionExit ( pColliderData->m_collider );
		pColliderData->m_transform.GetGameObject ( ).OnCollisionExit ( collision->m_collider );
	}

	pColliderData->m_currentCollisions.clear ( );

	for ( auto pOtherCollider : s_instance->m_collisionWorld )
	{
		if ( pOtherCollider == pColliderData )
		{
			continue;
		}

		auto found = std::find ( 
			pOtherCollider->m_currentCollisions.begin ( ), 
			pOtherCollider->m_currentCollisions.end ( ), 
			pColliderData );

		if ( found == pOtherCollider->m_currentCollisions.end ( ) )
		{
			// pColliderData is not currently colliding with pOtherCollider
			continue;
		}

		pOtherCollider->m_transform.GetGameObject ( ).OnCollisionExit ( pColliderData->m_collider );
		pColliderData->m_collider.GetGameObject ( ).OnCollisionExit ( pColliderData->m_collider );

		pOtherCollider->m_currentCollisions.erase ( found );

	}

}

CollisionManager * CollisionManager::s_instance = nullptr;
