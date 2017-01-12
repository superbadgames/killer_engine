/*========================================================================
A Particle force for 2D particles which simulates Gravity. In this case, 
down is going to be -y. 

It is based on the Cyclone engine design found in "Game Physics En-
gine Development, second edition" by Ian Millington.



This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
========================================================================*/
#ifndef GRAVITY_2D_H
#define GRAVITY_2D_H

//=====Engine includes=====
#include <Engine/Atom.h>
#include <Engine/ParticleForceGenerator2D.h>

namespace KM = KillerMath;
namespace KE = KillerEngine;

namespace KillerPhysics
{
	class ParticleGravity2D : public ParticleForceGenerator2D
	{
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================		
		ParticleGravity2D(void);

		ParticleGravity2D(const Vec2& gravity);

		~ParticleGravity2D(void);

//==========================================================================================================================
//
//Virtual functions
//
//==========================================================================================================================		
		void v_UpdateForce(Particle2D& particle);

	private:
		Vec2 _gravityAcc;
	};//end class
}//end namespace

#endif