#pragma once 
#include <string> 
#include <GL\glew.h>

class Texture
{

public: 
	Texture ( );
	Texture ( const std::string & fileName );
	Texture ( const char * fileName );
	~Texture ( );
	
	void LoadTexture ( const char * filename );
	void Bind ( unsigned int unit ); // bind upto 32 textures

protected: 

private:

	void SetDefaultTexture ( );

	GLuint _texture = 0u;
	int _width = 0;
	int	_height = 0;
	int _nrChannels = 0;
	bool _fileLoaded = false;

};