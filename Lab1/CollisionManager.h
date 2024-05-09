#pragma once
#include <vector>

#define COLLIDER_DEFAULT_CAPACITY 100

struct ColliderData;
class Collider;
class ColliderSphere;
class ColliderBox;

class CollisionManager
{

public:

	static void Startup ( );
	static void Service ( );
	static void Shutdown ( );

	static void RegisterCollider   ( const Collider * pCollider );
	static void DeregisterCollider ( const Collider * pCollider );

private:

	static CollisionManager * s_instance;

	/// <summary>
	/// The collision world represents all objects that could possibly collide with each other.
	/// A future implementation could have multiple collisionWorlds to represent the different layers 
	/// that objects are on.
	/// </summary>
	std::vector<ColliderData *> m_collisionWorld;

	static bool AreIntersecting ( const Collider * pCollider, const Collider * pOtherCollider );

	static bool AreIntersecting ( const ColliderSphere * pCollider, const ColliderSphere * pOtherCollider );
	static bool AreIntersecting ( const ColliderBox * pCollider, const ColliderBox * pOtherCollider );
	static bool AreIntersecting ( const ColliderSphere * pCollider, const ColliderBox * pOtherCollider );
	static bool AreIntersecting ( const ColliderBox * pCollider, const ColliderSphere * pOtherCollider );

	static ColliderData * GetColliderDataFor ( const Collider * pCollider );
	static void EndAllCollisionsWith ( ColliderData * pColliderData );

	CollisionManager ( ) { }
	~CollisionManager ( ) { }

};
