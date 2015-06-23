/*========================================================================
A Vector class that will follow the rules of Mathematics. The equations 
that the Vectors use for each operation were taken from 3D Math Primer 
for Graphics and Game Development by Dunn and Parberry. 

It is called Vector because it will only support 3D vectors. For any 2D 
work, simply adapt by not using the z axis (although you should not that
there will be some operations that will not support this, such as the 
cross multiplication operation. 

w is a special value that is used for computations convience. It is there
so that the vector can be transformed by a 4x4 matrix. As such, it will 
not be changed in any of the operators. Maybe later there will be a reason
to actually change the value of w, but for now I don't see a good reason 
to add this functionality.

This is not free to use, and cannot be used without the express permission
of KillerWave. 

Written by Maxwell Miller
========================================================================*/

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <Atom.h>

template<typename T>
class Vector {
private:
	T _x;
	T _y;
	T _z;
	T _w;

public:
	Vector()				       : _x(T(0)), _y(T(0)), _z(T(0)), _w(T(1)) 			       	{  }
	Vector(T xT, T yT)			   : _x(xT), _y(yT), _z(T(0)), _w(T(1))							{  }
	Vector(T xT, T yT, T zT) 	   : _x(xT), _y(yT), _z(zT), _w(T(1))    						{  }
	Vector(T xT, T yT, T zT, T wT) : _x(xT), _y(yT), _z(zT), _w(wT) 							{  }
	Vector(const Vector<T>& vT)	   : _x(vT.GetX()), _y(vT.GetY()), _z(vT.GetZ()), _w(vT.GetW()) {  }
	
	~Vector<T>(){  }

//==================================================> Note, find out if OGL is column or row major, I always forget, and make it the same

//=====Accessors=====
	T GetX() const { return _x; }
	T GetY() const { return _y; }
	T GetZ() const { return _z; }
	T GetW() const { return _w; }
 
//=====operator overloads=====
	//copy assignment
	Vector<T>& operator =(const Vector<T>& v) {
		_x = v.GetX();
		_y = v.GetY();
		_z = v.GetX();
		_w = v.GetW();

		return *this;
	}

	//Add by vector
	Vector<T> operator +(const Vector<T>& a) {
		return Vector<T>(_x + a.GetX(),
						 _y + a.GetY(),
						 _z + a.GetZ(),
						 _w );
	}

	Vector<T>& operator +=(const Vector<T>& a) {
		_x += a.GetX();
		_y += a.GetY();
		_z += a.GetZ();

		return *this;
	}

	//Add by scalar
	Vector<T> operator +(const T& a) {
		return Vector<T>(_x + a,
						 _y + a,
						 _z + a,
						 _w );
	}

	Vector<T>& operator +=(const T& a) {
		_x += a;
		_y += a;
		_z += a;

		return *this;
	}

	//Minus from vector
	Vector<T> operator-(const Vector<T>& s) {
		return Vector<T>(_x - s.GetX(),
						 _y - s.GetY(),
						 _z - s.GetZ(),
						 _w );
	}

	Vector<T>& operator -=(const Vector<T>& s) {
		_x -= s.GetX();
		_y -= s.GetY();
		_z -= s.GetZ();

		return *this;
	}

	//Minus from scalar
	Vector<T> operator-(const T& s) {
		return Vector<T>(_x - s,
						 _y - s,
						 _z - s,
						 _w );
	}

	Vector<T>& operator -=(const T& s) {
		_x -= s;
		_y -= s;
		_z -= s;

		return *this;
	}

	//Multiply by a scalar
	Vector<T> operator *(const T m) {
		return Vector<T>(_x * m,
						 _y * m,
						 _z * m,
						 _w );
	}

	Vector<T>& operator *=(const T m) {
		_x *= m;
		_y *= m;
		_z *= m;
		
		return *this;
	}

	//Vector Dot Operations will return a scalar value
	T operator *(const Vector<T>& m) {
		return (_x * m.GetX()) +
		       (_y * m.GetY()) +
		       (_z * m.GetZ());
	}
	//T& operator *+(const Vector<T>& m);

	//Vector Cross operation will return a Vector
	Vector<T> Cross(const Vector<T>& m) { return Vector<T>((_y * m.GetZ() - _z * m.GetY()), 
														   (_z * m.GetX() - _x * m.GetZ()), 
														   (_x * m.GetY() - _y * m.GetX()),
														    _w ); 
    }

	//Division by scalar
	Vector<T> operator /(const T d) {
		if(d == 0) { return *this; }

		return Vector<T>(_x / d,
						 _y / d,
						 _z / d,
						 _w );
	}

	Vector<T>& operator /=(const T d) {
		if (d == 0) { 
			//do nothing  ----------------------Needs to make error for this in error system 
		}
		else {
			_x /= d;
			_y /= d;
			_z /= d;
		}
		return *this;
	}

	T Magnitude() { return sqrt((_x * _x) + (_y * _y) + (_z * _z)); }

	Vector<T> Unit() { return Vector<T>((_x / Magnitude()), 
										(_y / Magnitude()), 
										(_z / Magnitude()),
										 _w ); 
	}

};

#endif
