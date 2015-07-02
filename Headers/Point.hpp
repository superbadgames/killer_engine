/*========================================================================
yTasic container for a Point. 3D is assumed, so only 3D points will be
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
private:
	T _x;
	T _y; 
	T _z;
	T _w;

public:
	Point(void) 				  : _x(0.0f), _y(0.0f), _z(T(0)), _w(T(1)) 	{  }
	Point(T xT, T yT) 			  : _x(xT),  _y(yT),    _z(T(0)), _w(T(1))	{  }
	Point(T xT, T yT, T zT)       : _x(xT),  _y(yT),    _z(zT),   _w(T(1)) 	{  }
	Point(T xT, T yT, T zT, T wT) : _x(xT),  _y(yT),    _z(zT),   _w(wT) 	{  }

	Point(const Point<T> &p) : _x(p.GetX()), _y(p.GetY()), _z(p.GetZ()), _w(p.GetW()) {  }

//=====Accessors=====
	T GetX() const { return _x; }
	T GetY() const { return _y; }
	T GetZ() const { return _z; }
	T GetW() const { return _w; }

//=====Operators=====
	//Copy
	Point<T>& operator =(const Point<T>& p) {
		_x = p.GetX();
		_y = p.GetY();
		_z = p.GetZ();
		
		return *this;
	}

	//Add to Point
	Point operator +(const Point<T>& p) {
		return Point<T>(_x + p.GetX(),
						_y + p.GetY(),
						_z + p.GetZ(),
						_w );
	}

	Point<T>& operator +=(const Point<T>& p) {
		_x += p.GetX();
		_y += p.GetY();
		_z += p.GetZ();

		return *this;
	}

	//Multiply by Point
	Point<T> operator *(const Point<T>& p) {
		return Point<T>(_x * p.GetX(),
						_y * p.GetY(),
						_z * p.GetZ(),
						_w );
	}

	Point<T>& operator *=(const Point<T>& p) {
		_x *= p.GetX();
		_y *= p.GetY();
		_z *= p.GetZ();

		return *this;
	}

	//Multiply by scalar
	Point<T> operator *(const T s) {
		return Point<T>(_x * s,
						_y * s,
						_z * s,
						_w );
	}

	Point<T>& operator *=(const T s) {
		_x *= s;
		_y *= s;
		_z *= s;

		return *this;
	}
};

#endif