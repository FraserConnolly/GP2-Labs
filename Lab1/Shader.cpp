#include "Shader.h"
#include <iostream>
#include <fstream>

#include <glm/gtc/type_ptr.hpp>

#define VertexShaderPath "shader.vert"
#define FragmentShaderPath "shader.frag"

Shader::Shader ( )
	: _program ( 0 ), _shaders ( ), _uniforms ( )
{ 

}

Shader::~Shader ( )
{ 
	// detach and delete our shaders from the program
	for ( size_t i = 0; i < NUM_SHADERS; i++ )
	{
		glDetachShader ( _program, _shaders [ i ] ); //detach shader from program
		glDeleteShader ( _shaders [ i ] ); //delete the shaders
	}
	
	glDeleteProgram ( _program );
}

void Shader::LoadDefaultShaders ( )
{
	LoadShaders ( VertexShaderPath, FragmentShaderPath );
}

void Shader::LoadShaders ( const std::string & vertShader, const std::string & fragShader )
{
	LoadShaders ( vertShader.c_str ( ), fragShader.c_str ( ) );
}

void Shader::LoadShaders ( const char * vertexShader, const char * fargmentShader )
{ 
	_program = glCreateProgram ( );

	_shaders [ 0 ] = CreateShader (
		LoadShader ( vertexShader ),
		GL_VERTEX_SHADER );

	_shaders [ 1 ] = CreateShader (
		LoadShader ( fargmentShader ),
		GL_FRAGMENT_SHADER );

	for ( size_t i = 0; i < NUM_SHADERS; i++ )
	{
		glAttachShader ( _program, _shaders [ i ] ); //attach the shader to the program
	}

	glLinkProgram ( _program ); //create executables that will run on the GPU shaders
	CheckShaderError ( _program, GL_LINK_STATUS, true, "Error: Shader program linking failed" ); // check for error

	// Validate the shader
	glValidateProgram ( _program ); //check the entire program is valid
	CheckShaderError ( _program, GL_VALIDATE_STATUS, true, "Error: Shader program not valid" );

	// Get the location of the uniform variables
	_uniforms [ MODEL_U ]		= glGetUniformLocation ( _program, "model" );
	_uniforms [ VIEW_U ]		= glGetUniformLocation ( _program, "view" );
	_uniforms [ PROJECTION_U ]	= glGetUniformLocation ( _program, "projection" );

	for ( size_t i = 0; i < NUM_SHADERS; i++ )
	{
		glDeleteShader ( _shaders [ i ] ); //delete the shader's source - not needed after compilation
	}
}

void Shader::Bind ( ) const
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

void Shader::CheckShaderError ( GLuint shader, GLuint flag, bool isProgram, const std::string & errorMessage )
{
	GLint success = 0;
	GLchar error [ 1024 ] = { 0 };
	if ( isProgram )
	{
		glGetProgramiv ( shader, flag, &success );
	}
	else
	{
		glGetShaderiv ( shader, flag, &success );
	}

	if ( success == GL_FALSE )
	{
		if ( isProgram )
		{
			glGetProgramInfoLog ( shader, sizeof ( error ), NULL, error );
		}
		else
		{
			glGetShaderInfoLog ( shader, sizeof ( error ), NULL, error );
		}

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

#pragma region Uniform Sets

inline GLint Shader::GetUnifromLocation ( const GLchar * name ) const
{
	return glGetUniformLocation ( _program, name );
}

void Shader::SetUniform ( const GLchar * name, const GLboolean v ) const
{
	glUniform1i ( GetUnifromLocation ( name ), v );
}

void Shader::SetUniform ( const GLchar * name, const GLint v ) const
{
	glUniform1i ( GetUnifromLocation ( name ), v );
}

void Shader::SetUniform ( const GLchar * name, const GLfloat v ) const
{ 
	glUniform1f ( GetUnifromLocation ( name ), v );
}

void Shader::SetUniform ( const GLchar * name, const GLfloat x, const GLfloat y, const GLfloat z ) const
{ 
	glUniform3f ( GetUnifromLocation ( name ), x, y, z );
}

void Shader::SetUniform ( const GLchar * name, const GLfloat x, const GLfloat y, const GLfloat z, const GLfloat w ) const
{
	glUniform4f ( GetUnifromLocation ( name ), x, y, z, w );
}

void Shader::SetUniform ( const GLchar * name, const glm::mat4 & matrix )
{
	glUniformMatrix4fv ( GetUnifromLocation ( name ), 1, GLU_FALSE, glm::value_ptr ( matrix ) );
}

#pragma endregion

void Shader::SetTransform ( const glm::mat4 & modelMatrix )
{
}

void Shader::Update ( Transform & transform )
{ 
	glm::mat4 model = transform.GetModel ( ); 
	// The last parameter of glUnifromMatrix4fv the actual matrix data, 
	// but GLM stores their matrices' data in a way that doesn't always match OpenGL's expectations 
	// so we first convert the data with GLM's built-in function value_ptr.
	glUniformMatrix4fv ( _uniforms [ MODEL_U ], 1, GLU_FALSE, glm::value_ptr ( model ) );

	if ( _camera != nullptr )
	{
		glm::mat4 view = _camera->GetViewMatrix ( );
		glUniformMatrix4fv ( _uniforms [ VIEW_U ], 1, GLU_FALSE, glm::value_ptr ( view ) );

		glm::mat4 projection = _camera->GetProjectionMatrix ( );
		glUniformMatrix4fv ( _uniforms [ PROJECTION_U ], 1, GLU_FALSE, glm::value_ptr ( projection ) );
	}

}

