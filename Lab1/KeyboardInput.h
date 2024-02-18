#pragma once
#include <windows.h>

// Standard library C-style
#include <wchar.h>
#include <stdlib.h>
#include <stdio.h>
#include <map>
#include <functional>

typedef struct
{
	bool isPressed;
	float pressedDuration;
	std::function<void ( int keyCode )> onPressCallback;
} keyEventStatus, *pKeyEventStatus;


class KeyboardInput
{

public:

	KeyboardInput ( );
	~KeyboardInput ( );

	void tick ( const float deltaTime );

	bool registerKey ( int keyCode );
	bool registerOnKeyPressed ( int keyCode, std::function<void ( int )> callback );

	bool wasPressedThisFrame ( int keyCode );
	bool isPressed ( int keyCode );

	// Call this whenever the scene loads to ensure that key holds are reset
	void resetKeyPresses ( );

	void processKeyEvent ( const int keyCode, const bool pressed, const float deltaTime );
	 
private:
	HANDLE m_bufferHandle = nullptr;
	BOOL m_ready = false;
	DWORD fdwSaveOldMode = 0;
	
	void init ( );
	std::map<int, pKeyEventStatus> m_keyRegistrations;

};
