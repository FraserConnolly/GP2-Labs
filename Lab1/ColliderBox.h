#pragma once
#include "ColliderBase.h"

class ColliderBox :
    public Collider
{

    friend class GameObject;

    ColliderBox ( GameObject & hostObject );

public:

    const glm::vec3 & GetCentre ( ) const override;
    const glm::vec3 & GetExtents ( ) const;
    void SetExtents ( const glm::vec3 & extents );

private:

    glm::vec3 m_extents;

};

