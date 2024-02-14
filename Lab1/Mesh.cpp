#include "Mesh.h"
#include "stb/stb_image.h"
#include <iostream>

Mesh::Mesh ( )
	: _vertexArrayBuffers ( ), _vertexArrayObject ( 0u ), _elementBufferObject ( 0u ), _drawCount ( 0 )
{ }

Mesh::Mesh ( const Vertex * vertices, const unsigned int numVertices )
	: _vertexArrayBuffers( ), _vertexArrayObject ( 0u ), _elementBufferObject( 0u ), _drawCount ( 0 )
{ 
	SetMesh ( vertices, numVertices, nullptr, 0 );
}

Mesh::Mesh ( const Vertex * vertices, const unsigned int numVertices, const  unsigned int * indices, const int indiciesCount )
	: _vertexArrayBuffers ( ), _vertexArrayObject ( 0u ), _elementBufferObject ( 0u ), _drawCount ( 0 )
{
	SetMesh ( vertices, numVertices, indices, indiciesCount );
}

Mesh::~Mesh ( )
{ 
	glDeleteVertexArrays ( 1, &_vertexArrayObject );
}

void Mesh::SetMesh ( const Vertex  * vertices, const unsigned int numVertices, const unsigned int * indices, const int indiciesCount)
{ 
	if ( _vertexArrayObject != NULL )
	{
		// delete any previous meshes associated with this object.
		glDeleteVertexArrays ( 1, &_vertexArrayObject );
	}

	_drawCount = numVertices;
	_indiciesCount = indiciesCount;

	glGenVertexArrays ( 1, &_vertexArrayObject );
	glBindVertexArray ( _vertexArrayObject );
	glGenBuffers ( NUM_BUFFERS, _vertexArrayBuffers );
	glGenBuffers ( NUM_BUFFERS, &_elementBufferObject );
	glBindBuffer ( GL_ARRAY_BUFFER, _vertexArrayBuffers [ POSITION_VERTEXBUFFER ] );

	//move the data to the GPU - type of data, size of data, starting address (pointer) of data, where do we store the data on the GPU
	glBufferData ( GL_ARRAY_BUFFER, _drawCount * sizeof ( vertices [ 0 ] ), vertices, GL_STATIC_DRAW );

	if ( indiciesCount > 0 && indices != nullptr )
	{
		glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, _elementBufferObject );
		glBufferData ( GL_ELEMENT_ARRAY_BUFFER, sizeof ( float ) * indiciesCount, indices, GL_STATIC_DRAW );
	}

	// position attribute
	glVertexAttribPointer ( Vertex::POSITION, 3, GL_FLOAT, GL_FALSE, Vertex::VERTEX_FLOAT_COUNT * sizeof ( float ), ( void * ) ( Vertex::VERTEX_POSITION_OFFSET * sizeof ( float ) ) );
	glEnableVertexAttribArray ( Vertex::POSITION );
	// colour attribute
	glVertexAttribPointer ( Vertex::COLOUR,   3, GL_FLOAT, GL_FALSE, Vertex::VERTEX_FLOAT_COUNT * sizeof ( float ), ( void * ) ( Vertex::VERTEX_COLOUR_OFFSET   * sizeof ( float ) ) );
	glEnableVertexAttribArray ( Vertex::COLOUR );
	// texture attribute
	glVertexAttribPointer ( Vertex::TEXTURE,  2, GL_FLOAT, GL_FALSE, Vertex::VERTEX_FLOAT_COUNT * sizeof ( float ), ( void * ) ( Vertex::VERTEX_TEXTURE_OFFSET  * sizeof ( float ) ) );
	glEnableVertexAttribArray ( Vertex::TEXTURE );

	glBindVertexArray ( 0 ); // unbind our VAO
}


void Mesh::Draw ( )
{ 
	glBindVertexArray ( _vertexArrayObject );
	if ( _indiciesCount > 0 )
	{
		glDrawElements ( GL_TRIANGLES, _drawCount, GL_UNSIGNED_INT, 0 );
	}
	else
	{
		glDrawArrays ( GL_TRIANGLES, 0, _drawCount );
	}
	glBindVertexArray ( 0 );
}

