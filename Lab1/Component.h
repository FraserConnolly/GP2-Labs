#pragma once

#include "ComponentTypes.h"

class GameObject;

class Component
{
public: 
	
	friend class GameObject;

	Component ( const ComponentTypes type );
	Component ( const ComponentTypes type, const bool enable );

	virtual void Update ( ) { }
	virtual void LateUpdate ( ) { }
	
	virtual void OnEnable ( ) { }
	virtual void OnDisable ( ) { }

	virtual void Awake ( ) { }
	virtual void Start ( ) { }
	virtual void OnDestroy ( ) { }

	virtual void Reset ( ) { }

	GameObject & GetGameObject ( ) const;

	bool IsDead ( ) const;
	void Kill ( );

	bool IsEnabled ( ) const;
	bool IsActiveAndEnabled ( ) const;

	void SetActive ( const bool enable );

	ComponentTypes GetType ( )
	{
		return m_componentType;
	}

protected:

	bool m_isEnabled = true;
	bool m_isDead = false;
	ComponentTypes m_componentType;

	GameObject * m_gameObject = nullptr;
};

