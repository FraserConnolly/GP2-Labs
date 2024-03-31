#pragma once

#include "Component.h"
#include "GameObject.h"
#include "Time.h"

class Rotator : public Component
{ 
public:
	Rotator() : Component( ComponentTypes::ROTATOR ) { }
	~Rotator() { }
	
	void Update ( )
	{
		float t = Time::GetTime ( );
		m_gameObject->GetTransform ( ).SetRotation ( m_x_speed * t, m_y_speed * t, m_z_speed * t );
	}
	
	void SetSpeed ( float speed )
	{
		m_speed = speed;
	}

	void SetRotationAxis ( const bool x, const bool y, const bool z )
	{
		m_x_speed = x ? m_speed : 0.0f;
		m_y_speed = y ? m_speed : 0.0f;
		m_z_speed = z ? m_speed : 0.0f;
	}

private:

	float m_speed = 1.0f;
	float m_x_speed = 0.0f;
	float m_y_speed = 0.0f;
	float m_z_speed = 0.0f;

};

