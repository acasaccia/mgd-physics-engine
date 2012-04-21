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

	struct Triangle
	{
		real vertexes[3];
		Triangle();
		Triangle( real, real, real );
	};

	class Terrain : public RigidBody
	{
	public:
		matrixN mVertexes;
		real mCellSize;
		real mMaxHeight;
		int mCellsNumber;

		//! Creates a new HeightMap
		//! \param iSize number of cells for this square heightMap
		//! \param iSquareSize dimension of a square of the matrix in the simulation world
		//! \return void
		Terrain( const int, const real, const real );

		//! Specifies this class type to implement polymorphic behaviour in Collisor
		//! \return int
		int getType();

		//! Returns a pair: first element is the number of neighbour triangles (could vary on edges)
		//! second element is an array of pointer to triangles
		//! \param r row number in the heightmap matrix
		//! \param c column number in the heightmap matrix
		//! \return std::pair<int,Triangle*>
		std::pair<int,Triangle*> getNeighbourTriangles( const int, const int );
	};

}