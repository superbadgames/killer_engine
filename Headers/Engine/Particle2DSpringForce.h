/*========================================================================
A force that can generate spring-like behaviors. The basic model is based
on the information found in Game Physics Engine Development 2nd edition, 

It uses Hooks law to generate the amount of force based on the distance
that the spring is extended. 

The base equation is:

f = -k * delta * l

Where delta is the distance that the spring has been moved and k is what is
known as the "spring constant", a value that represents the "stiffness" of 
the spring. For our terms, the equation will look like this:

f = -k(l - l^0)

Where l is the location of the end of the spring, and l^0 is the reseting 
position of the spring.

Since this is a vector force, the vector version of the law looks like this:

f = -l(|d| - l^0)^d

Where |d| is the magnitude or length of d, which is distance away from l^0
our spring now is, and ^d is a unit vector version of d. Also:

d = xA - xB

Where xA is the position of the spring attached to our object, and xB is 
the end of the spring. 

Usage:

The force generator cannot be re-used. For each unique spring-like force
we need to have its own Spring like force. Each spring-like force is 
created with a pointer to the object at the other end of the spring, the
length of the spring, and the spring constant. This then must be registered
with a ParticleForceRegistry*. 

To set an Anchored Spring Force Generator, simple give it an object that cannot
be moved. This can be enforced in the GameObject using physics or something. 
May need to be figured out later. 

This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
========================================================================*/
#ifndef SPRING2D_H
#define SPRING2D_H

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/Particle2DForceGenerator.h>

namespace KillerPhysics
{
	class Particle2DSpringForce : public Particle2DForceGenerator
	{
	public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
		Particle2DSpringForce(void);

		Particle2DSpringForce(Particle2D* other, real constant, real length);

		~Particle2DSpringForce(void);
//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
		void v_UpdateForce(Particle2D* particle);

//==========================================================================================================================
//
//Class Functions
//
//==========================================================================================================================		
		void MakeBungie(bool state) { _isBungie = state; }

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================		
		void SetOtherEnd(Particle2D* end) { _otherEnd = end; }

		void SetSpringConstant(real constant) { _springConstant = constant; }

		void SetRestLength(real length) { _restLength = length; }
	
	private:
		//Consider using a GameObject2D here instead of a Particle2D
		//This would allow for it to be more generic, and to be used
		//With any kind of object that is rendered in the Map.
		Particle2D* _otherEnd;
		real 		_springConstant;
		real 		_restLength;
		bool		_isBungie;
		
	};//end Class
}//end Namespace
#endif