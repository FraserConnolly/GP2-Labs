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

	Vertex ( float x, float y, float z, float r, float g, float b )
	{
		_pos.x = x;
		_pos.y = y;
		_pos.z = z;
		_col.r = r;
		_col.g = g;
		_col.b = b;
	}

	Vertex ( const glm::vec3 & pos )
	{
		_pos = pos;
	}

	Vertex ( const glm::vec3 & pos, const glm::vec3 & col )
	{
		_pos = pos;
		_col = col;
	}

	void SetColour ( float r, float g, float b )
	{
		_col.r = r;
		_col.g = g;
		_col.b = b;
	}

	void SetPosition ( float x, float y, float z )
	{
		_pos.x = x;
		_pos.y = y;
		_pos.z = z;
	}

private:
	glm::vec3 _pos;
	glm::vec3 _col;
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