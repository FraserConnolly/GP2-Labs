#pragma once
#include <glm/glm.hpp> 

class MouseInput
{

public:

	// call each frame
	void ResetMouseOffsets ( )
	{
		_mouseOffset.x = 0;
		_mouseOffset.y = 0;
	}

	void ProcessMouseRelativePosition ( const float x, const float y )
	{
		_mouseOffset.x += x;
		_mouseOffset.y += y;
	}

	void ProcessWheel ( const int horizontalMovement, const int verticalMovement )
	{
		_wheelOffset.x = horizontalMovement;
		_wheelOffset.y = verticalMovement;
	}

#pragma region Getters
	
	glm::vec2 GetMouseOffset ( )
	{
		return _mouseOffset;
	}

	float GetXOffset ( )
	{
		return _mouseOffset.y;
	}
	
	float GetYOffset ( )
	{
		return _mouseOffset.y;
	}

	int GetHorizontalWheelOffset ( )
	{
		return _wheelOffset.x;
	}

	int GetVerticalWheelOffset ( )
	{
		return _wheelOffset.y;
	}

#pragma endregion

private:

	glm::vec2 _mouseOffset;
	glm::ivec2 _wheelOffset;
};

