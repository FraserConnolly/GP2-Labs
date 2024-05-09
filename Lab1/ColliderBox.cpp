#include "ColliderBox.h"
#include "Transform.h"

ColliderBox::ColliderBox ( GameObject & hostObject ) :
    Collider ( hostObject, ComponentTypes::BOX_COLIDER ),
    m_extents ( 1.0f )
{ }

const glm::vec3 & ColliderBox::GetCentre ( ) const
{
    return m_transform.GetPosition ( );
}

const glm::vec3 & ColliderBox::GetExtents ( ) const
{
    return m_extents;
}

void ColliderBox::SetExtents ( const glm::vec3 & extents )
{
    m_extents = extents;
}
