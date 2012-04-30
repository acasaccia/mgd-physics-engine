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
#include "Triangle.h"

namespace PhysicsEngine
{
	class Terrain : public RigidBody
	{
	public:
		matrixN mVertexes;
		real mSquareSize;
		real mMaxHeight;
		real mFieldSize;
		unsigned int mSquaresNumber;

		//! Creates a new HeightMap
		//! \param iSize number of Squares for this square heightMap
		//! \param iSquareSize dimension of a square of the matrix in the simulation world
		//! \param iMaxHeight height of 3D point will be a random between 0 and iMaxHeight
		//! \return void
		Terrain( const unsigned int iSize, const real iSquareSize, const real iHeight);

		//! Specifies this class type to implement polymorphic behaviour in Collisor
		//! \return int one of the types listed in RigidBody.h
		int getType();

		//! Returns the 3D position of a heightmap point
		real* getVertexPosition(const int row, const int column, real* const iPosition) const;

		//! Returns the 3D position of a heightmap point
		Triangle* getSquareTessellation(const int row, const int column, Triangle* const tessellation) const;

		//! Returns a pair: first element is the number of neighbour triangles (could vary on edges)
		//! second element is an array of pointer to triangles
		//! \param r row number in the heightmap matrix
		//! \param c column number in the heightmap matrix
		//! \return std::pair<int,Triangle*>
		std::pair<int,Triangle*> getTrianglesAroundVertex( const int, const int, Triangle* neighboursTriangle );
	};

}