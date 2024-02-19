#include "Mesh.h"
#include "stb/stb_image.h"
#include <iostream>

Mesh::Mesh ( )
	: _vertexArrayBuffers ( ), 
	_vertexArrayObject ( 0u ),
	_elementBufferObject ( 0u ), 
	_drawCount ( 0 ),
	_indiciesCount ( 0 )
{ }

Mesh::~Mesh ( )
{ 
	glDeleteVertexArrays ( 1, &_vertexArrayObject );
}

void Mesh::loadModel ( const std::string & filename )
{
	IndexedModel model = OBJModel ( filename ).ToIndexedModel ( );

	initModel ( model );

	// position attribute
	glVertexAttribPointer ( Vertex1P1U1N::POSITION, 3, GL_FLOAT, GL_FALSE, Vertex1P1U1N::VERTEX_FLOAT_COUNT * sizeof ( float ), ( void * ) ( Vertex1P1U1N::VERTEX_POSITION_OFFSET * sizeof ( float ) ) );
	glEnableVertexAttribArray ( Vertex1P1U1N::POSITION );

	// texture attribute
	glVertexAttribPointer ( Vertex1P1U1N::TEXTURE, 2, GL_FLOAT, GL_FALSE, Vertex1P1U1N::VERTEX_FLOAT_COUNT * sizeof ( float ), ( void * ) ( Vertex1P1U1N::VERTEX_TEXTURE_OFFSET * sizeof ( float ) ) );
	glEnableVertexAttribArray ( Vertex1P1U1N::TEXTURE );
	
	// normal attribute
	glVertexAttribPointer ( Vertex1P1U1N::NORMAL, 3, GL_FLOAT, GL_FALSE, Vertex1P1U1N::VERTEX_FLOAT_COUNT * sizeof ( float ), ( void * ) ( Vertex1P1U1N::VERTEX_NORMAL_OFFSET * sizeof ( float ) ) );
	glEnableVertexAttribArray ( Vertex1P1U1N::NORMAL );
	
	glBindVertexArray ( 0 ); // unbind our VAO
}

void Mesh::initModel ( const IndexedModel & model )
{ 

	_drawCount = model.indices.size ( );

	glGenVertexArrays ( 1, &_vertexArrayObject );
	glBindVertexArray ( _vertexArrayObject );
	glGenBuffers ( NUM_BUFFERS, _vertexArrayBuffers );
	glGenBuffers ( NUM_BUFFERS, &_elementBufferObject );
	glBindBuffer ( GL_ARRAY_BUFFER, _vertexArrayBuffers [ POSITION_VERTEXBUFFER ] );

	//move the data to the GPU - type of data, size of data, starting address (pointer) of data, where do we store the data on the GPU
	glBufferData ( GL_ARRAY_BUFFER, _drawCount * sizeof ( vertices [ 0 ] ), vertices, GL_STATIC_DRAW );

	glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, _elementBufferObject );
	glBufferData ( GL_ELEMENT_ARRAY_BUFFER, sizeof ( float ) * model.indices.size(), sizeof( ), GL_STATIC_DRAW );


	glGenBuffers ( NUM_BUFFERS, vertexArrayBuffers ); //generate our buffers based of our array of data/buffers - GLuint vertexArrayBuffers[NUM_BUFFERS];

	glBindBuffer ( GL_ARRAY_BUFFER, vertexArrayBuffers [ POSITION_VERTEXBUFFER ] ); //tell opengl what type of data the buffer is (GL_ARRAY_BUFFER), and pass the data
	glBufferData ( GL_ARRAY_BUFFER, model.positions.size ( ) * sizeof ( model.positions [ 0 ] ), &model.positions [ 0 ], GL_STATIC_DRAW ); //move the data to the GPU - type of data, size of data, starting address (pointer) of data, where do we store the data on the GPU (determined by type)
	glEnableVertexAttribArray ( 0 );
	glVertexAttribPointer ( 0, 3, GL_FLOAT, GL_FALSE, 0, 0 );

	glBindBuffer ( GL_ARRAY_BUFFER, vertexArrayBuffers [ TEXCOORD_VB ] ); //tell opengl what type of data the buffer is (GL_ARRAY_BUFFER), and pass the data
	glBufferData ( GL_ARRAY_BUFFER, model.positions.size ( ) * sizeof ( model.texCoords [ 0 ] ), &model.texCoords [ 0 ], GL_STATIC_DRAW ); //move the data to the GPU - type of data, size of data, starting address (pointer) of data, where do we store the data on the GPU
	glEnableVertexAttribArray ( 1 );
	glVertexAttribPointer ( 1, 2, GL_FLOAT, GL_FALSE, 0, 0 );

	glBindBuffer ( GL_ARRAY_BUFFER, vertexArrayBuffers [ NORMAL_VB ] );
	glBufferData ( GL_ARRAY_BUFFER, sizeof ( model.normals [ 0 ] ) * model.normals.size ( ), &model.normals [ 0 ], GL_STATIC_DRAW );
	glEnableVertexAttribArray ( 2 );
	glVertexAttribPointer ( 2, 3, GL_FLOAT, GL_FALSE, 0, 0 );

	glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, vertexArrayBuffers [ INDEX_VB ] ); //tell opengl what type of data the buffer is (GL_ARRAY_BUFFER), and pass the data
	glBufferData ( GL_ELEMENT_ARRAY_BUFFER, model.indices.size ( ) * sizeof ( model.indices [ 0 ] ), &model.indices [ 0 ], GL_STATIC_DRAW ); //move the data to the GPU - type of data, size of data, starting address (pointer) of data, where do we store the data on the GPU

	glBindVertexArray ( 0 ); // unbind our VAO


}

