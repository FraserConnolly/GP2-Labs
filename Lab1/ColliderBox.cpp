#include "ColliderBox.h"
#include "Transform.h"

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
