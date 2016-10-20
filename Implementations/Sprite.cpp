#include <Engine/Sprite.h>

namespace KillerEngine 
{
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
	Sprite::Sprite(void) :  vertexPositions(NULL),
						    vertexColors(NULL),
						    vertexUvs(NULL),
						    width(NULL),
						    height(NULL),
						    color(),
						    textureID()
	{  }

	Sprite::Sprite(const F32 width, const F32 height) :  vertexPositions(NULL),
													     vertexColors(NULL),
													     vertexUvs(NULL),
													     width(width),
													     height(height),
													     color(),
													     textureID()
	{  }

	Sprite::Sprite(const F32 width, const F32 height, Col& col) :  vertexPositions(NULL),
															       vertexColors(NULL),
															       vertexUvs(NULL),
															       width(width),
															       height(height),
															       color(col),
															       textureID()
	{  }

	Sprite::Sprite(const F32 width, const F32 height, U32 tID) :  vertexPositions(NULL),
														          vertexColors(NULL),
														          vertexUvs(NULL),
														          width(width),
														          height(height),
														          color(),
														          textureID(tID)
	{  }
	
	Sprite::Sprite(const F32 width, const F32 height, Col& col, U32 tID) :  vertexPositions(NULL),
																			vertexColors(NULL),
																			vertexUvs(NULL),
																			width(width),
																			height(height),
																			color(col),
																			textureID(tID)
	{  }																		     
//==========================================================================================================================
//
//ShutDown
//							  					 
//==========================================================================================================================
//Implement later, when I understand more about what needs to happen here.
	
} //End namespace