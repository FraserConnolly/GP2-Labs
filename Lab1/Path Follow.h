#pragma once

#include "GameObject.h"
#include "Time.h"

class PathFollow : public Component
{
	friend class GameObject;

private:

	PathFollow ( GameObject & hostObject ) :
		Component ( ComponentTypes::PATH_FOLLOW, hostObject )
	{ }

	~PathFollow ( )
	{ }

public:

	void Update ( ) override;
	void AddWayPoint ( const glm::vec3 point );
	void ClearWayPoints ( );

private:

	// for future use
	int m_listenerIndex = 0;

	float m_speed = 1.0f;
	float m_checkDistance = 1.0f;
	int m_nextPointIndex = 0;
	std::vector<glm::vec3> m_path;

};

