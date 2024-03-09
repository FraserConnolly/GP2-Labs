#include "Transform.h"

#include "GameObject.h"

void Transform::OnDestroy ( )
{
	// Destroy children too
	for ( auto child : m_children )
	{
		child->Destroy ( );
	}
}

void Transform::AddChild ( Transform * const pChild )
{
	auto found = std::find ( m_children.begin ( ),
							 m_children.end ( ), pChild );

	if ( found != m_children.end ( ) )
	{
		// child is already in the list of children
		return;
	}

	m_children.push_back ( pChild );
}

void Transform::RemoveChild ( Transform * pChild )
{
	auto end = m_children.end ( );
	auto itor = std::find ( m_children.begin ( ), end, pChild );

	if ( itor != end )
	{
		// specified child is not one of ours.
		return;
	}

	m_children.erase ( itor );
}

// is called from our parent's OnDestroy method
void Transform::Destroy ( )
{
	for ( auto child : m_children )
	{
		child->Destroy ( );
	}

	m_gameObject->Destroy ( );
	Kill ( );
}
