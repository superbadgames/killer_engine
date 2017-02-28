/*========================================================================
Registry to find out which particles need forces. It keeps track of which
objects need specific forces for their development. 

It is based on the Cyclone engine design found in "Game Physics En-
gine Development, second edition" by Ian Millington.



This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
========================================================================*/
#ifndef P_FORCE_REGISTRY_2D_H
#define P_FORCE_REGISTRY_2D_H

//=====Engine includes=====
#include <Engine/Atom.h>
#include <Engine/Particle2DForceGenerator.h>

namespace KM = KillerMath;
namespace KE = KillerEngine;

//=====STL includes=====
#include <vector>

namespace KillerPhysics
{

	class Particle2DForceRegistry
	{
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================		
		Particle2DForceRegistry(void);

		~Particle2DForceRegistry(void);

//==========================================================================================================================
//
//ParticleForceRegistry functions
//
//==========================================================================================================================		
		void Add(Particle2D* particle, Particle2DForceGenerator* forceGen);

		void Remove(Particle2D* particle, Particle2DForceGenerator* forceGen);

		void Clear(void);

		void UpdateForces(void);
		
	private:
//==========================================================================================================================
//This struct will keep track of one force generator, and the particle that uses it. 
//==========================================================================================================================		
		struct ParticleForceRegistration
		{
			Particle2D* 			  particle;
			Particle2DForceGenerator* forceGen;

			ParticleForceRegistration(void) {  }

			bool operator ==(ParticleForceRegistration p)
			{
				if(p.particle == particle && p.forceGen == forceGen)
					return true;
				else
					return false;
			}			
		};//end struct

		typedef std::vector<ParticleForceRegistration> Registry;
		Registry _registrations;
	};//end class
}//end namespace

#endif