#include <Engine/Particle2DBuoyantForce.h>

namespace KillerPhysics
{
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
	Particle2DBuoyantForce::Particle2DBuoyantForce(void) : _maxDepth(0), _objectVolume(0), _liquidHeight(0), _liquidDensity(1000.0f)
	{  }

	Particle2DBuoyantForce::Particle2DBuoyantForce(real maxDepth, real objVolume, real liquidHeight)
		: _maxDepth(maxDepth), _objectVolume(objVolume), _liquidHeight(liquidHeight), _liquidDensity(1000.0f)
	{  }

	Particle2DBuoyantForce::Particle2DBuoyantForce(real maxDepth, real objVolume, real liquidHeight, real liquidDensity)
		: _maxDepth(maxDepth), _objectVolume(objVolume), _liquidHeight(liquidHeight), _liquidDensity(liquidDensity)
	{  }

	Particle2DBuoyantForce::~Particle2DBuoyantForce(void) {  }

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
	void Particle2DBuoyantForce::v_UpdateForce(Particle2D* particle)
	{
//=====Calculate Depth of object=====
		real depth = particle->GetPosition().GetY();

		if(depth >= _liquidHeight + _maxDepth) return;
		
		Vec2 force(0.0f);

		if(depth <= _liquidHeight - _maxDepth)
		{
			force.SetY(_liquidDensity * _objectVolume);
			particle->AddForce(force);
			return;
		}

		force.SetY(_liquidDensity * _objectVolume * (depth - _maxDepth - _liquidHeight) / 2 * _maxDepth);

		particle->AddForce(force);	
	}
}//end namespace