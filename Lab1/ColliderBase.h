#pragma once

#include "Component.h"
#include <glm/glm.hpp> 

class Collider : public Component
{ 
	friend class CollisionManager;

public:
	
	virtual const glm::vec3 & GetCentre ( ) const = 0;

protected:

	Collider ( GameObject & hostObject, ComponentTypes type )
		: Component ( hostObject, type )
	{ }

};

