/*! 
 *  Public interface for all PhysicsEngine entities implementations
 *  -
 *  Implementation of a simple physics engine, Physics Programming course
 *  Master in Computer Game Developement, Verona, Italy
 *  -
 *  \author Andrea Casaccia
 *  \date 23 March 2012
 */

#pragma once

#include "Eigen\Core"

namespace PhysicsEngine
{
	class EntityInterface
	{
	public:
		//! Updates internal state advancing time by dt seconds
		//! \param dt simulation step in seconds
		//! \return void
		virtual void update( const float dt ) = 0;

		//! Applies a force for the duration of this simulation step to this entity
		//! \param force the force to be applied
		//! \return void
		virtual void applyForce( const Eigen::Vector3f& force ) = 0;

		//! Returns current entity position
		//! \return Eigen::Vector3f& representing current position of the sphere
		virtual const Eigen::Vector3f& getPosition() = 0;

	};
}