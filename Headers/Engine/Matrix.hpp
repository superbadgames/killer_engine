/*=========================================================================
The Matrix is meant to be mathematically sound. The functions found here
have been tested and are built according to linear algebra rules. The 

Matrices will be column major to ahdere to the format used within opengl, 
and only 4x4 Matrices will be supported. This is because I cannot find any 
useful reason to suport a dynamic type at this time. In the future if other
Matrices appear to be useful, this class will basically be copied and will
be turned into whatever other type of Matrix is needed, be it a 3x3 or 2x2
or whatever. This class will only be a 4x4.

A typedef will be created in the Atom.h that will allow an object of this 
class to be created by just calling "matrix" as a class. 

Constructors: There are several ways to create a Matrix with this class.

matrix(single value) will create a identiy matrix of said value. 

maxtrix(16 values) will create a matrix as intended. It can take an array
or the values themselves. 

For the construction of the orthographic or persepctive matricies, there
is a funcion that you call to return the specified matrix. 

Matrix::Orthographic(width, height, depth)

Matrix::Perspective(width, height, depth)

Features to add later:

Perspective is planned, not to be implemenated until later. 

Multiplication by Matrix. This needs to be check. 

Multiplication by Vector (one column matrix). This will be added later in 
the name of pragmatism. 

Transpose. This may be useful later, but now so much now. 

This is not free to use, and cannot be used without the express permission
of KillerWave or Layer8, or whatever I am called now.

Written by Maxwell Miller
=========================================================================*/
#ifndef MATRIX_H
#define MATRIX_H

//=====Killer1 includes=====
#include <Engine/Atom.h>
#include <Engine/Vector.hpp>

namespace KillerMath {

	template<typename T>
	class Matrix4 {
	private:
		T _m[16];

	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
		Matrix4(void) {
			_m[0]  = _m[1]  = _m[2]  = _m[3]  = 0;
			_m[4]  = _m[5]  = _m[6]  = _m[7]  = 0;
			_m[8]  = _m[9]  = _m[10] = _m[11] = 0;
			_m[12] = _m[13] = _m[14] = _m[15] = 0;
		}
		
		Matrix4(T val) {
			_m[0] = _m[5] = _m[10] = _m[15] = val;
		
			_m[1]  = _m[2]  = _m[3]  = 0;
			_m[4]  = _m[6]  = _m[7]  = 0; 
			_m[8]  = _m[9]  = _m[11] = 0;
			_m[12] = _m[13] = _m[14] = 0;
		}
		
		Matrix4(const T mSrc[16]) {
			_m[0]  = mSrc[0];  _m[1] = mSrc[1];   _m[2]  = mSrc[2];  _m[3]  = mSrc[3];
			_m[4]  = mSrc[4];  _m[5] = mSrc[5];   _m[6]  = mSrc[6];  _m[7]  = mSrc[7];
			_m[8]  = mSrc[8];  _m[9] = mSrc[9];   _m[10] = mSrc[10]; _m[11] = mSrc[11];
			_m[12] = mSrc[12]; _m[13] = mSrc[13]; _m[14] = mSrc[14]; _m[15] = mSrc[15];
		}
		
		Matrix4( T m00, T m01, T m02, T m03,
				 T m10, T m11, T m12, T m13,
				 T m20, T m21, T m22, T m23,
				 T m30, T m31, T m32, T m33)
		{
			_m[0]  = m00;  _m[1] = m01;   _m[2]  = m02;  _m[3]  = m03;
			
			_m[4]  = m10;  _m[5] = m11;   _m[6]  = m12;  _m[7]  = m13;
			
			_m[8]  = m20;  _m[9] = m21;   _m[10] = m22; _m[11]  = m23;
			
			_m[12] = m30; _m[13] = m31;   _m[14] = m32; _m[15]  = m33;
		}


/*
	Work to fix this later, replace the default copy constructor.
		Matrix4(Matrix4<T> M) {
			T* m = M.GetElems();

			_m[0]  = m[0];  _m[1]  = m[1];   _m[2]   = m[2];  _m[3]   = m[3];
			
			_m[4]  = m[4];  _m[5]  = m[5];   _m[6]   = m[6];  _m[7]   = m[7];
			
			_m[8]  = m[8];  _m[9]  = m[9];   _m[10]  = m[10]; _m[11]  = m[11];
			
			_m[12] = m[12]; _m[13] = m[13];   _m[14] = m[14]; _m[15]  = m[15];
		}
*/

//==========================================================================================================================
//
//Matrix functions
//
//==========================================================================================================================
		void MakeOrthographic(T width, T height, T depth) {
		  	T right  = width   / 2;
		  	T left   = -width  / 2;
			T top    = height  / 2;
			T bottom = -height / 2;
			T far    = depth   / 2;
			T near   = -depth  / 2;

		  	//Reset Matrix
			_m[0]  =  _m[1]  =  _m[2]  =  _m[3]  = 0;

			_m[4]  =  _m[5]  =  _m[6]  =  _m[7]  = 0;

			_m[8]  =  _m[9]  =  _m[10] =  _m[11] = 0;

			_m[12] =  _m[13] =  _m[14] =  _m[15] = 0;

			//Diagnal
			_m[0]  = 2 / (right - left);
			_m[5]  = 2 / (top - bottom);
			_m[10] = 2 / (near - far);
			_m[15] = 1;

			//Transform "Vector"
			_m[12] = (left + right) / (left - right);
			_m[13] = (bottom + top) / (bottom - top);
			_m[14] = (near + far)   / (far - near);

		}

//==========================================================================================================================
//
//Accessor
//
//==========================================================================================================================
//=====Return the array containing all the elements=====
		const T* GetElems(void) const { return _m; }

//=====Return each element===== 
		T Get11(void) const { return _m[0];  }
		
