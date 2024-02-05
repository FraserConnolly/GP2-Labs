#pragma once
#include <string>
#include <GL\glew.h>

class Shader
{
public:

	Shader ( );
	Shader ( const std::string & filename );
	~Shader ( );
	
	void LoadDefaultShaders ( );
	void Bind ( ); //Set gpu to use our shaders
	std::string LoadShader ( const std::string & fileName );
	void CheckShaderError ( GLuint shader, GLuint flag, bool isProgram, const std::string &
							errorMessage );
	GLuint CreateShader ( const std::string & text, GLenum type );

private:
	
	static const unsigned int NUM_SHADERS = 2; // number of shaders
	
	Shader ( const Shader & other )
		:_program( 0 ), _shaders { 0, 0 }
	{ }
	
	void operator=( const Shader & other )
	{ }
	
	GLuint _program; // Track the shader program
	GLuint _shaders [ NUM_SHADERS ]; //array of shaders
};