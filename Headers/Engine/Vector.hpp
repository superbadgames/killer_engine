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

#include <Engine/Atom.h>

namespace KillerMath 
{

//======================================================================================================================================================
//==========================================================================================================================
//
//Vector2
//
//A 2D vector that is meant to be used in 2D space. It has 4 components still, but this is for easy mulitplication with the matrix class. 
//In the operators, Z will never change. This is true for addition. subtraction, mulitplication and divition. When it comes to multiplication, 
//it is important to keep in mind how vector multiplication works. For the Dot and Cross product operations, Z is involved and can change, also
//in the maginitude it can change, and in unit, but this should be as expected. Z is also updated in the component multiplication update, as that
//seems more nature than ignoring it. 
//
//The most important thing to note is the +, +=, -, -= operations. 	
//
//==========================================================================================================================
//======================================================================================================================================================
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
			_v[2] = V.GetZ();
			_v[3] = V.GetW();

			return *this;
		}

		//=====Add by vector=====
		Vector2<T> operator +(const Vector2<T>& V) 
		{
			return Vector2<T>( _v[0] + V.GetX(),
							   _v[1] + V.GetY(),
							   _v[2], 
							   _v[3] );
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
							   _v[2], 
							   _v[3] );
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
			_v[2] = 0;
			
			return *this;
		}

		//=====Straight Multiply by Vector2=====
		Vector2<T>& operator *=(const Vector2<T> v)
		{
			_v[0] *= v.GetX();
			_v[1] *= v.GetY();
			_v[2] = 0;

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

		//=====Makes this vector Unit=====
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

		//=====AddScales Vector=====
		void AddScaledVector(const Vector2<T> V, T scale)
		{
			_v[0] += V.GetX() * scale;
			_v[1] += V.GetY() * scale;
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

//======================================================================================================================================================
//==========================================================================================================================
//
//Vector3
//
//A standard 3D vector that will act as expected. It is mostly a copy/paste of the Vector2 class, as this seemed more nature than using,
//inheritance, which I considered. This may change later on, as a better design may present itself, but I feel for right now have some
//duplicate code is accepable for both clarity and accuracy. As this is primiaryly a 2D engine that is being built, it is acceptable to
//have this little duplication. 
//
//==========================================================================================================================
//======================================================================================================================================================

	template<typename T>
	class Vector3 
	{
	private:
		T _v[4];

	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
		Vector3()
		{
			_v[0] = 0;
			_v[1] = 0;
			_v[2] = 0;
			_v[3] = 1;
		}
		
		Vector3(T x, T y)
		{
			_v[0] = x;
			_v[1] = y;
			_v[2] = 0;
			_v[3] = 1;
		}
		
		Vector3(T x, T y, T z)
		{
			_v[0] = x;
			_v[1] = y;
			_v[2] = z;
			_v[3] = 1;
		}
		
		Vector3(T x, T y, T z, T w)
		{
			_v[0] = x;
			_v[1] = y;
			_v[2] = z;
			_v[3] = w;
		}
		
		Vector3(const Vector3<T>& V)
		{
			_v[0] = V.GetX();
			_v[1] = V.GetY();
			_v[2] = V.GetZ();
			_v[3] = V.GetW();
		}
			
		~Vector3<T>() {	 }

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
		Vector3<T>& operator =(const Vector3<T>& V) 
		{
			_v[0] = V.GetX();
			_v[1] = V.GetY();
			_v[2] = V.GetX();
			_v[3] = V.GetW();

			return *this;
		}

		//=====Add by vector=====
		Vector3<T> operator +(const Vector3<T>& V) 
		{
			return Vector3<T>( _v[0] + V.GetX(),
							   _v[1] + V.GetY(),
							   _v[2] + V.GetZ(), 
							   _v[3] );
		}

		Vector3<T>& operator +=(const Vector3<T>& V) 
		{
			_v[0] += V.GetX();
			_v[1] += V.GetY();
			_v[2] += V.GetZ();

			return *this;
		}

		//=====Add by scalar=====
		Vector3<T> operator +(const T& a) 
		{
			return Vector3<T>( _v[0] + a,
							   _v[1] + a,
							   _v[2] + a, 
							   _v[3] );
		}

		Vector3<T>& operator +=(const T& a) 
		{
			_v[0] += a;
			_v[1] += a;
			_v[2] += a;

			return *this;
		}

		//=====Minus from vector=====
		Vector3<T> operator-(const Vector3<T>& V) 
		{
			return Vector3<T>( _v[0] - V.GetX(),
							   _v[1] - V.GetY(),
							   _v[2] - V.GetZ(), 
							   _v[3] );
		}

		Vector3<T>& operator -=(const Vector3<T>& V) 
		{
			_v[0] -= V.GetX();
			_v[1] -= V.GetY();
			_v[2] -= V.GetZ();

			return *this;
		}

		//=====Minus from scalar=====
		Vector3<T> operator-(const T& s) 
		{
			return Vector3<T>( _v[0] - s,
							   _v[1] - s,
							   _v[2] - s, 
							   _v[3] );
		}

		Vector3<T>& operator-=(const T& s) 
		{
			_v[0] -= s;
			_v[1] -= s;
			_v[2] -= s;
			
			return *this;
		}

		//=====Multiply by a scalar=====
		Vector3<T> operator*(const T m) 
		{
			return Vector3<T>( _v[0] * m,
							   _v[1] * m,
							   _v[2] * m, 
							   _v[3] );
		}

		Vector3<T>& operator *=(const T m) 
		{
			_v[0] *= m;
			_v[1] *= m;
			_v[2] *= m;
			
			return *this;
		}

		//=====Dot Product=====
		T DotProduct(const Vector3<T>& V) 
		{
			return _v[0] * V.GetX() +
			       _v[1] * V.GetY() +
			       _v[2] * V.GetZ();
		}

		T operator *(const Vector3<T>& V) { return DotProduct(V); } 

		//====Cross Product=====
		Vector3<T> CrossProduct(const Vector3<T>& V) 
		{ 
			return Vector3<T>( _v[1] * V.GetZ() - _v[2] * V.GetY(), 
							   _v[2] * V.GetX() - _v[0] * V.GetZ(), 
							   _v[0] * V.GetY() - _v[1] * V.GetX(),
							   _v[3] ); 
	    }

	    Vector3<T> operator%(const Vector3<T>& V) { return CrossProduct(V); }

	    Vector3<T>& operator%=(const Vector3<T>& V) 
	    {
	    	_v[1] *= V.GetZ() - _v[2] * V.GetY(); 
			_v[2] *= V.GetX() - _v[0] * V.GetZ(); 
			_v[0] *= V.GetY() - _v[1] * V.GetX();
			
			return *this;
	    }

		//=====Division by scalar=====
		Vector3<T> operator /(const T d) 
		{
			if(d == 0) { return *this; }

			return Vector3<T>( _v[0] / d,
							   _v[1] / d,
							   _v[2] / d, 
							   _v[3] );
		}

		Vector3<T>& operator /=(const T d) 
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
				_v[2] /= d;
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

			if(mag > 0) { (*this) *= 1 / mag; } 
		}

		void MakeOrthonormalBasis(const Vector3<T>& A, const Vector3<T>& B, const Vector3<T>& C) 
		{
			A.Normalize();

			C = A % B;

			if(C.SqrMagnitude() == 0.0) return; //Add error here

			C.Normalize();

			B = C % A;
		}
		
		//=====AddScales Vector=====
		void AddScaledVector(const Vector3<T> V, T scale)
		{
			_v[0] += V.GetX() * scale;
			_v[1] += V.GetY() * scale;
			_v[2] += V.GetZ() * scale;
		}

		//=====Component Mulitplication=====
		Vector3<T> ComponentProduct(const Vector3<T>& V) 
		{
			return Vector3<T>( _v[0] * V.GetX(),
							   _v[1] * V.GetY(),
							   _v[2] * V.GetZ(),
							   _v[3] );
		}

		void ComponentProductUpdate(const Vector3<T>& V) {
			_v[0] *= V.GetX();
			_v[1] *= V.GetY();
			_v[2] *= V.GetZ();
		}

	};

}//end namespace 	

#endif
