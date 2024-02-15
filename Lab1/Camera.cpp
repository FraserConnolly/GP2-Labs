#include "Camera.h"

Camera::Camera ( )
	: _mode ( CameraMode::PERSPECTIVE )
{ }

Camera::~Camera ( )
{ }	

void Camera::SetMode ( const CameraMode mode )
{
	_mode = mode;
}

Transform & Camera::GetTransform ( )
{
	return _transform;
}

glm::mat4 Camera::GetViewMatrix ( ) const
{
	glm::mat4 view = glm::mat4 ( 1.0f );
	// note that we're translating the scene in the reverse direction of where we want to move
	// FC - I'm not sure if this negation should be here or not.
	view = glm::translate ( view, - _transform.GetPosition() );
	return view;
}

glm::mat4 Camera::GetProjectionMatrix ( ) const
{
	if ( _mode == CameraMode::PERSPECTIVE )
	{
		return glm::perspective ( 
			_fov, _aspectRatio,
			_clippingPlanes.x, _clippingPlanes.y );
	}
	else if ( _mode == CameraMode::ORTHOGRAPHIC )
	{
		return glm::ortho ( 
			_orthoRectangle.x, 
			_orthoRectangle.y, 
			_orthoRectangle.z, 
			_orthoRectangle.w, 
			_clippingPlanes.x, _clippingPlanes.y );
	}
}