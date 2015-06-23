/*========================================================================
Basic container for a Point. 3D is assumed, so only 3D points will be
supported. Since most of the games will be 2D, use Z accordingly.

This is not free to use, and cannot be used without the express permission
of KillerWave. 

Written by Maxwell Miller
========================================================================*/

#ifndef POINT_HPP
#define POINT_HPP

//User defined includes
#include <Atom.h>

template <typename T=F32>
struct Point {

	T x;
	T y; 
	T z;
	T w;

	Point(void) : x(0.0f), y(0.0f), z(0.0f), w(1.0f) 	{  }
	Point(T a, T b) : x(a), y(b), z(1.0f), w(1.0f)		{  }
	Point(T a, T b, T c) : x(a), y(b), z(c), w(1.0f) 	{  }
	Point(T a, T b, T c, T d) : x(a), y(b), z(c), w(d) 	{  }

	Point(const Point<T> &p) : x(p.x), y(p.y), z(p.z), w(p.w) {  }

	Point<T>& operator =(const Point<T> &p) {
		x = p.x;
		y = p.y;
		z = p.z;
		w = p.w;
		
		return *this;
	}


	Point operator+(const Point<T>& p) {
		return Point<T>(x + p.x,
						y + p.y,
						z + p.z,
						w + p.w);
	}

	Point<T>& operator +=(const Point<T>& p) {
		x += p.x;
		y += p.y;
		z += p.z;
		w += p.w;

		return *this;
	}
};

#endif