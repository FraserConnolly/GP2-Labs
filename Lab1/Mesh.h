#pragma once
#include <glm\glm.hpp>
#include <GL\glew.h>

class Vertex
{
public:

	Vertex ( )
	{ }

	Vertex ( float x, float y, float z )
	{
		_pos.x = x;
		_pos.y = y;
		_pos.z = z;
	}

	Vertex ( const glm::vec3 & pos )
	{
		this->_pos = pos;
	}

private:
	glm::vec3 _pos;
};


class Mesh
{
public:
	Mesh ( );
	Mesh ( Vertex * vertices, unsigned int numVertices );
	~Mesh ( );

	void SetMesh ( Vertex * vertices, unsigned int numVertices );
	void Draw ( );

private:
	enum
	{
		POSITION_VERTEXBUFFER,
		NUM_BUFFERS
	};

	GLuint _vertexArrayObject;
	GLuint _vertexArrayBuffers [ NUM_BUFFERS ]; // create our array of buffers

	unsigned int _drawCount; //how much of the vertexArrayObject do we want to draw
};