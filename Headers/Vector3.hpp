#ifndef VECTOR3_H
#define VECTOR3_H

#include <Atom.h>
#include <type_traits>

template<typename T>
class Vector3 {
public:
	Vector3(){}
	Vector3(T xT, T yT, T zT) {
		x = xT;
		y = yT;
		z = zT;

	}
	~Vector3<T>(){}

	T x;
	T y;
	T z;

	//operator overloads
	Vector3<T>& operator +(const Vector3<T>& a) {
		return Vector3<T>(x+a.x,
						  y+a.y,
						  z+a.z);
	}

	void operator +=(const Vector3<T>& a) {
		x += a.x;
		y += a.y;
		z += a.z;
	}

	Vector3<T>& operator-(const Vector3<T>& s) {
		return Vector3<T>(x-s.x,
						  y-s.y,
						  z-s.z);
	}

	void operator -=(const Vector3<T>& s) {
		x -= s.x;
		y -= s.y;
		z -= s.z;
	}
	//void operator =(const Vector3<T>& s)

	//Multiply by a scalar
	Vector3<T>& operator *(const T m) {
		return Vector3<T>(x*m,
						  y*m,
						  z*m);
	}

	void operator *=(const T m) {
		x *= m;
		y *= m;
		z *= m;
	}

	//Vector Dot Operations will return a scalar value
	T operator *(const Vector3<T>& m) {
		return (x * m.x) +
		       (y * m.y) +
		       (z * m.z);
	}
	//T& operator *+(const Vector3<T>& m);

	//Vector Cross operation will return a Vector
	//Vector3<T>& X(const Vector3<T>& m) { }

	//Division by scalar
	Vector3<T>& operator /(const T d) {
		//if(d == 0) {return NULL;}

		return Vector3<T>(x / d,
						  y / d,
						  z / d);
	}

	void operator /=(const T d) {
		//if(d == 0) {return NULL;}

		x /= d;
		y /= d;
		z /= d;
	}

	T Magnitude() { return sqrt((x*x) + (y*y) + (z*z)); }

	Vector3<T>& Unit() { return Vector3<T>((x/Magnitude()), (y/Magnitude()), (z/Magnitude())); }

};

#endif
