#pragma once

#include <glm\glm.hpp>
#include <GL\glew.h>
#include "Vertex.h"
#include "obj_loader.h"

class Mesh
{
public:
	Mesh ( );
	~Mesh ( );

	void loadModel ( const std::string & filename );

	void SetMesh ( const Vertex1P1D1U * vertices, const unsigned int numVertices, const  unsigned int * indices, const int numIndicies );
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

	void initModel ( const IndexedModel & model );

	GLuint _vertexArrayObject;
	GLuint _vertexArrayBuffers [ NUM_BUFFERS ]; // create our array of buffers
	GLuint _elementBufferObject; //GL_ELEMENT_ARRAY_BUFFER

	unsigned int _drawCount; //how much of the vertexArrayObject do we want to draw
	unsigned int _indiciesCount; 
};