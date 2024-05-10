#pragma once

#include "Component.h"
#include "GameObject.h"
#include "Audio.h"

class AudioEventEmitter : public Component
{ 
	friend class GameObject;

private:

	AudioEventEmitter ( GameObject & hostObject ) : 
		Component( hostObject, ComponentTypes::AUDIO_EVENT_EMITTER ) { }
	~AudioEventEmitter () { }
	
public:

	/// <summary>
	/// Loads the event into the system if it isn't already.
	/// This will also create the FMOD event instance.
	/// </summary>
	/// <param name="strEventName">These are FMOD events so don't forget to use the full FMOD path which will start event:/</param>
	void LoadEvent ( const std::string & strEventName )
	{
		m_eventName = strEventName; // copy string
		Audio::LoadEvent ( m_eventName );
		m_position = m_transform.GetPosition ( );
		Audio::SetEvent3dAttributes ( m_eventName, m_transform );
	}

	void PlayEvent ( )
	{
		if ( m_eventName.empty( ) )
		{
			return;
		}

		Audio::PlayEvent ( m_eventName );
	}
	
	void StopEvent ( )
	{
		if ( m_eventName.empty ( ) )
		{
			return;
		}

		Audio::StopEvent ( m_eventName );
	}

	bool IsPlaying ( )
	{
		if ( m_eventName.empty ( ) )
		{
			return false;
		}

		return Audio::IsEventPlaying ( m_eventName );
	}

	void Update ( ) override
	{
		if ( !IsPlaying ( ) )
		{
			return;
		}

		auto & newPosition = m_transform.GetPosition ( );
		if ( newPosition != m_position )
		{
			m_position = newPosition;
			Audio::SetEvent3dAttributes ( m_eventName, m_transform );
		}
	}

private:

	glm::vec3 m_position;
	std::string m_eventName;

};

