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
		assert(d != 0);

		return Quaternion(_q[0] / d, _q[1] / d, _q[2] / d, _q[3] / d);
	}

	Quaternion& Quaternion::operator/= (real d)
	{
		assert(d != 0);

		_q[0] /= d;
		_q[1] /= d; 
		_q[2] /= d;
		_q[3] /= d; 

		return *this;
	}

	Quaternion Quaternion::operator* (real m)
	{
		return Quaternion(_q[0] *= m, _q[1] *= m, _q[2] *= m, _q[3] *= m);
	}

	Quaternion Quaternion::operator* (Quaternion q2)
	{
		real w2 = q2.GetW();
		real x2 = q2.GetX();
		real y2 = q2.GetY();
		real z2 = q2.GetZ();

		return Quaternion(_q[0] * w2 - _q[1] * x2 - _q[2] * y2 - _q[3] * z2,  //w
						  _q[0] * x2 + _q[1] * w2 + _q[2] * z2 - _q[3] * y2,  //x
						  _q[0] * y2 + _q[2] * w2 + _q[3] * x2 - _q[1] * z2,  //y
						  _q[0] * z2 + _q[3] * w2 + _q[1] * y2 - _q[2] * x2); //z
	}

	Quaternion& Quaternion::operator*= (real m)
	{
		_q[0] *= m;
		_q[1] *= m; 
		_q[2] *= m;
		_q[3] *= m; 

		return *this;
	}

	Quaternion& Quaternion::operator*= (Quaternion q2)
	{
		real w1 = _q[0];
		real x1 = _q[1];
		real y1 = _q[2];
		real z1 = _q[3];

		real w2 = q2.GetW();
		real x2 = q2.GetX();
		real y2 = q2.GetY();
		real z2 = q2.GetZ();

		_q[0] = w1 * w2 - x1 * x2 - y1 * y2 - z1 * z2;  //w
		_q[1] = w1 * x2 + x1 * w2 + y1 * z2 - z1 * y2;  //x
		_q[2] = w1 * y2 + y1 * w2 + z1 * x2 - x1 * z2;  //y
		_q[3] = w1 * z2 + z1 * w2 + x1 * y2 - y1 * x2;  //z

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