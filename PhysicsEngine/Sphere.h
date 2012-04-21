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
		//! \param iSize number of cells for this square heightMap
		//! \param iSquareSize dimension of a square of the matrix in the simulation world
		//! \return void
		Sphere( const real iRadius );
		
		//! Specifies this class type to implement polymorphic behaviour in Collisor
		//! \return int
		int getType();
		real mRadius;
	};

}