#pragma once
#include <glm/glm.hpp> 
#include <glm/gtx/transform.hpp> 

struct Transform
{
public: 
	Transform ( const glm::vec3 & pos = glm::vec3 ( ), const glm::vec3 & rot = glm::vec3 ( ), const glm::vec3 & scale = glm::vec3 ( 1.0f, 1.0f, 1.0f ) )
	{
		this->_position = pos; 
		this->_rotation = rot; 
		this->_scale = scale;
	}

	inline glm::mat4 GetModel ( ) const //runs as compile time 
	{
		glm::mat4 posMat = glm::translate ( _position );
		glm::mat4 scaleMat = glm::scale ( _scale );

		// won't this result in Gimble lock?
		glm::mat4 rotX = glm::rotate ( _rotation.x, glm::vec3 ( 1.0f, 0.0f, 0.0f ) );
		glm::mat4 rotY = glm::rotate ( _rotation.y, glm::vec3 ( 0.0f, 1.0f, 0.0f ) );
		glm::mat4 rotZ = glm::rotate ( _rotation.z, glm::vec3 ( 0.0f, 0.0f, 1.0f ) );
		glm::mat4 rotMat = rotX * rotY * rotZ;

		// matrices are multiplied in reverse order, so we scale, then rotate, then translate.
		return posMat * rotMat * scaleMat;
	}

#pragma region Getters

	inline const glm::vec3 & GetPosition ( ) const
	{
		return _position;
	} 

	inline const glm::vec3 & GetRotation() const
	{ 
		return _rotation; 
	} 

	inline const glm::vec3 & GetScale() const
	{ 
		return _scale; 
	}

#pragma endregion

#pragma region Setters

	inline void SetPosition ( const glm::vec3 & pos )
	{
		_position = pos;
	} 

	inline void SetPosition ( const float x, const float y, const float z )
	{
		_position.x = x;
		_position.y = y;
		_position.z = z;
	}

	inline void SetRotation( const glm::vec3 & rot) 
	{
		_rotation = rot; 
	}

	inline void SetRotation ( const float x, const float y, const float z )
	{
		_rotation.x = x;
		_rotation.y = y;
		_rotation.z = z;
	}
	
	inline void SetEulerRotation ( const float x, const float y, const float z )
	{ 
		_rotation.x = glm::radians( x );
		_rotation.y = glm::radians( y );
		_rotation.z = glm::radians( z );
	}

	inline void SetScale(const glm::vec3 & scale) 
	{ 
		_scale = scale; 
	} 

	inline void SetScale ( const float x, const float y, const float z )
	{
		_scale.x = x;
		_scale.y = y;
		_scale.z = z;
	}

	inline void SetScale ( const float s )
	{
		_scale.x = s;
		_scale.y = s;
		_scale.z = s;
	}

#pragma endregion

protected: 

private: 
	glm::vec3 _position; 
	glm::vec3 _rotation; 
	glm::vec3 _scale; 

};