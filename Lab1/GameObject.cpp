#include "GameObject.h"
#include "Camera.h"
#include "Mesh.h"
#include "CameraFlyController.h"
#include "Rotator.h"
#include "Audio Event Emitter.h"
#include "Audio Listener.h"
#include "Path Follow.h"
#include "ColliderBase.h"
#include "ColliderBox.h"
#include "ColliderSphere.h"

unsigned int GameObject::s_objectIDCounter = 0;

GameObject::GameObject ( )
    : m_transform ( *new Transform ( *this ) ), m_id ( 0 )
{
    m_id = s_objectIDCounter++;
    AddComponent ( &m_transform );
}

GameObject::~GameObject ( )
{
	RemoveAllComponentsImmediately ( );
}

Component * GameObject::CreateComponent ( ComponentTypes component, GameObject & hostObject )
{
    switch ( component )
    {
        case TRANSFORM:
            // Transform can only be constructed inside the initialisation list of a GameObject.
            return nullptr;
        case MESH_RENDERER:
            return new MeshRenderer ( hostObject );
        case BOX_COLIDER:
            return new ColliderBox ( hostObject );
        case SPHERE_COLIDER:
            return new ColliderSphere ( hostObject );
        case CAMERA:
            return new Camera ( hostObject );
        case CAMERA_FLY_CONTROLLER:
            return new CameraFlyController ( hostObject );
        case ROTATOR:
            return new Rotator ( hostObject );
        case AUDIO_EVENT_EMITTER:
            return new AudioEventEmitter ( hostObject );
        case AUDIO_LISTENER:
            return new AudioListener ( hostObject );
        case PATH_FOLLOW:
            return new PathFollow ( hostObject );
    }

    return nullptr;
}

void GameObject::Update ( )
{
    for ( auto & comp : m_components )
    {
        if ( comp->IsEnabled ( ) )
        {
            comp->Update ( );
        }
    }
}

void GameObject::OnCollisionEnter ( const Collider & otherCollider )
{
    for ( auto & comp : m_components )
    {
        if ( comp->IsEnabled ( ) )
        {
            comp->OnCollisionEnter ( otherCollider );
        }
    }
}

void GameObject::OnCollisionExit ( const Collider & otherCollider )
{
    for ( auto & comp : m_components )
    {
        if ( comp->IsEnabled ( ) )
        {
            comp->OnCollisionExit ( otherCollider );
        }
    }
}

Component * GameObject::AddComponent ( ComponentTypes component )
{
    Component * pComponent = CreateComponent ( component , *this );

    if ( pComponent == nullptr )
    {
        return nullptr;
    }

    return AddComponent ( pComponent );
}

Component * GameObject::AddComponent ( Component * const pComponent )
{
    //Make sure this component doesn't already exist in the components list
    VectorItor found = std::find ( m_components.begin ( ),
                                   m_components.end ( ), pComponent );

    if ( found != m_components.end ( ) )
    {
        return pComponent;
    }

    m_components.push_back ( pComponent );

    pComponent->Awake ( );
    if ( pComponent->IsEnabled ( ) )
    {
        pComponent->OnEnable ( );
    }

    return pComponent;
}

void GameObject::RemoveComponent ( Component * const pToRemove )
{ 
    if ( pToRemove->GetType ( ) == TRANSFORM )
    {
        // Can not remove a transform.
        return;
    }

    //Make the sure the instance exists in this object 
    VectorItor end = m_components.end ( );
    VectorItor itor = std::find ( m_components.begin ( ), end, pToRemove );

    if ( itor != end )
        return;

    ( *itor )->Kill ( );

    // note - don't erase or delete in this function, do that in the clean up.
}

void GameObject::RemoveAllComponentsImmediately ( )
{ 
    VectorItor itor = m_components.begin ( );
    VectorItor end = m_components.end ( );
    while ( itor != end )
    {
        ( *itor )->Kill ( ); 
        ( *itor )->OnDestroy ( );
        delete *itor;
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
            m_components [ endIndex ] = m_components [ m_components.size ( ) - 1 ]; // copy the pointer to the last component to this element
            m_components.pop_back ( );  // pop the last element which is now a duplicate.
        }
    }
}


void GameObject::RemoveAllComponents ( )
{
    for ( size_t i = 0; i < m_components.size ( ); ++i )
    {
        if ( m_components[i]->GetType( ) == TRANSFORM )
        {
            // can not remove the transform component.
            continue;
        }
    
        m_components [ i ]->Kill ( );
    }
}

void GameObject::RemoveAllComponents ( ComponentTypes type )
{
    if ( type == TRANSFORM )
    {
        // can not remove the transform component.
        return;
    }

    for ( size_t i = 0; i < m_components.size ( ); ++i )
    {
        if ( m_components [ i ]->GetType ( ) == type )
        {
            m_components [ i ]->Kill ( );
        }
    }
}


