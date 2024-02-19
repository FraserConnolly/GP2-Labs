#include "Camera.h"

Camera::Camera ( )
	: _mode ( CameraMode::PERSPECTIVE )
{ }

Camera::~Camera ( )
{ }	

Transform & Camera::GetTransform ( )
{
	return _transform;
}

glm::mat4 Camera::GetViewMatrix ( )
{
	return GetProjectionMatrix ( ) * glm::lookAt ( _transform.GetPosition ( ), _transform.GetPosition ( ) + _cameraForward, _cameraUp );
}

glm::mat4 Camera::GetProjectionMatrix ( )
{
	if ( _projectionMatrixIsDirty )
	{
		// recalculate projection matrix
		if ( _mode == CameraMode::PERSPECTIVE )
		{

			_projectionMatrix = glm::perspective (
				_fov, _aspectRatio,
				_clippingPlanes.x, _clippingPlanes.y );
			_projectionMatrixIsDirty = false;
		}
		else if ( _mode == CameraMode::ORTHOGRAPHIC )
		{
			_projectionMatrix = glm::ortho (
				_orthoRectangle.x,
				_orthoRectangle.y,
				_orthoRectangle.z,
				_orthoRectangle.w,
				_clippingPlanes.x, _clippingPlanes.y );
			_projectionMatrixIsDirty = false;
		}
	}

	return _projectionMatrix;
}