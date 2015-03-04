/*--------------------------------------------------------------------
A Vector class that will follow the rules of Mathematics. The equations 
that the Vectors use for each operation were taken from 3D Math Primer 
for Graphics and Game Development by Dunn and Parberry. 

It is called Vector because it will only support 3D vectors. For any 2D 
work, simply adapt by not using the z axis (although you should not that
there will be some operations that will not support this, such as the 
cross multiplication operation. 

This is not free to use, and cannot be used without the express permission
of KillerWave. 

Written by Maxwell Miller
---------------------------------------------------------------------*/

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <Atom.h>

template<typename T>
class Vector {
public:
	Vector(){}
	Vector(T xT, T yT, T zT) {
		x = xT;
		y = yT;
		z = zT;

	}
	~Vector<T>(){}

	T x;
	T y;
	T z;

	//operator overloads
	Vector<T> operator +(const Vector<T>& a) {
		return Vector<T>(x+a.x,
						 y+a.y,
						 z+a.z);
	}

	void operator +=(const Vector<T>& a) {
		x += a.x;
		y += a.y;
		z += a.z;
	}

	Vector<T> operator-(const Vector<T>& s) {
		return Vector<T>(x-s.x,
						 y-s.y,
						 z-s.z);
	}

	void operator -=(const Vector<T>& s) {
		x -= s.x;
		y -= s.y;
		z -= s.z;
	}
	//void operator =(const Vector<T>& s)

	//Multiply by a scalar
	Vector<T> operator *(const T m) {
		return Vector<T>(x*m,
						 y*m,
						 z*m);
	}

	void operator *=(const T m) {
		x *= m;
		y *= m;
		z *= m;
	}

	//Vector Dot Operations will return a scalar value
	T operator *(const Vector<T>& m) {
		return (x * m.x) +
		       (y * m.y) +
		       (z * m.z);
	}
	//T& operator *+(const Vector<T>& m);

	//Vector Cross operation will return a Vector
	Vector<T> X(const Vector<T>& m) { return Vector<T>((y*m.z - z*m.y), (z*m.x - x*m.z), (x*m.y - y*m.x)); }

	//Division by scalar
	Vector<T> operator /(const T d) {
		//if(d == 0) {return NULL;}

		return Vector<T>(x / d,
						 y / d,
						 z / d);
	}

	void operator /=(const T d) {
		if (d == 0) { d == 1; }

		x /= d;
		y /= d;
		z /= d;
	}

	T Magnitude() { return sqrt((x*x) + (y*y) + (z*z)); }

	Vector<T> Unit() { return Vector<T>((x/Magnitude()), (y/Magnitude()), (z/Magnitude())); }

};

#endif
