/*========================================================================
The Particle represents a point mass that will be used in physics calcula-
tions. It is based on the Cyclone engine design found in "Game Physics En-
gine Development, second edition" by Ian Millington.

This is the 3D implementation. 

This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
========================================================================*/
#ifndef KILLER_ENGINE_H
#define KILLER_ENGINE_H
#pragma once

//=====Physics includes=====
#include <Engine/Atom.h>

//=====KillerMath includes=====
#include <Engine/Timer.h>

//=====STL and other includes=====
#include <cassert>

namespace KM = KillerMath;

namespace KillerPhysics 
{
	class Particle3D
	{
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
		Particle3D(void);
	
		~Particle3D(void);

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
		Vec3& GetPosition(void) { return position; }
		
		void  SetPosition(Vec3& pos) { position = pos; }

		Vec3& GetVelocity(void) { return velocity; }
		
		void  SetVelocity(Vec3& vel) { velocity = vel; }

		Vec3& GetAcceleration(void) { return acceleration; }

		void SetAcceleration(Vec3& acc) { acceleration = acc; }

		real GetDamping(void) { return damping; }

		void SetDamping(real damp) { damping = damp; }

		real GetInverseMass(void) { return damping; }

		void SetInverseMass(real mass) { inverseMass = mass; }

		real GetMass(void);

		void SetMass(const real mass);

//==========================================================================================================================
//
//Particle functions
//
//==========================================================================================================================
		void Update(void);

	protected:
		Vec3 position;
		Vec3 velocity;
		Vec3 acceleration;
		real damping;
		real inverseMass;

	private:
		KM::Timer* _timer;
	};
}//End namespace

#endif