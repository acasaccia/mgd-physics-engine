
#pragma once

#include "LinearAlgebra.h"
#include "Sphere.h"
#include "Constants.h"

namespace PhysicsEngine
{

	Sphere::Sphere( const real iRadius ) :
		RigidBody(),
		radius( iRadius )
	{}

	int Sphere::getType()
	{
		return RIGID_BODY_TYPE_SPHERE;
	}
}