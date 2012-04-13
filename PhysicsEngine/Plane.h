/*! 
 *  A physical sphere with a radius, a mass, a position and a linear momentum
 *  -
 *  Implementation of a simple physics engine, Physics Programming course
 *  Master in Computer Game Developement, Verona, Italy
 *  -
 *  \author Andrea Casaccia
 *  \date 23 March 2012
 */

#pragma once

#include "LinearAlgebra.h"
#include "RigidBody.h"

namespace PhysicsEngine
{

	class Plane : public RigidBody
	{
	public:
		Plane( const vector3 iNormal, const real iDistance ) :
		  RigidBody(),
		  normal( iNormal ),
		  distance( iDistance )
		{}

	private:
		vector3 normal;
		real distance;
	};

}