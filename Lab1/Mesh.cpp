#include "Mesh.h"

Mesh::Mesh ( )
	:_vertexArrayBuffers ( ), _vertexArrayObject ( 0u )
{ }

Mesh::Mesh ( Vertex * vertices, unsigned int numVertices )
	:_vertexArrayBuffers( ), _vertexArrayObject ( 0u )
{ 
	SetMesh ( vertices, numVertices );
}

Mesh::~Mesh ( )
{ 
	glDeleteVertexArrays ( 1, &_vertexArrayObject );
}

void Mesh::SetMesh ( Vertex * vertices, unsigned int numVertices )
{ 
	if ( _vertexArrayObject != NULL )
	{
		// delete any previous meshes associated with this object.
		glDeleteVertexArrays ( 1, &_vertexArrayObject );
	}

	_drawCount = numVertices;

	glGenVertexArrays ( 1, &_vertexArrayObject );
	glBindVertexArray ( _vertexArrayObject );
	glGenBuffers ( NUM_BUFFERS, _vertexArrayBuffers );
	glBindBuffer ( GL_ARRAY_BUFFER, _vertexArrayBuffers [ POSITION_VERTEXBUFFER ] );
	glBufferData ( GL_ARRAY_BUFFER, _drawCount * sizeof ( vertices [ 0 ] ), vertices, GL_STATIC_DRAW );
	glEnableVertexAttribArray ( 0 );
	glVertexAttribPointer ( 0, 3, GL_FLOAT, GL_FALSE, 0, 0 );
	glBindVertexArray ( 0 );
}

void Mesh::Draw ( )
{ 
	glBindVertexArray ( _vertexArrayObject );
	glDrawArrays ( GL_TRIANGLES, 0, _drawCount );
	glBindVertexArray ( 0 );
}
