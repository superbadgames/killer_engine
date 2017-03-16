#include <Engine/Particle2DSpringForce.h>

namespace KillerPhysics
{
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
	Particle2DSpringForce::Particle2DSpringForce(void) : _otherEnd(), _springConstant(1), _restLength(1), _isBungie(false)  
	{  }

	Particle2DSpringForce::Particle2DSpringForce(Particle2D* other, real constatant, real length) 
		: _otherEnd(other), _springConstant(constatant), _restLength(length), _isBungie(false)
	{  }

	Particle2DSpringForce::~Particle2DSpringForce(void) {  }

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
	void Particle2DSpringForce::v_UpdateForce(Particle2D* particle)
	{
//=====Calculate Vector of the spring=====
		Vec2 force = particle->GetPosition();
		force -= _otherEnd->GetPosition();

//=====Calculate magnitude of force=====
		real magnitude = force.Magnitude();

		//=====Bungie Checke=====
		if(magnitude <= _restLength) return;

		magnitude = fabsf(magnitude - _restLength) * _springConstant;

//=====Calculate final force=====
		force.Normalize();
		force *= -magnitude;

		particle->AddForce(force);
	}
}//end namespace