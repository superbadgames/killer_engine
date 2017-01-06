/*========================================================================
Particle Drag for 2D Particles. 

It is based on the Cyclone engine design found in "Game Physics En-
gine Development, second edition" by Ian Millington.



This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
========================================================================*/
#ifndef P_DRAG_2D_H
#define P_DRAG_2D_H

//=====Engine includes=====
#include <Engine/Atom.h>
#include <Engine/ParticleForceGenerator2D.h>

namespace KM = KillerMath;
namespace KE = KillerEngine;

namespace KillerPhysics
{
	class ParticleDrag2D : public ParticleForceGenerator2D
	{
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
		ParticleDrag2D(void);

		ParticleDrag2D(real k1, real k2);

		~ParticleDrag2D(void);

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================		
		void v_UpdateForce(Particle2D& particle);

	private:
		//Drag Coefficient
		real _k1;
		//Drag Coefficient Squared
		real _k2;
	};//end class
}//end namespace

#endif