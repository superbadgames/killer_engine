#include <Engine/Cell.h>

namespace KillerEngine 
{
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
	Cell::Cell(void) :  _position(0,0),
						_color(0,0,0),
						_width(NULL),
						_height(NULL),
						_vertexPositions(NULL),
						_vertexColors(NULL),
						_vertexUvs(NULL)
	{ _renderer = Renderer::Instance(); }
//==========================================================================================================================
//
//ShutDown
//							  					 
//==========================================================================================================================
//Implement later, when I understand more about what needs to happen here.

} //End namespace