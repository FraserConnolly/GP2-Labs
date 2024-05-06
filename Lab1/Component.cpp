#include "Component.h"
#include "GameObject.h"

Component::Component ( const ComponentTypes type ) :
	m_isEnabled ( true )
{ 
	m_componentType = type;
}

Component::Component ( const ComponentTypes type,  const bool enable )
{ 
	m_componentType = type;
	m_isEnabled = enable;
	}

GameObject & Component::GetGameObject ( ) const
{
	return *m_gameObject;
}

bool Component::IsDead ( ) const
{
	return m_isDead;
}

void Component::Kill ( )
{ 
	SetActive ( false );
	m_isDead = true;
}

bool Component::IsEnabled ( ) const
{
	return m_isEnabled;
}

void Component::SetActive ( const bool enable )
{
	if ( m_isEnabled == enable )
	{
		return;
	}

	m_isEnabled = enable;

	if ( enable )
	{
		OnEnable();
	}
	else
	{
		OnDisable ( );
	}

}
