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
		glm::mat4 rotX = glm::rotate ( _rotation.x, glm::vec3 ( 1.0, 0.0, 0.0 ) );
		glm::mat4 rotY = glm::rotate ( _rotation.y, glm::vec3 ( 0.0, 1.0, 0.0 ) );
		glm::mat4 rotZ = glm::rotate ( _rotation.z, glm::vec3 ( 0.0, 0.0, 1.0 ) );
		glm::mat4 rotMat = rotX * rotY * rotZ;
		return posMat * rotMat * scaleMat;
	}

#pragma region Getters

	inline glm::vec3 * GetPos ( )
	{
		return &_position;
	} 

	inline glm::vec3* GetRot() 
	{ 
		return &_rotation; 
	} 

	inline glm::vec3* GetScale() 
	{ 
		return &_scale; 
	}

#pragma endregion

#pragma region Setters

	inline void SetPos ( glm::vec3 & pos )
	{
		this->_position = pos;
	} 

	inline void SetRot(glm::vec3& rot) 
	{
		this->_rotation = rot; 
	}

	inline void SetScale(glm::vec3& scale) 
	{ 
		this->_scale = scale; 
	} 

#pragma endregion

protected: 

private: 
	glm::vec3 _position; 
	glm::vec3 _rotation; 
	glm::vec3 _scale; 

};