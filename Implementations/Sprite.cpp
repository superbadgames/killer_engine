#include <Engine/Sprite.h>

namespace KillerEngine 
{
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
	Sprite::Sprite(void) :  _bottomTop(),
							_leftRight(),
						    width(NULL),
						    height(NULL),
						    color(),
						    textureID()
	{  }

	Sprite::Sprite(const F32 width, const F32 height) :  _bottomTop(),
														 _leftRight(),
													     width(width),
													     height(height),
													     color(),
													     textureID()
	{  }

	Sprite::Sprite(const F32 width, const F32 height, Col& col) :  _bottomTop(),
														 		   _leftRight(),
															       width(width),
															       height(height),
															       color(col),
															       textureID()
	{  }

	Sprite::Sprite(const F32 width, const F32 height, U32 tID) :  _bottomTop(),
														 		  _leftRight(),
														          width(width),
														          height(height),
														          color(),
														          textureID(tID)
	{  }
	
	Sprite::Sprite(const F32 width, const F32 height, Col& col, U32 tID) :  _bottomTop(),
														 		   			_leftRight(),
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