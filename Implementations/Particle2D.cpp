#include <Engine/Particle2D.h>

namespace KillerPhysics
{

//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================	
	Particle2D::Particle2D(void) {  }

	Particle2D::~Particle2D(void) {  }

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
	real Particle2D::GetMass(void)
	{
		if(inverseMass == 0) { return REAL_MAX; }
		
		else { return real(1.0) / inverseMass; }
	}

	void Particle2D::SetMass(const real mass)
	{
		assert(mass != 0);
		inverseMass = real(1.0) / mass;
	}

//==========================================================================================================================
//
//Particle Functions
//
//==========================================================================================================================
	void Particle2D::Update(void) 
	{
		//if there no mass, there is no update
		if(inverseMass == 0) return;

		F32 delta = KM::Timer::Instance()->DeltaTime();

		//Update position
		KE::GameObject2D::position.AddScaledVector(velocity, delta);

		Vec2 resultingAcc = KE::GameObject2D::acceleration;

		KE::GameObject2D::velocity.AddScaledVector(resultingAcc, delta);

		KE::GameObject2D::velocity *= (F32)real_pow(damping, delta);

		//=====clear force accumulator will go here when it is written=====
	}

}//end namespace