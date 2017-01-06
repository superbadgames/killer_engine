#include <Engine/ParticleDrag2D.h>

namespace KillerPhysics
{
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
	ParticleDrag2D::ParticleDrag2D(void) {  }

	ParticleDrag2D::ParticleDrag2D(real k1, real k2) : _k1(k1), _k2(k2)
	{  }

	ParticleDrag2D::~ParticleDrag2D(void) {  }

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
	void ParticleDrag2D::v_UpdateForce(Particle2D& particle)
	{
		Vec2 force = particle.GetVelocity();

		real dragCoeff = force.Magnitude();
		dragCoeff = _k1 * dragCoeff  + _k2 * dragCoeff * dragCoeff;

		force.Normalize();
		force *= -dragCoeff;

		particle.AddForce(force);
	}
}//end namespace