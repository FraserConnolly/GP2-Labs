#pragma once

#include <vector>

#include "Component.h"
#include "Transform.h"


/// <summary>
/// The whether an object is active or not is defined by the enabled flag of its transform.
/// </summary>
class GameObject
{ 
public: 
	
	GameObject ( );
	~GameObject ( );

	virtual void Update ( ) { }; // override in base class if it should have an update routine.

	Transform & GetTransform ( )
	{
		return m_transform;
	}
	
	int GetID ( ) const
	{
		return m_id;
	}

	void Destroy ( )
	{
		RemoveAllComponents ( ); // this will also destroy children through the transform component.
		m_isDestroyed = true;
		// to do - how will this game object be cleaned up?
	}

	const bool GetIsDestroyed ( ) const
	{
		return m_isDestroyed;
	}

	const bool IsActive ( )
	{
		return m_transform.IsEnabled ( );
	}

#pragma region Components

	void     AddComponent ( Component * const pComponent );
	void     RemoveComponent ( Component * const pToRemove );
	void     RemoveAllComponents ( );
	void     RemoveAllComponents ( ComponentTypes type );
	
	template<typename T>
	void GetComponent ( ComponentTypes type, T *& pComp );
	template<typename T>
	void GetAllComponent ( ComponentTypes type, std::vector<T *> & comps );

	void CleanUpComponents ( );

#pragma endregion

private: 
	
	int     m_id;
	Transform m_transform;
	
	//Shorter name for my vector 
	typedef std::vector<Component *> ComponentVector;
	//Shorter name for my iterator 
	typedef ComponentVector::iterator  VectorItor;

	ComponentVector m_components;
	//ArcheTypes m_type;
	
	bool m_isDestroyed = false;

	static int  s_objectIDCounter;
};

