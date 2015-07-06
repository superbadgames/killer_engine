#include <Cell.h>

//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
//Default
Cell::Cell(void) : _renderer(Renderer::Instance()), _position(), _color(), 
				   _totalWidth(1.0f), _right(0.5f), _left(-0.5f),
				   _totalHeight(1.0f), _top(0.5f), _bottom(-0.5f)  {  }

//Width and Height only
Cell::Cell(F32 w, F32 h): _renderer(Renderer::Instance()), _position(), _color(),
						  _totalWidth(w), _right(w / 2), _left(-w / 2),
						  _totalHeight(h), _top(h / 2), _bottom(-h / 2) {  }

//Width, Height, Position, Color
Cell::Cell(const F32 w, const F32 h, const point& p, const color& c) : _renderer(Renderer::Instance()), _position(p), _color(c),
											   _totalWidth(w), _right(w / 2), _left(-w / 2),
						  					   _totalHeight(h), _top(h / 2), _bottom(-h / 2) {  }

//==========================================================================================================================
//ShutDown
//==========================================================================================================================
//Implement later, when I understand more about what needs to happen her.

//==========================================================================================================================
//
//Operators
//
//==========================================================================================================================
Cell& Cell::operator=(const Cell& cell) {
	_position   	= cell.GetPosition();
	_color      	= cell.GetColor();
	SetDimensions	(cell.GetWidth(), cell.GetHeight());

	return *this;
}

//==========================================================================================================================
//
//RenderAs* 
//
//This is a group of functions that will be used to decide the ultimate end shape of the cell on the screen. This are imple-
//mented directly in the Renderer. 
//
//==========================================================================================================================
void Cell::RenderAsTri(void) { _renderer->AddTri(*this); }
void Cell::RenderAsSqr(void) { _renderer->AddSqr(*this); }
void Cell::RenderAsHex(void) { _renderer->AddHex(*this); }
