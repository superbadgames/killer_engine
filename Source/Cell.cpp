#include <Cell.h>

//------------------------------------------------------------------------------------------------
//Constructors
//------------------------------------------------------------------------------------------------
//Default
Cell::Cell(void) {
	_vertexPositions = new point[_totalPositions];
	_vertexColors    = new color[_totalPositions];

	_renderer = Renderer::Instance();
}

//Width and Height only
Cell::Cell(F32 w, F32 h) {
	_width  	= w;
	_halfWidth  = w / 2;
	_height 	= h;
	_halfHeight = h / 2;

	_vertexPositions = new point[_totalPositions];
	_vertexColors	 = new color[_totalPositions];

	_renderer = Renderer::Instance();
}

//Width, Height, Position, Color
Cell::Cell(F32 w, F32 h, point& p, color& c) {
	_width 		= w;
	_halfWidth  = w / 2;
	_height 	= h;
	_halfHeight = h / 2;

	_position = p;
	_color    = c;

	_vertexPositions = new point[_totalPositions];
	_vertexColors	 = new color[_totalPositions];

	_renderer = Renderer::Instance();
}

//------------------------------------------------------------------------------------------------
//ShutDown
//------------------------------------------------------------------------------------------------
void Cell::ShutDown(void) {
	delete[] _vertexPositions;
	delete[] _vertexColors;
}

//---------------------------------------------------------------------------------------------------------
//Operators
//---------------------------------------------------------------------------------------------------------
void Cell::operator=(const Cell* cell) {
	_renderer   	= Renderer::Instance();
	_position   	= cell->_position;
	_color      	= cell->_color;
	_width      	= cell->_width;
	_halfWidth  	= cell->_halfWidth;
	_height     	= cell->_height;
	_halfHeight 	= cell->_halfHeight;
	_totalPositions = cell->_totalPositions;
	_totalVertices  = cell->_totalVertices;
}

//------------------------------------------------------------------------------------------------
//Render
//------------------------------------------------------------------------------------------------
void Cell::Render(void) {
	_InitVertexPositions();
	_InitVertexColors();

	_renderer->AddCell(*this);
}

//------------------------------------------------------------------------------------------------
//SetEvenScale
//------------------------------------------------------------------------------------------------
void Cell::SetEvenScale(F32 scale) {
	_width      = scale;
	_height     = scale;
	_halfWidth  = scale / 2;
	_halfHeight = scale / 2;
}


//------------------------------------------------------------------------------------------------
//_InitVertexPositions
//------------------------------------------------------------------------------------------------
void Cell::_InitVertexPositions(void) {
	//Vertices of triangle 1
	_vertexPositions[0] = point(_position.GetX() -_halfWidth, _position.GetY() -_halfHeight, _position.GetZ()); //Bottom Left
	_vertexPositions[1] = point(_position.GetX() +_halfWidth, _position.GetY() -_halfHeight, _position.GetZ()); //Bottom Right
	_vertexPositions[2] = point(_position.GetX() -_halfWidth, _position.GetY() +_halfHeight, _position.GetZ()); //Top Left

	//Verticies of triangle 2
	_vertexPositions[3] = point(_position.GetX() +_halfWidth, _position.GetY() -_halfHeight, _position.GetZ()); //Bottom Right
	_vertexPositions[4] = point(_position.GetX() +_halfWidth, _position.GetY() +_halfHeight, _position.GetZ()); //Top Right
	_vertexPositions[5] = point(_position.GetX() -_halfWidth, _position.GetY() +_halfHeight, _position.GetZ()); //Top Left
}

//------------------------------------------------------------------------------------------------
//_InitVertexColors
//------------------------------------------------------------------------------------------------
void Cell::_InitVertexColors(void) {
	for(U32 i = 0; i < _totalPositions; i++) {
		_vertexColors[i] = _color;
	}
}