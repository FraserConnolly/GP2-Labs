#include "Component.h"
#include "GameObject.h"

Component::Component ( const ComponentTypes type, GameObject & hostObject ) :
	m_isEnabled ( true ), m_componentType ( type ), m_gameObject ( hostObject )
{ 
}

Component::Component ( const ComponentTypes type, GameObject & hostObject,  const bool enable ) :
	m_isEnabled ( enable ), m_componentType ( type ), m_gameObject ( hostObject )
{
}

GameObject & Component::GetGameObject ( ) const
{
	return m_gameObject;
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

bool Component::IsActiveAndEnabled ( ) const
{
	if ( ! m_isEnabled )
	{
		return false;
	}

	return m_gameObject.IsActiveInHierarchy ( );
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
