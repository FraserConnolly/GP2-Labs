#include "Input.h"

void Input::StartUp ( )
{ 
	s_instance = new Input ( );
	s_instance->m_keyboardInput = new KeyboardInput ( );
	s_instance->m_mouseInput = new MouseInput ( );
}

void Input::Shutdown ( )
{ 
	delete s_instance->m_keyboardInput;
	delete s_instance->m_mouseInput;
	delete s_instance;
}

void Input::Service ( )
{ 
	s_instance->m_keyboardInput->Service ( );
	s_instance->m_mouseInput->Service ( );
}

void Input::ProcessKeyEvent ( const int keyCode, const bool pressed )
{ 
	s_instance->m_keyboardInput->processKeyEvent ( keyCode, pressed );
}

void Input::ProcessMouseRelativePosition ( const float x, const float y )
{ 
	s_instance->m_mouseInput->ProcessMouseRelativePosition ( x, y );
}

void Input::ProcessWheel ( const int horizontalMovement, const int verticalMovement )
{ 
	s_instance->m_mouseInput->ProcessWheel ( horizontalMovement, verticalMovement );
}

bool Input::RegisterKey ( int keyCode )
{
	return s_instance->m_keyboardInput->registerKey ( keyCode );
}

bool Input::RegisterOnKeyPressed ( int keyCode, std::function<void ( int )> callback )
{
	return s_instance->m_keyboardInput->registerOnKeyPressed ( keyCode, callback );
}

bool Input::WasKeyPressedThisFrame ( int keyCode )
{
	return s_instance->m_keyboardInput->wasPressedThisFrame ( keyCode );
}

bool Input::IsKeyPressed ( int keyCode )
{
	return s_instance->m_keyboardInput->isPressed ( keyCode );
}

void Input::ResetKeyPresses ( )
{ 
	s_instance->m_keyboardInput->resetKeyPresses ( );
}

Input * Input::s_instance = nullptr;