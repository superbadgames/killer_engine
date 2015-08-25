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

#include <Engine/Atom.h>

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



	//Matrix4(Matrix4<T> M); Implement later


	//==========================================================================================================================
	//
	//Special functions
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
		_m[0] = 2 / (right - left);
		_m[5] = 2 / (top - bottom);
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
	const T* GetElems(void) const { return _m; }

	//==========================================================================================================================
	//
	//Operator Overloads
	//
	//==========================================================================================================================
//	Matrix& operator =(const Matrix* M) {

//	}
	//Matrix<T> operator *(Matrix<T> M);
	//Matrix<T>& operator *=(Matrix<T> M);
};

#endif
