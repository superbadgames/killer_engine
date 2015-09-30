/*========================================================================
A Vector class that will follow the rules of Mathematics. The equations 
that the Vectors use for each operation were taken from 3D Math Primer 
for Graphics and Game Development by Dunn and Parberry. 

There are two classes that are created in this file. They are the Vector2
and the Vector3. The difference is whether the z can be changed or not. In
a Vector2, once it is created the z will stay the same no matter what, where
in the Vector3, the z will change dynamically as expected. 

Both have 4 elements, but the difference is how the elements are allowed 
to be changed throughout the life of the object. 

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

#include <KillerMath/Atom.h>

namespace KillerMath 
{

	template<typename T>
	class Vector2 
	{
	private:
		T _v[4];

	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
		Vector2()
		{
			_v[0] = 0;
			_v[1] = 0;
			_v[2] = 0;
			_v[3] = 1;
		}
		
		Vector2(T x, T y)
		{
			_v[0] = x;
			_v[1] = y;
			_v[2] = 0;
			_v[3] = 1;
		}
		
		Vector2(T x, T y, T z)
		{
			_v[0] = x;
			_v[1] = y;
			_v[2] = z;
			_v[3] = 1;
		}
		
		Vector2(T x, T y, T z, T w)
		{
			_v[0] = x;
			_v[1] = y;
			_v[2] = z;
			_v[3] = w;
		}
		
		Vector2(const Vector2<T>& V)
		{
			_v[0] = V.GetX();
			_v[1] = V.GetY();
			_v[2] = V.GetZ();
			_v[3] = V.GetW();
		}
			
		~Vector2<T>() {	 }

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
		T GetX() const { return _v[0]; }
		
		T GetY() const { return _v[1]; }
		
		T GetZ() const { return _v[2]; }
		
		T GetW() const { return _v[3]; }
	 
//==========================================================================================================================
//
//Operator Overloads
//
//==========================================================================================================================
		//=====Copy assignment=====
		Vector2<T>& operator =(const Vector2<T>& V) 
		{
			_v[0] = V.GetX();
			_v[1] = V.GetY();
			_v[2] = V.GetX();
			_v[3] = V.GetW();

			return *this;
		}

		//=====Add by vector=====
		Vector2<T> operator +(const Vector2<T>& V) 
		{
			return Vector2<T>( _v[0] + V.GetX(),
							   _v[1] + V.GetY(),
							   _v[2], _v[3] );
		}

		Vector2<T>& operator +=(const Vector2<T>& V) 
		{
			_v[0] += V.GetX();
			_v[1] += V.GetY();

			return *this;
		}

		//=====Add by scalar=====
		Vector2<T> operator +(const T& a) 
		{
			return Vector2<T>( _v[0] + a,
							   _v[1] + a,
							   _v[2], _v[3] );
		}

		Vector2<T>& operator +=(const T& a) 
		{
			_v[0] += a;
			_v[1] += a;

			return *this;
		}

		//=====Minus from vector=====
		Vector2<T> operator-(const Vector2<T>& V) 
		{
			return Vector2<T>( _v[0] - V.GetX(),
							   _v[1] - V.GetY(),
							   _v[2], _v[3] );
		}

		Vector2<T>& operator -=(const Vector2<T>& V) 
		{
			_v[0] -= V.GetX();
			_v[1] -= V.GetY();

			return *this;
		}

		//=====Minus from scalar=====
		Vector2<T> operator-(const T& s) 
		{
			return Vector2<T>( _v[0] - s,
							   _v[1] - s,
							   _v[2], _v[3] );
		}

		Vector2<T>& operator-=(const T& s) 
		{
			_v[0] -= s;
			_v[1] -= s;
			
			return *this;
		}

		//=====Multiply by a scalar=====
		Vector2<T> operator*(const T m) 
		{
			return Vector2<T>( _v[0] * m,
							   _v[1] * m,
							   _v[2], _v[3] );
		}

		Vector2<T>& operator *=(const T m) 
		{
			_v[0] *= m;
			_v[1] *= m;
			
			return *this;
		}

		//=====Dot Product=====
		T DotProduct(const Vector2<T>& V) 
		{
			return _v[0] * V.GetX() +
			       _v[1] * V.GetY() +
			       _v[2] * V.GetZ();
		}

		T operator *(const Vector2<T>& V) { return DotProduct(V); } 

		//====Cross Product=====
		Vector2<T> CrossProduct(const Vector2<T>& V) 
		{ 
			return Vector2<T>( _v[1] * V.GetZ() - _v[2] * V.GetY(), 
							   _v[2] * V.GetX() - _v[0] * V.GetZ(), 
							   _v[0] * V.GetY() - _v[1] * V.GetX(),
							   _v[3] ); 
	    }

	    Vector2<T> operator%(const Vector2<T>& V) { return CrossProduct(V); }

	    Vector2<T>& operator%=(const Vector2<T>& V) 
	    {
	    	_v[1] *= V.GetZ() - _v[2] * V.GetY(); 
			_v[2] *= V.GetX() - _v[0] * V.GetZ(); 
			_v[0] *= V.GetY() - _v[1] * V.GetX();
			
			return *this;
	    }

		//=====Division by scalar=====
		Vector2<T> operator /(const T d) 
		{
			if(d == 0) { return *this; }

			return Vector2<T>(_v[0] / d,
							 _v[1] / d,
							 _v[2], _v[3] );
		}

		Vector2<T>& operator /=(const T d) 
		{
			if (d == 0) 
			{ 
				//do nothing  ----------------------Needs to make error for this in error system 
				return *this;
			}
			
			else 
			{
				_v[0] /= d;
				_v[1] /= d;
			}

			return *this;
		}

//==========================================================================================================================
//
//Vector Functions
//
//==========================================================================================================================
		T Magnitude(void) { return sqrt(_v[0]*_v[0] + _v[1]*_v[1] + _v[2]*_v[2]); }
		
		T SqrMagnitude(void) { return _v[0]*_v[0] + _v[1]*_v[1] + _v[2]*_v[2]; }

		void Normalize(void) 
		{
			T mag = Magnitude();

			if(mag > 0) { (*this) *= T(1)/mag; } 
		}

		void MakeOrthonormalBasis(const Vector2<T>& A, const Vector2<T>& B, const Vector2<T>& C) 
		{
			A.Normalize();

			C = A % B;

			if(C.SqrMagnitude() == 0.0) return; //Add error here

			C.Normalize();

			B = C % A;
		}
		
		//=====Component Mulitplication=====
		Vector2<T> ComponentProduct(const Vector2<T>& V) 
		{
			return Vector2<T>( _v[0] * V.GetX(),
							  _v[1] * V.GetY(),
							  _v[2] * V.GetZ(),
							  _v[3] );
		}

		void ComponentProductUpdate(const Vector2<T>& V) {
			_v[0] *= V.GetX();
			_v[1] *= V.GetY();
			_v[2] *= V.GetZ();
		}

	};

}//end namespace 	

#endif
