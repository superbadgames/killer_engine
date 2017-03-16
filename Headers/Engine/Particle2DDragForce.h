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
#include <Engine/Particle2DForceGenerator.h>

namespace KM = KillerMath;
namespace KE = KillerEngine;

namespace KillerPhysics
{
	class Particle2DDragForce : public Particle2DForceGenerator
	{
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
		Particle2DDragForce(void);

		Particle2DDragForce(real k1, real k2);

		~Particle2DDragForce(void);

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