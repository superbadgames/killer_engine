/*========================================================================
Using the basic idea of a spring, this force with simulate buoyancy using
the density of liquid combined with the mass of an object and the depth 
of its submersion to determine a buoyant force of up or none.

When d <= 0, the force is 0
When d >= 1, the force is v * p
Otherwise, the force is d * v * p

Where d is the amount of the object that is submerged (1 meaning when 
fully submerged, and 0 when completely out of the liquid), v is the volume
of the object, and p is the density of the liquid.

Usage:

The force generator cannot be re-used. For each unique spring-like force
we need to have its own Spring like force. Each spring-like force is 
created with a pointer to the object at the other end of the spring, the
length of the spring, and the spring constant. This then must be registered
with a ParticleForceRegistry*. 

This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
========================================================================*/
#ifndef BUOYANT_H
#define BUOYANT_H

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/Particle2DForceGenerator.h>

namespace KillerPhysics
{
	class Particle2DBuoyantForce : public Particle2DForceGenerator
	{
	public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
		Particle2DBuoyantForce(void);

		Particle2DBuoyantForce::Particle2DBuoyantForce(real maxDepth, real objVolume, real liquidHeight);

		Particle2DBuoyantForce(real maxDepth, real objVolume, real liquidHeight, real liquidDensity);

		~Particle2DBuoyantForce(void);
//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
		void v_UpdateForce(Particle2D* particle);

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
		void SetMaxDepth(real depth) { _maxDepth = depth; }

		void SetObjectVolume(real volume) { _objectVolume = volume; }

		void SetLiquidHeight(real hieght) { _liquidHeight = hieght; }

		void SetLiquidDensity(real density) { _liquidDensity = density; }
	
	private:
		real _maxDepth;
		real _objectVolume;
		real _liquidHeight;
		real _liquidDensity;
		
	};//end Class
}//end Namespace
#endif