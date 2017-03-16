#include <Engine/Particle2DForceRegistry.h>

namespace KillerPhysics
{
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
	Particle2DForceRegistry::Particle2DForceRegistry(void)
	{  }

	Particle2DForceRegistry::~Particle2DForceRegistry(void)
	{  }

//==========================================================================================================================
//
//Particle2DForceRegistry functions
//
//==========================================================================================================================	
	void Particle2DForceRegistry::Add(Particle2D* particle, Particle2DForceGenerator* forceGen)
	{
		Particle2DForceRegistry::ParticleForceRegistration registration;
		registration.particle = particle;
		registration.forceGen = forceGen;

		_registrations.push_back(registration);
	}

	void Particle2DForceRegistry::Remove(Particle2D* particle, Particle2DForceGenerator* forceGen)
	{
		Particle2DForceRegistry::ParticleForceRegistration registration;
		registration.particle = particle;
		registration.forceGen = forceGen;

		auto it = std::find(_registrations.begin(), _registrations.end(), registration);

		if(it != _registrations.end())
		{
			_registrations.erase(it);
		}
	}

	void Particle2DForceRegistry::Clear(void)
	{
		_registrations.clear();
	}

	void Particle2DForceRegistry::UpdateForces(void)
	{
		Registry::iterator i = _registrations.begin();
		for(; i != _registrations.end(); ++i)
		{
			i->forceGen->v_UpdateForce(*i->particle);
		}
	}
}//end namespace