#pragma once
#include <glm/glm.hpp> 
#include <glm/gtx/transform.hpp> 

#include "Component.h"
#include <vector>

class Transform : public Component
{
public: 

#pragma region Getters

	inline glm::mat4 & GetModel ( )
	{
		if ( m_isDirty )
		{
			glm::mat4 posMat = glm::translate ( m_position );
			glm::mat4 scaleMat = glm::scale ( m_scale );

			// won't this result in Gimble lock?
			glm::mat4 rotX = glm::rotate ( m_rotation.x, glm::vec3 ( 1.0f, 0.0f, 0.0f ) );
			glm::mat4 rotY = glm::rotate ( m_rotation.y, glm::vec3 ( 0.0f, 1.0f, 0.0f ) );
			glm::mat4 rotZ = glm::rotate ( m_rotation.z, glm::vec3 ( 0.0f, 0.0f, 1.0f ) );
			glm::mat4 rotMat = rotX * rotY * rotZ;

			// matrices are multiplied in reverse order, so we scale, then rotate, then translate.
			m_modelMatrix = posMat * rotMat * scaleMat;

			m_isDirty = false;
		}
		return m_modelMatrix;
	}

	inline const glm::vec3 & GetPosition ( ) const
	{
		return m_position;
	} 

	inline const glm::vec3 & GetRotation() const
	{ 
		return m_rotation; 
	} 

	inline const glm::vec3 & GetScale() const
	{ 
		return m_scale; 
	}

#pragma endregion

#pragma region Setters

	inline void SetPosition ( const glm::vec3 & pos )
	{
		m_position = pos;
		SetDirty ( );
	}

	inline void SetPosition ( const float x, const float y, const float z )
	{
		m_position.x = x;
		m_position.y = y;
		m_position.z = z;
		SetDirty ( );
	}

	inline void SetRotation( const glm::vec3 & rot ) 
	{
		m_rotation = rot; 
		SetDirty ( );
	}

	inline void SetRotation ( const float x, const float y, const float z )
	{
		m_rotation.x = x;
		m_rotation.y = y;
		m_rotation.z = z;
		SetDirty ( );
	}
	
	inline void SetEulerRotation ( const float x, const float y, const float z )
	{ 
		m_rotation.x = glm::radians( x );
		m_rotation.y = glm::radians( y );
		m_rotation.z = glm::radians( z );
		SetDirty ( );
	}

	inline void SetScale ( const glm::vec3 & scale )
	{
		m_scale = scale;
		SetDirty ( );
	}

	inline void SetScale ( const float x, const float y, const float z )
	{
		m_scale.x = x;
		m_scale.y = y;
		m_scale.z = z;
		SetDirty ( );
	}

	inline void SetScale ( const float s )
	{
		m_scale.x = s;
		m_scale.y = s;
		m_scale.z = s;
		SetDirty ( );
	}

#pragma endregion

#pragma region Hierarchy

	void SetParent ( Transform * const parent )
	{
		if ( m_parent != nullptr )
		{
			m_parent->RemoveChild ( this );
			// remove use from the existing parent's list of children
		}

		m_parent = parent;
		m_parent->AddChild ( this );
		SetDirty ( );
	}

#pragma endregion

	// Inherited via Component
	void Reset ( ) override
	{
		SetPosition ( 0.0f, 0.0f, 0.0f );
		SetRotation ( 0.0f, 0.0f, 0.0f );
		SetScale ( 1.0f, 1.0f, 1.0f );
	}

	void OnDestroy ( ) override;

protected: 

	void SetDirty ( )
	{
		if ( m_isDirty )
		{
			// already flagged as dirty
			return;
		}

		m_isDirty = true;

		// set the dirty flag for all children too
		for ( auto child : m_children )
		{
			child->SetDirty ( );
		}
	}

#pragma region Hierarchy

	void AddChild ( Transform * const pChild );

	void RemoveChild ( Transform * pChild );

	void Destroy ( );

#pragma endregion

private: 

	friend class GameObject;

	Transform ( const glm::vec3 & pos = glm::vec3 ( ), const glm::vec3 & rot = glm::vec3 ( ), const glm::vec3 & scale = glm::vec3 ( 1.0f, 1.0f, 1.0f ) ) 
		: Component ( ComponentTypes::TRANSFORM )
	{
		SetPosition ( pos );
		SetRotation ( rot );
		SetScale ( scale );
	}

	bool m_isDirty;

	glm::vec3 m_position; 
	glm::vec3 m_rotation; 
	glm::vec3 m_scale; 
	
	glm::mat4 m_modelMatrix;

	Transform * m_parent = nullptr;
	std::vector<Transform *> m_children;

};