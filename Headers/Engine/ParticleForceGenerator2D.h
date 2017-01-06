/*========================================================================
The ParticleForceGenerator2D provides the interface for forces to be generated 
and then accumulated by anything that uses forces for physics calculations.

It is based on the Cyclone engine design found in "Game Physics En-
gine Development, second edition" by Ian Millington.



This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
========================================================================*/
#ifndef P_FORCE_GENERATOR_2D_H
#define P_FORCE_GENERATOR_2D_H

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/Timer.h>
#include <Engine/Particle2D.h>

namespace KM = KillerMath;
namespace KE = KillerEngine;

namespace KillerPhysics
{
	class ParticleForceGenerator2D
	{
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
		ParticleForceGenerator2D(void) { }

		~ParticleForceGenerator2D(void) { }


//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================	
		virtual void v_UpdateForce(Particle2D& particle)=0;
	private:

	};//end class
}//end namespace

#endif