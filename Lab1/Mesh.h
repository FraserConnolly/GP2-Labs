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

	void SetTexture ( float u, float v )
	{
		_tex.x = u;
		_tex.y = v;
	}

private:
	glm::vec3 _pos;
	glm::vec3 _col;
	glm::vec2 _tex;
};


class Mesh
{
public:
	Mesh ( );
	Mesh ( const Vertex * vertices, const unsigned int numVertices );
	Mesh ( const Vertex * vertices, const unsigned int numVertices, const  unsigned int * indices, const int numIndicies);

	~Mesh ( );

	void SetMesh ( const Vertex * vertices, const unsigned int numVertices, const  unsigned int * indices, const int numIndicies );
	void Draw ( );

	void LoadTexture ( const char * filename );

private:
	enum
	{
		POSITION_VERTEXBUFFER,
		NUM_BUFFERS
	};

	GLuint _vertexArrayObject;
	GLuint _vertexArrayBuffers [ NUM_BUFFERS ]; // create our array of buffers
	GLuint _elementBufferObject; //GL_ELEMENT_ARRAY_BUFFER

	GLuint _texture;

	unsigned int _drawCount; //how much of the vertexArrayObject do we want to draw
};