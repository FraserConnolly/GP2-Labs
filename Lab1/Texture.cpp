#include "Texture.h"
#include "stb/stb_image.h"
#include <cassert> 
#include <iostream>
#include "Renderer.h"

Texture::Texture ( )
{ 
}

Texture::Texture ( const std::string & fileName )
{ 
	LoadTexture ( fileName.c_str ( ) );
}

Texture::Texture ( const char * fileName )
{ 
	LoadTexture ( fileName );
}

Texture::~Texture ( ) 
{
    glDeleteTextures ( 1, &_texture );
}

void Texture::LoadTexture ( const char * filename )
{
	if ( _texture != 0u )
	{
		// delete any existing texture - to do 
	}


	// load and generate the texture
	//    unsigned char *data = stbi_load(filename, &x, &y, &n, 0);
    // ... process data if not NULL ...
    // ... x = width, y = height, n = # 8-bit components per pixel ...
    // ... replace '0' with '1'..'4' to force that many components per pixel
    // ... but 'n' will always be the number that it would have been if you said 0
	
	// we must use 4 because we later have GL_RGBA which requires all four channels.
	unsigned char * data = stbi_load ( filename, &_width, &_height, &_nrChannels, 4 );

	if ( ! data )
	{
		std::cout << "Failed to load texture" << std::endl;
		_fileLoaded = false;
		return;
	}

	glGenTextures ( 1, &_texture );

	glBindTexture ( GL_TEXTURE_2D, _texture );
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data );
	glGenerateMipmap ( GL_TEXTURE_2D );
	_fileLoaded = true;

	stbi_image_free ( data );
}

void Texture::Bind ( GLint unit )
{
	// check we are working with one of the available textures
	// from OpenGL 4.0 there must be at least 80.
	assert ( unit >= 0 && unit <= Renderer::GetMaxTextureUnits( ) ); 

	if ( _texture == 0u )
	{
		// generate a 1x1 white default texture
		SetDefaultTexture ( );
	}

	glBindTextureUnit ( GL_TEXTURE0 + unit, _texture );
	_activeBind = unit;
	
	// these two functions can be called together with glBindtextureUnit
	//glActiveTexture ( GL_TEXTURE0 + unit ); //set active texture unit 
	//glBindTexture(GL_TEXTURE_2D, _texture); //type of and texture to bind to unit
}

void Texture::SetDefaultTexture ( )
{ 
	if ( _texture != 0u )
	{
		// delete any existing texture - to do 
	}

	glGenTextures ( 1, &_texture );

	glBindTexture ( GL_TEXTURE_2D, _texture );
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	// RGBA values for a single pixel
	unsigned char data[ ] = { 0xff, 0xff, 0xff, 0xff };

	glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, data );
	glGenerateMipmap ( GL_TEXTURE_2D );

}


