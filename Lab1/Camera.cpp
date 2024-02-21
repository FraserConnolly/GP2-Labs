#include "Camera.h"

Camera::Camera ( )
	: _mode ( CameraMode::PERSPECTIVE )
{ }

Camera::~Camera ( )
{ }	

void Camera::SetCameraTarget ( const glm::vec3 & target )
{
	_cameraTarget = target;
	_cameraDirection = glm::normalize ( _transform.GetPosition ( ) - _cameraTarget );
	glm::vec3 up = glm::vec3 ( 0.0f, 1.0f, 0.0f );
	glm::vec3 right = glm::normalize ( glm::cross ( up, _cameraDirection ) );
	_cameraUp = glm::cross ( _cameraDirection, right );
}



Transform & Camera::GetTransform ( )
{
	return _transform;
}

glm::mat4 Camera::GetViewMatrix ( )
{
	// in lab 4 Bryan multiples the View Matrix with the Projection matrix here instead of passing the projection matrix seperatly as a unform.
	// Bryan also multiplies the combined View Project matrix with the Model matrix in the application before sending the MVP (Model View Matrix) 
	// as a whole to the vertex shader.
	// I have opeted to pass the three matrixes to the vertex shader seperatly so that the GPU can do this calculation.


	// these lines of code will result in a camera that is always looking at the target position in world space.
	//glm::vec3 up = glm::vec3 ( 0.0f, 1.0f, 0.0f );
	//return glm::lookAt ( _transform.GetPosition( ), _cameraTarget, up );

	
	// this line will result in a matrix where the camera will always look forward rather than at a defined target position in world space.
	return glm::lookAt ( _transform.GetPosition ( ), _transform.GetPosition ( ) + _cameraForward, _cameraUp );

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