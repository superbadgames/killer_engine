#include <Engine/Particle2DGravityForce.h>

namespace KillerPhysics
{
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
	Particle2DGravityForce::Particle2DGravityForce(void) : _gravityAcc(Vec2(0.0f, 1.0f, 0.0f))
	{  }

	Particle2DGravityForce::Particle2DGravityForce(const Vec2& gravity) : _gravityAcc(gravity) 
	{  }

	Particle2DGravityForce::~Particle2DGravityForce(void) {  }

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
	void Particle2DGravityForce::v_UpdateForce(Particle2D& particle)
	{
		if(!particle.HasFiniteMass()) return;

		particle.AddForce(_gravityAcc * particle.GetMass());
	}
}//end namespace