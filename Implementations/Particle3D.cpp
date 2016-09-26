#include <Engine/Particle3D.h>

namespace KillerPhysics
{

//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================	
	Particle3D::Particle3D(void) : _timer(KM::Timer::Instance())
	{  }

	Particle3D::~Particle3D(void) {  }

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
	real Particle3D::GetMass(void)
	{
		if(inverseMass == 0) { return REAL_MAX; }
		
		else { return real(1.0) / inverseMass; }
	}

	void Particle3D::SetMass(const real mass)
	{
		assert(mass != 0);
		inverseMass = real(1.0) / mass;
	}

//==========================================================================================================================
//
//Particle Functions
//
//==========================================================================================================================
	void Particle3D::Update(void) 
	{
		//if there no mass, there is no update
		if(inverseMass == 0) return;

		F32 delta = _timer->DeltaTime();

		//Update position
		position.AddScaledVector(velocity, delta);

		Vec3 resultingAcc = acceleration;

		velocity.AddScaledVector(resultingAcc, delta);

		velocity *= real_pow(damping, delta);

		//=====clear force accumulator will go here when it is written=====
	}

}//end namespace