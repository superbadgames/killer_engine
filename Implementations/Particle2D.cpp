#include <Engine/Particle2D.h>

namespace KillerPhysics
{

//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================	
	Particle2D::Particle2D(void) : _damping(0.0f), _inverseMass(0.0f), _forceAccum()
	{  }

	Particle2D::~Particle2D(void) {  }

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
	real Particle2D::GetMass(void)
	{
		if(_inverseMass == 0) { return REAL_MAX; }
		
		else { return real(1.0) / _inverseMass; }
	}

	void Particle2D::SetMass(const real mass)
	{
		assert(mass != 0);
		_inverseMass = real(1.0) / mass;
	}

	bool Particle2D::HasFiniteMass(void)
	{
		return _inverseMass >= 0.0f;
	}

//==========================================================================================================================
//
//Particle Functions
//
//==========================================================================================================================
	void Particle2D::Update(void) 
	{
		//if there no mass, there is no update
		if(_inverseMass == 0) return;

		F32 delta = KM::Timer::Instance()->DeltaTime();

		Vec2 velocity = KE::GameObject2D::GetVelocity();
		
		//Update position
		KE::GameObject2D::SetScaledPosition(velocity, delta);

		Vec2 resultingAcc = KE::GameObject2D::GetAcceleration();

		velocity.AddScaledVector(resultingAcc, delta);

		velocity *= (F32)real_pow(_damping, delta);

		KE::GameObject2D::SetVelocity(velocity);

		ClearAccumulator();
	}

	void Particle2D::ClearAccumulator(void)
	{
		_forceAccum.Clear();
	}

	void Particle2D::AddForce(const Vec2& force)
	{
		_forceAccum += force;
	}

}//end namespace