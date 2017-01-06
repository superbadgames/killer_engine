#include <Engine/ParticleForceRegistry2D.h>

namespace KillerPhysics
{
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
	ParticleForceRegistry2D::ParticleForceRegistry2D(void)
	{  }

	ParticleForceRegistry2D::~ParticleForceRegistry2D(void)
	{  }

//==========================================================================================================================
//
//ParticleForceRegistry2D functions
//
//==========================================================================================================================	
	void ParticleForceRegistry2D::Add(Particle2D* particle, ParticleForceGenerator2D* forceGen)
	{
		ParticleForceRegistry2D::ParticleForceRegistration registration;
		registration.particle = particle;
		registration.forceGen = forceGen;

		_registrations.push_back(registration);
	}

	void ParticleForceRegistry2D::Remove(Particle2D* particle, ParticleForceGenerator2D* forceGen)
	{
		ParticleForceRegistry2D::ParticleForceRegistration registration;
		registration.particle = particle;
		registration.forceGen = forceGen;

		auto it = std::find(_registrations.begin(), _registrations.end(), registration);

		if(it != _registrations.end())
		{
			_registrations.erase(it);
		}
	}

	void ParticleForceRegistry2D::Clear(void)
	{
		_registrations.clear();
	}

	void ParticleForceRegistry2D::UpdateForces(void)
	{
		Registry::iterator i = _registrations.begin();
		for(; i != _registrations.end(); ++i)
		{
			i->forceGen->v_UpdateForce(*i->particle);
		}
	}
}//end namespace