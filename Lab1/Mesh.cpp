#include "Mesh.h"
#include "stb/stb_image.h"
#include <iostream>

Mesh::Mesh ( )
	: _vertexArrayBuffers ( ), _vertexArrayObject ( 0u ), _elementBufferObject ( 0u ), _texture ( 0u ), _drawCount ( 0 )
{ }

Mesh::Mesh ( const Vertex * vertices, const unsigned int numVertices )
	: _vertexArrayBuffers( ), _vertexArrayObject ( 0u ), _elementBufferObject( 0u ), _texture ( 0u ), _drawCount ( 0 )
{ 
	SetMesh ( vertices, numVertices, nullptr, 0 );
}

Mesh::Mesh ( const Vertex * vertices, const unsigned int numVertices, const  unsigned int * indices, const int indiciesCount )
	: _vertexArrayBuffers ( ), _vertexArrayObject ( 0u ), _elementBufferObject ( 0u ), _texture ( 0u ), _drawCount ( 0 )
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

	glGenVertexArrays ( 1, &_vertexArrayObject );
	glBindVertexArray ( _vertexArrayObject );
	glGenBuffers ( NUM_BUFFERS, _vertexArrayBuffers );
	glGenBuffers ( NUM_BUFFERS, &_elementBufferObject );
	glBindBuffer ( GL_ARRAY_BUFFER, _vertexArrayBuffers [ POSITION_VERTEXBUFFER ] );
	glBufferData ( GL_ARRAY_BUFFER, _drawCount * sizeof ( vertices [ 0 ] ), vertices, GL_STATIC_DRAW );

	if ( indiciesCount > 0 && indices != nullptr )
	{
		glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, _elementBufferObject );
		glBufferData ( GL_ELEMENT_ARRAY_BUFFER, sizeof ( float ) * indiciesCount, indices, GL_STATIC_DRAW );
	}

	// position attribute
	glVertexAttribPointer ( 0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof ( float ), ( void * ) 0 );
	glEnableVertexAttribArray ( 0 );
	// color attribute
	glVertexAttribPointer ( 1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof ( float ), ( void * ) ( 3 * sizeof ( float ) ) );
	glEnableVertexAttribArray ( 1 );
	// texture attribute
	glVertexAttribPointer ( 2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof ( float ), ( void * ) ( 6 * sizeof ( float ) ) );
	glEnableVertexAttribArray ( 2 );

	glBindVertexArray ( 0 );
}

void Mesh::Draw ( )
{ 
	glBindVertexArray ( _vertexArrayObject );
	if ( _texture >= 0 )
	{
		glBindTexture ( GL_TEXTURE_2D, _texture );
		glDrawElements ( GL_TRIANGLES, _drawCount, GL_UNSIGNED_INT, 0 );
	}
	else
	{
		glDrawArrays ( GL_TRIANGLES, 0, _drawCount );
	}
	glBindVertexArray ( 0 );
}

void Mesh::LoadTexture ( const char * filename )
{ 
	glGenTextures ( 1, &_texture );

	glBindTexture ( GL_TEXTURE_2D, _texture );
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	// load and generate the texture
	int width, height, nrChannels;
	unsigned char * data = stbi_load ( filename, &width, &height, &nrChannels, 0 );

	if ( data )
	{
		glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data );
		glGenerateMipmap ( GL_TEXTURE_2D );
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free ( data );
}
