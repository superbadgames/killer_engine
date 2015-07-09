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
	T _p[4];

public:
	Point(void) { 
		_p[0] = _p[1] = 0;
		_p[2] = _p[3] = 1;
	}
	
	Point(T xT, T yT) { 
		_p[0] = xT;
		_p[1] = yT;
		_p[2] = 1;
		_p[3] = 1;
	}
	Point(T xT, T yT, T zT) {
		_p[0] = xT;
		_p[1] = yT;
		_p[2] = zT;
		_p[3] = 1;
	}
	Point(T xT, T yT, T zT, T wT){
		_p[0] = xT;
		_p[1] = yT;
		_p[2] = zT;
		_p[3] = wT;
	}

	Point(const Point<T> &p) {
		_p[0] = p.GetX();
		_p[1] = p.GetY();
		_p[2] = p.GetZ();
		_p[3] = p.GetW();
	}

//=====Accessors=====
	const T* Get()  const { return _p; }
	const T  GetX() const { return _p[0]; }
	const T  GetY() const { return _p[1]; }
	const T  GetZ() const { return _p[2]; }
	const T  GetW() const { return _p[3]; }

//=====Operators=====
	//Copy
	Point<T>& operator =(const Point<T>& p) {
		_p[0] = p.GetX();
		_p[1] = p.GetY();
		_p[2] = p.GetZ();
		_p[3] = p.GetW();
		
		return *this;
	}
	//Add to Point
	const Point<T> operator +(const Point<T>& p) {
		return Point<T>(_p[0] + p.GetX(),
			_p[1] + p.GetY(),
			_p[2], //+ p.GetZ(),
			_p[3]);
	}

	Point<T>& operator +=(const Point<T>& p) {
		_p[0] += p.GetX();
		_p[1] += p.GetY();
		//_p[2] += p.GetZ();

		return *this;
	}

	//Multiply by Point
	const Point<T> operator *(const Point<T>& p) const {
		return Point<T>(_p[0] * p.GetX(),
						_p[1] * p.GetY(),
						_p[2] * p.GetZ(),
						_p[3] );
	}

	Point<T>& operator *=(const Point<T>& p) {
		_p[0] *= p.GetX();
		_p[1] *= p.GetY();
		_p[2] *= p.GetZ();

		return *this;
	}

	//Multiply by scalar
	const Point<T> operator *(const T s) const {
		return Point<T>(_p[0] * s,
						_p[1] * s,
						_p[2] * s,
						_p[3] );
	}

	Point<T>& operator *=(const T s) {
		_p[0] *= s;
		_p[1] *= s;
		_p[2] *= s;

		return *this;
	}
};

#endif