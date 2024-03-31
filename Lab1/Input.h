#pragma once
#include "KeyboardInput.h"
#include "MouseInput.h"

/// <summary>
/// A static class that will handle all input from the user
/// </summary>

class Input
{ 
	friend class GameEngine;

public:

#pragma region Keyboard functions


	// Keyboard functions

	static bool RegisterKey ( int keyCode );
	static bool RegisterOnKeyPressed ( int keyCode, std::function<void ( int )> callback );

	static bool WasKeyPressedThisFrame ( int keyCode );
	static bool IsKeyPressed ( int keyCode );

	// Call this whenever the scene loads to ensure that key holds are reset
	static void ResetKeyPresses ( );

#pragma endregion

#pragma region Mouse Functions


#pragma endregion


private:

	static void StartUp ( );
	static void Shutdown ( );
	static void Service ( );

	static Input * s_instance;

	KeyboardInput * m_keyboardInput;
	MouseInput * m_mouseInput;

	static void ProcessKeyEvent ( const int keyCode, const bool pressed );

	static void ProcessMouseRelativePosition ( const float x, const float y );
	static void ProcessWheel ( const int horizontalMovement, const int verticalMovement );

};