		T Get12(void) const { return _m[1];  }
		
		T Get13(void) const { return _m[2];  }
		
		T Get14(void) const { return _m[3];  }

		T Get21(void) const { return _m[4];  }
		
		T Get22(void) const { return _m[5];  }
		
		T Get23(void) const { return _m[6];  }
		
		T Get24(void) const { return _m[7];  }

		T Get31(void) const { return _m[8];  }
		
		T Get32(void) const { return _m[9];  }
		
		T Get33(void) const { return _m[10]; }
		
		T Get34(void) const { return _m[11]; }

		T Get41(void) const { return _m[12]; }
		
		T Get42(void) const { return _m[13]; }
		
		T Get43(void) const { return _m[14]; }
		
		T Get44(void) const { return _m[15]; }

//==========================================================================================================================
//
//Operator Overloads
//
//==========================================================================================================================
		Matrix4<T>& operator=(const Matrix4<T>& M) {
			const T* elems = M.GetElems();

			_m[0] = elems[0];
			_m[1] = elems[1];
			_m[2] = elems[2];
			_m[3] = elems[3];

			_m[4] = elems[4];
			_m[5] = elems[5];
			_m[6] = elems[6];
			_m[7] = elems[7];


			_m[8]  = elems[8];
			_m[9]  = elems[9];
			_m[10] = elems[10];
			_m[11] = elems[11];

			_m[12] = elems[12];
			_m[13] = elems[13];
			_m[14] = elems[14];
			_m[15] = elems[15];

			return *this;
		}
		
		Matrix4<T> operator*(const Matrix4<T>& RHM) {
			const T* lhm = this->GetElems();
			const T* rhm = RHM.GetElems();

			return Matrix4<T>
			(
				lhm[0] * rhm[0] + lhm[1] * rhm[4] + lhm[2] * rhm[8]  + lhm[3] * rhm[12], //m11
				lhm[0] * rhm[1] + lhm[1] * rhm[5] + lhm[2] * rhm[9]  + lhm[3] * rhm[13], //m12
				lhm[0] * rhm[2] + lhm[1] * rhm[6] + lhm[2] * rhm[10] + lhm[3] * rhm[14], //m13
				lhm[0] * rhm[3] + lhm[1] * rhm[7] + lhm[2] * rhm[11] + lhm[3] * rhm[15], //m14

				lhm[4] * rhm[0] + lhm[5] * rhm[4] + lhm[6] * rhm[8]  + lhm[7] * rhm[12], //m21
				lhm[4] * rhm[1] + lhm[5] * rhm[5] + lhm[6] * rhm[9]  + lhm[7] * rhm[13], //m22
				lhm[4] * rhm[2] + lhm[5] * rhm[6] + lhm[6] * rhm[10] + lhm[7] * rhm[14], //m23
				lhm[4] * rhm[3] + lhm[5] * rhm[7] + lhm[6] * rhm[11] + lhm[7] * rhm[15], //m24

				lhm[8] * rhm[0] + lhm[9] * rhm[4] + lhm[10] * rhm[8]  + lhm[11] * rhm[12], //m31
				lhm[8] * rhm[1] + lhm[9] * rhm[5] + lhm[10] * rhm[9]  + lhm[11] * rhm[13], //m32
				lhm[8] * rhm[2] + lhm[9] * rhm[6] + lhm[10] * rhm[10] + lhm[11] * rhm[14], //m33
				lhm[8] * rhm[3] + lhm[9] * rhm[7] + lhm[10] * rhm[11] + lhm[11] * rhm[15], //m34

				lhm[12] * rhm[0] + lhm[13] * rhm[4] + lhm[14] * rhm[8]  + lhm[15] * rhm[12], //m41
				lhm[12] * rhm[1] + lhm[13] * rhm[5] + lhm[14] * rhm[9]  + lhm[15] * rhm[13], //m42
				lhm[12] * rhm[2] + lhm[13] * rhm[6] + lhm[14] * rhm[10] + lhm[15] * rhm[14], //m43
				lhm[12] * rhm[3] + lhm[13] * rhm[7] + lhm[14] * rhm[11] + lhm[15] * rhm[15]  //m44
			);
		}
		
		Matrix4<T>& operator *=(Matrix4<T>& RHM) {
			*this = *this * RHM;
			return *this;
		}

		Vector2<T>& operator *(const Vector2<T>& RHV)
		{
			return Vector2<T>
			(
				RHV.GetX() * _m[0] + RHV.GetY() * _m[1],
				RHV.GetX() * _m[4] + RHV.GetY() * _m[5]
			);
		}

		Vector3<T>& operator *(const Vector3<T>& RHV)
		{
			return Vector3<T>
			(
				RHV.GetX() * _m[0] + RHV.GetY() * _m[1] + RHV.GetZ() * _m[2],
				RHV.GetX() * _m[4] + RHV.GetY() * _m[5] + RHV.GetZ() * _m[6]
			);
		}
	};

}//End namespace

#endif
