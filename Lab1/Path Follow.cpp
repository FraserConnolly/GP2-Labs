#include "Path Follow.h"

PathFollow::PathFollow ( GameObject & hostObject ) :
	Component ( ComponentTypes::PATH_FOLLOW, hostObject ),
	m_nextPointIndex ( 0 ), m_speed ( 1.0f ), m_checkDistance ( 0.1f )
{ }

void PathFollow::Update ( )
{
	if ( m_path.size ( ) == 0 )
	{
		return;
	}

	auto & nextPoint = m_path [ m_nextPointIndex ];
	auto distance = glm::distance ( m_transform.GetPosition ( ), nextPoint );


	if ( distance < m_checkDistance )
	{
		m_nextPointIndex++;

		if ( m_nextPointIndex >= m_path.size ( ) )
		{
			m_nextPointIndex = 0;
		}

		return;
	}

	m_transform.LookAt ( nextPoint );
	m_transform.Translate ( Time::GetDeltaTime ( ) * m_speed * m_transform.GetForward ( ) );
}

void PathFollow::AddWayPoint ( const glm::vec3 point )
{ 
	m_path.push_back ( point );
}

void PathFollow::ClearWayPoints ( )
{ 
	m_path.clear ( );
}