void Mesh::SetMesh ( const Vertex1P1D1U  * vertices, const unsigned int numVertices, const unsigned int * indices, const int indiciesCount)
{ 
	if ( _vertexArrayObject != NULL )
	{
		// delete any previous meshes associated with this object.
		glDeleteVertexArrays ( 1, &_vertexArrayObject );
	}

	_indiciesCount = indiciesCount;

	IndexedModel model;

	for ( unsigned int i = 0; i < numVertices; i++ )
	{
		model.positions.push_back ( vertices [ i ].GetPosition ( ) );
		model.texCoords.push_back ( vertices [ i ].GetTextureCord ( ) );
	}

	for ( unsigned int i = 0; i < _indiciesCount; i++ )
	{
		model.indices.push_back ( indices [ i ] );
	}

	initModel ( model );

	// position attribute
	glVertexAttribPointer ( Vertex1P1D1U::POSITION, 3, GL_FLOAT, GL_FALSE, Vertex1P1D1U::VERTEX_FLOAT_COUNT * sizeof ( float ), ( void * ) ( Vertex1P1D1U::VERTEX_POSITION_OFFSET * sizeof ( float ) ) );
	glEnableVertexAttribArray ( Vertex1P1D1U::POSITION );
	// colour attribute
	glVertexAttribPointer ( Vertex1P1D1U::COLOUR, 3, GL_FLOAT, GL_FALSE, Vertex1P1D1U::VERTEX_FLOAT_COUNT * sizeof ( float ), ( void * ) ( Vertex1P1D1U::VERTEX_COLOUR_OFFSET * sizeof ( float ) ) );
	glEnableVertexAttribArray ( Vertex1P1D1U::COLOUR );
	// texture attribute
	glVertexAttribPointer ( Vertex1P1D1U::TEXTURE, 2, GL_FLOAT, GL_FALSE, Vertex1P1D1U::VERTEX_FLOAT_COUNT * sizeof ( float ), ( void * ) ( Vertex1P1D1U::VERTEX_TEXTURE_OFFSET * sizeof ( float ) ) );
	glEnableVertexAttribArray ( Vertex1P1D1U::TEXTURE );

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

