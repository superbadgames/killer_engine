#include <Engine/Quaternion.h>

namespace KillerMath
{
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
	Quaternion::Quaternion(void)
	{
		_q[0] = _q[1] = _q[2] = _q[3] = 0; 
	}

	Quaternion::Quaternion(real value)
	{
		_q[0] = _q[1] = _q[2] = _q[3] = value; 	
	}

	Quaternion::Quaternion(real w, real x, real y, real z)
	{
		_q[0] = w;

		_q[1] = x; 

		_q[2] = y; 

		_q[3] = z; 
	}

	Quaternion::Quaternion(const Quaternion& Q)
	{
		_q[0] = Q.GetW();

		_q[1] = Q.GetX();

		_q[2] = Q.GetY();

		_q[3] = Q.GetZ();
	}

	Quaternion::~Quaternion(void)
	{  }
//==========================================================================================================================
//
//Opperators
//
//==========================================================================================================================
	Quaternion Quaternion::operator/ (real d)
	{
		return Quaternion(_q[0] / d, _q[1] / d, _q[2] / d, _q[3] / d);
	}

	Quaternion& Quaternion::operator/= (real d)
	{
		_q[0] /= d;
		_q[1] /= d; 
		_q[2] /= d;
		_q[3] /= d; 

		return *this;
	}

	Quaternion Quaternion::operator* (real m)
	{
		return *this;
	}

	Quaternion& Quaternion::operator*= (real m)
	{
		return *this;
	}

//==========================================================================================================================
//
//Quaternion Functions
//
//==========================================================================================================================	
	real Quaternion::Magnitude(void)
	{
		return sqrt(_q[0] * _q[0] + _q[1] * _q[1] + _q[2] * _q[2] + _q[3] * _q[3]);
	}

	Quaternion Quaternion::Conjugate(void)
	{
		Quaternion Q{_q[0], _q[1] * -1.0f, _q[2] * -1.0f, _q[3] * -1.0f};

		return Q;
	}

	Quaternion Quaternion::Inverse(void)
	{
		Quaternion conjugate = Conjugate();
		real mag = Magnitude();

		return conjugate / mag;
	}


}//end namespace