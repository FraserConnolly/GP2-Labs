#include "Time.h"

void Time::StartUp ( )
{
	s_instance = new Time ( );
}

void Time::Shutdown ( )
{ 
	delete s_instance;
}

float Time::GetTime ( )
{
	return s_instance->m_time;
}

float Time::GetDeltaTime ( )
{
	return s_instance->m_deltaTime;
}

Time::Time ( ) : m_time ( 0.0f ), m_deltaTime ( 0.0f )
{ 

}

Time::~Time ( )
{ }

Time * Time::s_instance = nullptr;