
#pragma once

#include "LinearAlgebra.h"
#include "Sphere.h"

namespace PhysicsEngine
{

	Sphere::Sphere( const real iRadius ) :
		RigidBody(),
		mRadius( iRadius )
	{}

	int Sphere::getType()
	{
		return RIGID_BODY_TYPE_SPHERE;
	}
}