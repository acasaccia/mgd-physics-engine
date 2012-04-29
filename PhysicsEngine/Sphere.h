/*! 
 *  A physical sphere identified by a radius
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

	class Sphere : public RigidBody
	{
	public:
		//! Creates a new sphere
		//! \param iRadius radius of the sphere for collision detection
		//! \return void
		Sphere( const real iRadius );
		
		//! Specifies this class type to implement polymorphic behaviour in Collisor
		//! \return int one of the types listed in RigidBody.h
		int getType();

		real mRadius;
	};

}