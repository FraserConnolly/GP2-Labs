#pragma once

#include "GameObject.h"
#include "Time.h"

class PathFollow : public Component
{
	friend class GameObject;

private:

	PathFollow ( GameObject & hostObject );

	~PathFollow ( )
	{ }

public:

	void Update ( ) override;
	void AddWayPoint ( const glm::vec3 point );
	void ClearWayPoints ( );

private:

	float m_speed;
	float m_checkDistance;
	int m_nextPointIndex = 0;
	std::vector<glm::vec3> m_path;

};

