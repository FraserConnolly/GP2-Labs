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
		m_gameObject->GetTransform().SetRotation ( 0.0f, m_speed * Time::GetTime(), 0.0f );
	}
	
	void SetSpeed ( float speed )
	{
		m_speed = speed;
	}

private:
	float m_speed = 1.0f;
};

