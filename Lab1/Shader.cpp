#include "Shader.h"
#include <iostream>
#include <fstream>

Shader::Shader ( )
	: _program( 0 ), _shaders ( )
{ 

}

Shader::Shader ( const std::string & filename )
	: _program ( 0 ), _shaders ( )
{
	// not yet implemented
}

Shader::~Shader ( )
{ 
	// detach and delete our shaders from the program
	for ( size_t i = 0; i < NUM_SHADERS; i++ )
	{
		glDetachShader ( _program, _shaders [ i ] ); //detach shader from program
		glDeleteShader ( _shaders [ i ] ); //delete the sahders
	}
	
	glDeleteProgram ( _program );
}

void Shader::LoadDefaultShaders ( )
{ 
	_program = glCreateProgram ( );

	_shaders [ 0 ] = CreateShader (
		LoadShader ( "shader.vert" ),
		GL_VERTEX_SHADER );

	_shaders [ 1 ] = CreateShader (
		LoadShader ( "shader.frag" ),
		GL_FRAGMENT_SHADER );

	for ( size_t i = 0; i < NUM_SHADERS; i++ )
	{
		glAttachShader ( _program, _shaders [ i ] );
	}

	glBindAttribLocation ( _program, 0, "position" );

	glLinkProgram ( _program ); //create executables that will run on the GPU shaders
	CheckShaderError ( _program, GL_LINK_STATUS, true, "Error: Shader program linking failed" ); // cheack for error

	// validate the shader
	glValidateProgram ( _program ); //check the entire program is valid
	CheckShaderError ( _program, GL_VALIDATE_STATUS, true, "Error: Shader program not valid" );
}

void Shader::Bind ( )
{ 
	glUseProgram ( _program );
}

std::string Shader::LoadShader ( const std::string & fileName )
{
	std::ifstream file;
	file.open ( ( fileName ).c_str ( ) );
	std::string output;
	std::string line;
	if ( file.is_open ( ) )
	{
		while ( file.good ( ) )
		{
			getline ( file, line );
			output.append ( line + "\n" );
		}
	}
	else
	{
		std::cerr << "Unable to load shader: " << fileName << std::endl;
	}
	return output;
}

void Shader::CheckShaderError ( GLuint shader, GLuint flag, bool isProgram, const std::string &
								errorMessage )
{
	GLint success = 0;
	GLchar error [ 1024 ] = { 0 };
	if ( isProgram )
		glGetProgramiv ( shader, flag, &success );
	else
		glGetShaderiv ( shader, flag, &success );
	if ( success == GL_FALSE )
	{
		if ( isProgram )
			glGetProgramInfoLog ( shader, sizeof ( error ), NULL, error );
		else
			glGetShaderInfoLog ( shader, sizeof ( error ), NULL, error );
		std::cerr << errorMessage << ": '" << error << "'" << std::endl;
	}
}

GLuint Shader::CreateShader ( const std::string & text, GLenum type )
{
	auto shader = glCreateShader ( type );
	
	if ( shader == 0 ) //if == 0 shader no created
	{
		std::cerr << "Error type creation failed " << type << std::endl;
		return 0;
	}

	const GLchar * source [ 1 ];
	source[ 0 ] = text.c_str ( );
	glShaderSource ( shader, 1, source, NULL );
	glCompileShader ( shader );

	CheckShaderError ( shader, GL_COMPILE_STATUS, false, "Error compiling shader!" ); //check for compile error

	return shader;
}
