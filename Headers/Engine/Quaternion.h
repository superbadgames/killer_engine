/*========================================================================
Quaternions will handle the rotational math that the engine will use. This
class is the holder of these functions. 

This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
========================================================================*/
#ifndef QUATERNION_H
#define QUATERNION_H

//=====Engine Includes=====
#include <Engine/Atom.h>

#include <assert.h>

namespace KillerMath
{
	class Quaternion
	{
	public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
		Quaternion(void);
		
		Quaternion(real value);

		Quaternion(real w, real x, real y, real z);

		Quaternion(const Quaternion& Q);

		~Quaternion(void);
		
//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
//==========================================================================================================================
//Accessors
//==========================================================================================================================		
		real GetW(void) const
		{
			return _q[0];
		}

		real GetX(void) const
		{
			return _q[1];
		}

		real GetY(void) const
		{
			return _q[2];
		}

		real GetZ(void) const
		{
			return _q[3];
		}

		const real* GetElems(void) const
		{
			return _q;
		}
//==========================================================================================================================
//
//Operators
//
//==========================================================================================================================
		Quaternion operator/ (real d);

		Quaternion& operator/= (real d);

		Quaternion operator* (real m);

		Quaternion operator* (Quaternion q2);

		Quaternion& operator*= (real m);

		Quaternion& operator*= (Quaternion q2);

//==========================================================================================================================
//
//Quaternion Functions
//
//==========================================================================================================================
		real Magnitude(void);

		Quaternion Conjugate(void);

		Quaternion Inverse(void);

		Quaternion Difference(Quaternion Q);
		

	private:
		real _q[4];
	};//end Class
}//end Namespace
#endif