/*========================================================================
The Particle represents a point mass that will be used in physics calcula-
tions. It is based on the Cyclone engine design found in "Game Physics En-
gine Development, second edition" by Ian Millington.



This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
========================================================================*/
#ifndef PARTICLE2D_H
#define PARTICLE2D_H

//=====KillerMath includes=====
#include <Engine/Timer.h>
#include <Engine/Atom.h>
#include <Engine/GameObject2D.h>

//=====STL and other includes=====
#include <cassert>

namespace KM = KillerMath;
namespace KE = KillerEngine;

namespace KillerPhysics 
{
	class Particle2D : public KE::GameObject2D
	{
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
		Particle2D(void);
	
		~Particle2D(void);

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
		real GetDamping(void) { return _damping; }

		void SetDamping(real damp) { _damping = damp; }

		real GetInverseMass(void) { return _inverseMass; }

		void SetInverseMass(real mass) { _inverseMass = ((real)1.0f) / mass; }

		real GetMass(void);

		void SetMass(const real mass);

		bool HasFiniteMass(void);


//==========================================================================================================================
//
//Particle functions
//
//==========================================================================================================================
		void Update(void);

		void ClearAccumulator(void);

		void AddForce(const Vec2& force);

	private:
		//=====Description=====
		//Used to simulate Newtons first law
		real _damping;

		//=====Description=====
		//Mass stored over 1 in order to take
		//advantage of the equation -> a = 1/m * f
		//which is a transformed version of -> f = m * a
		//where f is a force applied to the particle. 
		real _inverseMass;

		Vec2 _forceAccum;
	};
}//End namespace

#endif