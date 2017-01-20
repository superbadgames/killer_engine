#include <Engine/Sprite.h>

namespace KillerEngine 
{
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
	Sprite::Sprite(void) :  uvOrigin(),
							uvLimit(),
						    width(NULL),
						    height(NULL),
						    color(),
						    textureID()
	{  }

	Sprite::Sprite(const F32 width, const F32 height) :  uvOrigin(),
														 uvLimit(),
													     width(width),
													     height(height),
													     color(),
													     textureID()
	{  }

	Sprite::Sprite(const F32 width, const F32 height, Col& col) :  uvOrigin(),
														 		   uvLimit(),
															       width(width),
															       height(height),
															       color(col),
															       textureID()
	{  }

	Sprite::Sprite(const F32 width, const F32 height, U32 tID) :  uvOrigin(),
														 		  uvLimit(),
														          width(width),
														          height(height),
														          color(),
														          textureID(tID)
	{  }
	
	Sprite::Sprite(const F32 width, const F32 height, Col& col, U32 tID) :  uvOrigin(),
														 		   			uvLimit(),
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