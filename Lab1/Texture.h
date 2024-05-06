#pragma once 

#include <string> 
#include <GL\glew.h>

class Texture
{
	friend class Renderer;

public: 
	Texture ( );
	Texture ( const std::string & fileName );
	Texture ( const char * fileName );
	~Texture ( );
	
	void LoadTexture ( const char * filename );

	// bind up to 80 in OpenGL 4 textures. 
	// true limit is determined at runtime.
	// On Nvidia GForce 1050TI it is 192.
	void Bind ( unsigned int unit ); 

protected: 

private:

	void SetDefaultTexture ( );

	GLuint _texture = 0u;
	int _width = 0;
	int	_height = 0;
	int _nrChannels = 0;
	bool _fileLoaded = false;
	GLint _activeBind = -1;

};