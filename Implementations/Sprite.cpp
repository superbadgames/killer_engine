#include <Engine/Sprite.h>

namespace KillerEngine 
{
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
	Sprite::Sprite(void) :  _vertexPositions(NULL),
						    _vertexColors(NULL),
						    _vertexUvs(NULL),
						    _width(NULL),
						    _height(NULL),
						    _color(),
						    _texture()
	{ _renderer = Renderer::Instance(); }

	Sprite::Sprite(const F32 width, const F32 height) :  _vertexPositions(NULL),
											     _vertexColors(NULL),
											     _vertexUvs(NULL),
											     _width(width),
											     _height(height),
											     _color(),
											     _texture()
	{ _renderer = Renderer::Instance(); }

	Sprite::Sprite(const F32 width, const F32 height, Col& col) :  _vertexPositions(NULL),
																	     _vertexColors(NULL),
																	     _vertexUvs(NULL),
																	     _width(width),
																	     _height(height),
																	     _color(col),
																	     _texture()
	{ _renderer = Renderer::Instance(); }

	Sprite::Sprite(const F32 width, const F32 height, Texture& texture) :  _vertexPositions(NULL),
																			     _vertexColors(NULL),
																			     _vertexUvs(NULL),
																			     _width(width),
																			     _height(height),
																			     _color(),
																			     _texture(texture)
	{ _renderer = Renderer::Instance(); }
	
	Sprite::Sprite(const F32 width, const F32 height, Col& col, Texture& texture) :  _vertexPositions(NULL),
																					 _vertexColors(NULL),
																					 _vertexUvs(NULL),
																					 _width(width),
																					 _height(height),
																					 _color(col),
																					 _texture(texture)
	{ _renderer = Renderer::Instance(); }																		     
//==========================================================================================================================
//
//ShutDown
//							  					 
//==========================================================================================================================
//Implement later, when I understand more about what needs to happen here.


//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
/*
	void Sprite::SetPosition(Vec2& position)
	{
		_position = position;

		v_SetVertexPositions();
	}

	void Sprite::SetColor(Col& col)
	{
		_color = col;

		v_SetVertexColors();
	}

	void Sprite::SetTexture(Texture& texture, const F32 top, const F32 bottom, const F32 right, const F32 left)
	{
		_texture = texture;

		v_SetTextureCoords(top, bottom, left, right);
	}
*/
	
} //End namespace