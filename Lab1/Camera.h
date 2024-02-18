#pragma once

#include <glm/glm.hpp> 
#include <glm/gtx/transform.hpp> 

#include "Transform.h"

class Camera
{
public:
	enum CameraMode
	{
		PERSPECTIVE,
		ORTHOGRAPHIC
	};
	
	Camera ( );
	~Camera ( );

#pragma region Getters and Setters


	void SetMode ( const CameraMode mode );
	
	/// <summary>
	/// Set the camera's field of view.
	/// </summary>
	/// <param name="fov">In degrees.</param>
	void SetFoV ( const float fov )
	{
		_fov = glm::radians( fov );
	}

	void SetClippingPlanes ( const glm::vec2 & planes )
	{
		_clippingPlanes = planes;
	}

	void SetClippingPlanes ( const float near, const float far )
	{
		_clippingPlanes.x = near;
		_clippingPlanes.y = far;
	}

	void SetOrthoRectangle ( const glm::vec4 & rect )
	{
		_orthoRectangle = rect;
	}
	
	void SetOrthoRectangle ( const float left, const float right, const float bottom, const float top )
	{
		_orthoRectangle.x = left;
		_orthoRectangle.y = right;
		_orthoRectangle.z = bottom;
		_orthoRectangle.w = top;
	}

	void SetAspectRatio ( const float aspectRatio )
	{
		_aspectRatio = aspectRatio;
	}

	void SetAspectRatio ( const float width, const float height )
	{
		_aspectRatio = width / height;
	}

	void SetCameraTarget ( const glm::vec3 & target )
	{
		_cameraTarget = target;
		_cameraDirection = glm::normalize( _transform.GetPosition( ) - _cameraTarget );
		glm::vec3 up = glm::vec3 ( 0.0f, 1.0f, 0.0f );
		_cameraRight = glm::normalize ( glm::cross ( up, _cameraDirection ) );
		_cameraUp = glm::cross ( _cameraDirection, _cameraRight );
	}

	glm::vec3 GetCameraRight ( )
	{
		return _cameraRight;
	}

	glm::vec3 GetCameraFront ( )
	{
		return glm::vec3 ( 0.0f, 0.0f, -1.0f );
	}

	glm::vec3 GetCameraUp ( )
	{
		return _cameraUp;
	}

#pragma endregion

	Transform & GetTransform ( );

	glm::mat4 GetViewMatrix ( ) const;
	glm::mat4 GetProjectionMatrix ( ) const;

private:
	float _fov = glm::radians( 45.0f );
	float _aspectRatio = 16.0f / 9.0f;
	glm::vec2 _clippingPlanes = glm::vec2 ( 0.1f, 100.0f );
	glm::vec4 _orthoRectangle = glm::vec4 ( -10.0f, 10.0f, -10.0f, 10.0f );
	CameraMode _mode;
	Transform _transform;
	glm::vec3 _cameraTarget;
	glm::vec3 _cameraDirection;
	glm::vec3 _cameraRight;
	glm::vec3 _cameraUp;
};

