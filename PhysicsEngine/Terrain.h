/*! 
 *  A terrain identified by a matrix of height
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

	class Terrain : public RigidBody
	{
	public:
		matrixN mVertexes;
		float cellSize;

		//! Creates a new HeightMap
		//! \param iSize number of cells for this square heightMap
		//! \param iSquareSize dimension of a square of the matrix in the simulation world
		//! \return void
		Terrain( const int, const real, const real );
		int getType();
	};

}