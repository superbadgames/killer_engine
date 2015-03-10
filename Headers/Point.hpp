/*--------------------------------------------------------------------
Basic container for a Point. 3D is assumed, so only 3D points will be
supported. Since most of the games will be 2D, use Z accordingly.

This is not free to use, and cannot be used without the express permission
of KillerWave. 

Written by Maxwell Miller
---------------------------------------------------------------------*/

#ifndef POINT_HPP
#define POINT_HPP

//User defined includes
#include <Atom.h>

template <typename T>
struct Point {
	T x;
	T y; 
	T z;

	Point(void) : x(0), y(0), z(0) {}
	Point(T a, T b, T c) : x(a), y(b), z(c) {}
};

#endif