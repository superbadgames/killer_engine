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

template <typename T=F32>
struct Point {
	T x;
	T y; 
	T z;

	Point(void): x(0.0f), y(0.0f), z(0.0f) {}
	Point(T a, T b, T c) : x(a), y(b), z(c) {}

	void operator =(const Point<T>& p) {
		x = p.x;
		y = p.y;
		z = p.z;
	}

	void operator =(const Point<T>* p) {
		x = p->x;
		y = p->y;
		z = p->z;
	}

	Point operator+(const Point<T>& p) {
		return Point<T>(x + p.x,
						y + p.y,
						z + p.z);
	}

	void operator +=(const Point<T>& p) {
		x += p.x;
		y += p.y;
		z += p.z;
	}
};

#endif