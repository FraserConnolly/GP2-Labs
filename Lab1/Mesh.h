#pragma once
#include <glm\glm.hpp>
#include <GL\glew.h>

class Vertex
{
public:
	static const int VERTEX_FLOAT_COUNT = 3 + 3 + 2 ;
	static const int VERTEX_POSITION_OFFSET = 0 ;
	static const int VERTEX_COLOUR_OFFSET = 3 ;
	static const int VERTEX_TEXTURE_OFFSET = 6 ;

	enum Attributes
	{
		POSITION,
		COLOUR,
		TEXTURE,

		NUMBER_OF_ATTRIBUTES
	};

	Vertex ( )
	{ }

	Vertex ( const float x, const float y, const float z )
	{
		SetPosition ( x, y, z );
	}

	Vertex ( const float x, const float y, const float z, const float r, const float g, const float b )
	{
		SetPosition ( x, y, z );
		SetColour ( r, g, b );
	}

	Vertex ( const float x, const float y, const float z, const float r, const float g, const float b, const float u, const float v )
	{
		SetPosition ( x, y, z );
		SetColour ( r, g, b );
		SetTexture ( u, v );
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

	void SetColour ( const float r, const float g, const float b )
	{
		_col.r = r;
		_col.g = g;
		_col.b = b;
	}

	void SetPosition ( const float x, const float y, const float z )
	{
		_pos.x = x;
		_pos.y = y;
		_pos.z = z;
	}

	void SetTexture ( const float u, const float v )
	{
		_tex.x = u;
		_tex.y = v;
	}

private:
	glm::vec3 _pos;
	glm::vec3 _col = glm::vec3( 1.0f, 1.0f, 1.0f ); // default colour to white.
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

private:

	/*
	* Note that in Lab 3 Bryan has the vertex data split into multiple lists (vectors) of data (position and texture coordinates)
	* so that they can each have their own buffer in memory.
	* For the time being I have decided to go with the approach on Lean OpenGL where only one OpenGL buffer is created.
	* Bryan's approach means that stride and offset (pointer) are left at 0 but at the expense of copying the vertex data
	* into the mesh class instead of just holding a pointer to that data.
	*/

	enum
	{
		POSITION_VERTEXBUFFER,
		NUM_BUFFERS
	};

	GLuint _vertexArrayObject;
	GLuint _vertexArrayBuffers [ NUM_BUFFERS ]; // create our array of buffers
	GLuint _elementBufferObject; //GL_ELEMENT_ARRAY_BUFFER

	unsigned int _drawCount; //how much of the vertexArrayObject do we want to draw
	unsigned int _indiciesCount; 
};