/*! 
 *  Main class of the engine.
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
#include "Sphere.h"
#include "Terrain.h"
#include "Collisor.h"
#include <map>
#include <string>

namespace PhysicsEngine
{
	// http://eigen.tuxfamily.org/dox-devel/TopicStlContainers.html
	typedef std::map<std::string, RigidBody*, std::less<std::string>, Eigen::aligned_allocator< std::pair<const int, vector3>>> stringToRigidBodyMap;
	typedef std::map<std::string, vector3*, std::less<std::string>, Eigen::aligned_allocator< std::pair<const int, vector3>>> stringToForceMap;

	class Simulation
	{
	public:

		stringToRigidBodyMap mRigidBodies;
		stringToForceMap mGlobalForces;
		Collisor mCollisor;

		Simulation();
		Simulation::~Simulation();

		//! Adds a rigid body to be managed by the engine
		//! \param iBodyName a label associated to the body for future retrieval
		//! \param iBody a pointer to rigid body
		//! \return void
		void addRigidBody( std::string, RigidBody* const );

		//! Adds a force that acts on all rigid bodies
		//! \param iForceName a label associated to the force for future retrieval
		//! \param iForce the vector representing the force
		//! \return void
		void addGlobalForce( std::string, vector3* const );

		//! Applies registered global forces to rigid bodies
		//! then updates their internal state advancing time by dt seconds
		//! \param iDt simulation step in seconds
		//! \return void
		void update( const float );

		// http://eigen.tuxfamily.org/dox-devel/TopicStructHavingEigenMembers.html
		EIGEN_MAKE_ALIGNED_OPERATOR_NEW

	};

}