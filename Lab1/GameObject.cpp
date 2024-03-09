#include "GameObject.h"

GameObject::GameObject ( )
{
    // Reset transform and add it to the components vector
    m_transform.Reset ( );
    AddComponent ( &m_transform );
}


GameObject::~GameObject ( )
{
	RemoveAllComponents ( );
}

void GameObject::AddComponent ( Component * const pComponent )
{
    if ( pComponent->m_gameObject != nullptr )
    {
        // to do - log this error - the component is already attached to an object.
        return;
    }

    //Make sure this component doesn't already exist in the components list
    VectorItor found = std::find ( m_components.begin ( ),
                                   m_components.end ( ), pComponent );

    if ( found != m_components.end ( ) )
    {
        return;
    }

    //Set this object as the parent 
    pComponent->m_gameObject = this;
    m_components.push_back ( pComponent );
}

void GameObject::RemoveComponent ( Component * const pToRemove )
{ 
    //Make the sure the instance exists in this object 
    VectorItor end = m_components.end ( );
    VectorItor itor = std::find ( m_components.begin ( ), end, pToRemove );

    if ( itor != end )
        return;

    ( *itor )->Kill ( );

    // note - don't erase or delete in this function, do that in the clean up.
}

void GameObject::RemoveAllComponents ( )
{ 
    VectorItor itor = m_components.begin ( );
    VectorItor end = m_components.end ( );
    while ( itor != end )
    {
        ( *itor )->OnDestroy ( );
        delete ( *itor );
        ++itor;
    }
    m_components.clear ( );
}

template<typename T>
void GameObject::GetComponent ( ComponentTypes type, T *& pComp )
{
    size_t size = m_components.size ( );
    for ( size_t i = 0; i < size; ++i )
    {
        //if we found the correct type, set and return 
        if ( m_components [ i ]->GetType ( ) == type )
        {
            pComp = static_cast< T * >( m_components [ i ] );
            return;
        }
    }
    pComp = 0;
}

template<typename T>
void GameObject::GetAllComponent ( ComponentTypes type, std::vector<T *> & comps )
{
    size_t size = m_components.size ( );
    for ( size_t i = 0; i < size; ++i )
    {
        //if we found the correct type, add to vector 
        if ( m_components [ i ]->GetType ( ) == type )
            comps.push_back ( static_cast< T * >( m_components [ i ] ) );
    }
}

void GameObject::CleanUpComponents ( )
{ 
    int endIndex = m_components.size ( ) - 1;
    for ( ; endIndex >= 0; --endIndex )
    {
        if ( m_components [ endIndex ]->IsDead( ) )
        {
            m_components [ endIndex ]->OnDestroy ( );
            delete m_components [ endIndex ];
            m_components [ endIndex ] = m_components [ m_components.size ( )
                - 1 ];
            m_components.pop_back ( );
        }
     //   else
     //   {
     //       m_components [ endIndex ]->Update ( dt );
     //   }
    }
}

void GameObject::RemoveAllComponents ( ComponentTypes type )
{
    for ( size_t i = 0; i < m_components.size ( ); ++i )
    {
        if ( m_components [ i ]->GetType ( ) == type )
        {
            m_components [ i ]->Kill ( );
        }
    }
}


