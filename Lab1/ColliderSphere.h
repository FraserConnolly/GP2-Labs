#pragma once
#include "ColliderBase.h"

class ColliderSphere :
    public Collider
{

    friend class GameObject;

    ColliderSphere ( GameObject & hostObject ) :
        Collider ( hostObject, ComponentTypes::SPHERE_COLIDER )
    { }

public:

    const glm::vec3 & GetCentre ( ) const override;
    const float GetRadious ( ) const;
    void SetRadious ( const float radious );

private:

    float m_radious;

};

