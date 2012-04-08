/*! 
 *  A mesh which structure is identified by a matrix of height
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

	class HeightMap : public RigidBody
	{
	public:
		//! Creates a new HeightMap
		//! \param iVertexes matrix with height map data
		//! \param iPosition position where the center of the mesh will be placed
		//! \param iSquareSize dimension of a square of the matrix in the simulation world
		//! \return void
		HeightMap( Eigen::MatrixXi iVertexes, const Eigen::Vector3f iPosition, const float iSquareSize ) :
		  vertexes( iVertexes ),
		  position( iPosition ),
		  squareSize( iSquareSize )
		{};

		//! Updates internal state advancing time by dt seconds
		//! \param dt simulation step in seconds
		//! \return void
		void update( const float dt );

		//! \param force a force to apply for this frame to this entity (will be added to net force)
		//! \return void
		void applyForce( const Eigen::Vector3f& force );

		//! \return Eigen::Vector3f& representing current position of the sphere
		const Eigen::Vector3f& getPosition();

	private:
		Eigen::MatrixXi vertexes;
		Eigen::Vector3f position;
		float squareSize;
	};

	void HeightMap::update( const float dt )
	{
		return;
	}

	void HeightMap::applyForce( const Eigen::Vector3f& force )
	{
		return;
	}

	const Eigen::Vector3f& HeightMap::getPosition()
	{
		return position;
	}

}