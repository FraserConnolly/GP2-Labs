#pragma once

// In game engine architecture, 11.1.2.3 the author suggests that the Vertex class may contain the following data:
// - position
// - diffuse colour and translucency
// - specular colour
// - 0, 1 or more set of tex coords (not normally more than 2)
// - joint indices, and joint weights, for skinning.
// - etc.

// The Vertex class name contains the number of each data type for example
// - Vertex1P would contain 1 set of position data.
// - Vertex1P1D1S2UV4J would contain a skinned vertex with position, diffuse and specular colours and four weighted joint influences.

// Data type key:
// P = Position
// N = Normal
// T = Tangent
// B = Bitangent
// D = Diffuse colour
// S = Specular colour
// UV = Texture coordinates
// K = Joint indices
// W = Joint weights
// J = K and W - a vertex can have multiple joint influences j, each denoted by the pair of numbers ( k, w )


class Vertex1P1D1U
{
public:
	static const int VERTEX_FLOAT_COUNT = 3 + 3 + 2 ;
	static const int VERTEX_POSITION_OFFSET = 0 ;
	static const int VERTEX_COLOUR_OFFSET = 3 ;
	static const int VERTEX_TEXTURE_OFFSET = 6 ;

	enum Attributes
	{
		POSITION,
		COLOUR,
		TEXTURE,

		NUMBER_OF_ATTRIBUTES
	};

	Vertex1P1D1U ( )
	{ }

	Vertex1P1D1U ( const float x, const float y, const float z )
	{
		SetPosition ( x, y, z );
	}

	Vertex1P1D1U ( const float x, const float y, const float z, const float r, const float g, const float b )
	{
		SetPosition ( x, y, z );
		SetColour ( r, g, b );
	}

	Vertex1P1D1U ( const float x, const float y, const float z, const float r, const float g, const float b, const float u, const float v )
	{
		SetPosition ( x, y, z );
		SetColour ( r, g, b );
		SetTexture ( u, v );
	}

	Vertex1P1D1U ( const glm::vec3 & pos )
	{
		_pos = pos;
	}

	Vertex1P1D1U ( const glm::vec3 & pos, const glm::vec3 & col )
	{
		_pos = pos;
		_col = col;
	}

	void SetColour ( const float r, const float g, const float b )
	{
		_col.r = r;
		_col.g = g;
		_col.b = b;
	}

	void SetPosition ( const float x, const float y, const float z )
	{
		_pos.x = x;
		_pos.y = y;
		_pos.z = z;
	}

	void SetTexture ( const float u, const float v )
	{
		_tex.x = u;
		_tex.y = v;
	}

private:
	glm::vec3 _pos;
	glm::vec3 _col = glm::vec3 ( 1.0f, 1.0f, 1.0f ); // default colour to white.
	glm::vec2 _tex;
};
