/*--------------------------------------------------------------------
The Cell, or rendering cell is the basic Geometric perimitive that any
game object or entity that is to be rendered will have. It will be the 
OGL verticies that make up the position on the screen. While it will
never be called on its own, it will be part of the rendered game objects.

This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
----------------------------------------------------------------------*/

#ifndef CELL_H
#define CELL_H

//Killer1 inlucdes
#include <Atom.h>
#include <Point.hpp>
#include <Color.hpp>
#include <Renderer.h>

//3rd party and system includes
#include <GL/gl.h>
#include <GL/glu.h>

//Predefined classes
class Renderer;

class Cell {
	Renderer*	   _renderer;
	Point<>        _position;
	Color<>        _color;

	Point<>*	   _vertexPositions = NULL;
	Color<>*	   _vertexColors = NULL;

	F32		       _width;
	F32			   _halfWidth;
	F32			   _height;
	F32			   _halfHeight;

	U32			   _totalPositions = 6;
	U32			   _totalVertices = _totalPositions * 3; //Triangles for this one, making squares

public:
	Cell(void);
	Cell(F32 w, F32 h);
	Cell(F32 w, F32 h, Point<>& p, Color<>& c);

	~Cell(void){}

	//operators
	void operator =(const Cell* cell);

	void ShutDown(void);

	void Render(void);
	//Accessors
	void SetPosition(Point<>& p) { _position = p; }
	void SetColor(Color<>& c) { _color = c; }

	Point<> CellPosition(void)  { return _position; }
	Color<> CellColor(void)     { return _color; }

	Point<>* VertexPositions(void) { return _vertexPositions; }
	Color<>* VertexColors(void)    { return _vertexColors; }

	U32 TotalPositions(void){ return _totalPositions; }
	U32 TotalVertices(void) { return _totalVertices; }

private:
	void _InitVertexPositions(void);
	void _InitVertexColors(void);


};

#endif