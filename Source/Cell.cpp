#include <Cell.h>

//------------------------------------------------------------------------------------------------
//Constructors
//------------------------------------------------------------------------------------------------
//Default
Cell::Cell(void) {
	_vertexPositions = new Point<>[_totalPositions];
	_vertexColors    = new Color<>[_totalPositions];

	_renderer = Renderer::Instance();
}

//Width and Height only
Cell::Cell(F32 w, F32 h) {
	_width  	= w;
	_halfWidth  = w / 2;
	_height 	= h;
	_halfHeight = h / 2;

	_vertexPositions = new Point<>[_totalPositions];
	_vertexColors	 = new Color<>[_totalPositions];

	_renderer = Renderer::Instance();
}

//Width, Height, Position, Color
Cell::Cell(F32 w, F32 h, Point<>& p, Color<>& c) {
	_width 		= w;
	_halfWidth  = w / 2;
	_height 	= h;
	_halfHeight = h / 2;

	_position = p;
	_color = c;

	_vertexPositions = new Point<>[_totalPositions];
	_vertexColors	 = new Color<>[_totalPositions];

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
//_InitVertexPositions
//------------------------------------------------------------------------------------------------
void Cell::_InitVertexPositions(void) {
	//Vertices of triangle 1
	_vertexPositions[0] = new Point<>(_position.x -_halfWidth, _position.y -_halfHeight, _position.z); //Bottom Left
	_vertexPositions[1] = new Point<>(_position.x +_halfWidth, _position.y -_halfHeight, _position.z); //Bottom Right
	_vertexPositions[2] = new Point<>(_position.x -_halfWidth, _position.y +_halfHeight, _position.z); //Top Left

	//Verticies of triangle 2
	_vertexPositions[3] = new Point<>(_position.x +_halfWidth, _position.y -_halfHeight, _position.z); //Bottom Right
	_vertexPositions[4] = new Point<>(_position.x +_halfWidth, _position.y +_halfHeight, _position.z); //Top Right
	_vertexPositions[5] = new Point<>(_position.x -_halfWidth, _position.y +_halfHeight, _position.z); //Top Left
}

//------------------------------------------------------------------------------------------------
//_InitVertexColors
//------------------------------------------------------------------------------------------------
void Cell::_InitVertexColors(void) {
	for(U32 i = 0; i < _totalPositions; i++) {
		_vertexColors[i] = _color;
	}
}