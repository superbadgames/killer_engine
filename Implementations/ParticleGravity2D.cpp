#include <Engine/ParticleGravity2D.h>

namespace KillerPhysics
{
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
	ParticleGravity2D::ParticleGravity2D(void) {  }

	ParticleGravity2D::ParticleGravity2D(const Vec2& gravity) : _gravityAcc(gravity) 
	{  }

	ParticleGravity2D::~ParticleGravity2D(void) {  }

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
	void ParticleGravity2D::v_UpdateForce(Particle2D& particle)
	{
		if(!particle.HasFiniteMass()) return;

		particle.AddForce(_gravityAcc * particle.GetMass());
	}
}//end namespace