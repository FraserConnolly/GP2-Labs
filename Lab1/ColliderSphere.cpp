#include "ColliderSphere.h"

#include "Transform.h"

const glm::vec3 & ColliderSphere::GetCentre ( ) const
{
    return m_transform.GetPosition ( );
}

const float ColliderSphere::GetRadious ( ) const
{
    return m_radious;
}

void ColliderSphere::SetRadious ( const float radious )
{
    if ( radious < 0.0f )
    {
        m_radious = 0.0f;
        return;
    }

    m_radious = radious;
}

