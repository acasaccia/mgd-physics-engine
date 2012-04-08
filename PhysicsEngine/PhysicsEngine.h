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
#include "HeightMap.h"
#include "Collisor.h"
#include <map>
#include <string>

namespace PhysicsEngine
{
	class Simulation
	{
	public:
		Simulation() :
		  mRigidBodies(),
		  mGlobalForces()
		  {};

		//! Adds a rigid body to be managed by the engine
		//! \param iBodyName a label associated to the body for future retrieval
		//! \param iBody a pointer to rigid body
		//! \return void
		void addRigidBody( const std::string, RigidBody* const );

		//! Adds a force that acts on all rigid bodies
		//! \param iForceName a label associated to the force for future retrieval
		//! \param iForce the vector representing the force
		//! \return void
		void addGlobalForce( const std::string, const vector3 );

		//! Applies registered global forces to rigid bodies
		//! then updates their internal state advancing time by dt seconds
		//! \param iDt simulation step in seconds
		//! \return void
		void update( const real );

	private:
		std::map<std::string, RigidBody*> mRigidBodies;
		std::map<std::string, vector3> mGlobalForces;
	};

	void Simulation::addGlobalForce( const std::string iForceName, const vector3 iForce )
	{
		mGlobalForces[ iForceName ] = iForce;
	}

	void Simulation::addRigidBody( const std::string iRigidBodyName, RigidBody* const iRigidBody )
	{
		mRigidBodies[ iRigidBodyName ] = iRigidBody;
	}

	void Simulation::update( const real iDt )
	{
		std::map<std::string,RigidBody*>::iterator bodiesIt;

		// Check collisions between all registered entities
		//std::map<std::string,RigidBody*>::iterator bodiesIt_2;
		//for (bodiesIt = rigidBodies.begin(); bodiesIt != rigidBodies.end(); ++bodiesIt)
		//	for (bodiesIt_2 = rigidBodies.begin(); bodiesIt_2 != rigidBodies.end(); ++bodiesIt_2)
		//		if (bodiesIt != bodiesIt_2)
		//			Collisor::check(bodiesIt->second, bodiesIt_2->second);

		// Apply global forces
		std::map<std::string,vector3>::iterator forcesIt;

		for (forcesIt = mGlobalForces.begin(); forcesIt != mGlobalForces.end(); ++forcesIt)
			for (bodiesIt = mRigidBodies.begin(); bodiesIt != mRigidBodies.end(); ++bodiesIt)
				bodiesIt->second->applyForce(forcesIt->second);

		// Update all bodies
		for (bodiesIt = mRigidBodies.begin(); bodiesIt != mRigidBodies.end(); ++bodiesIt)
			bodiesIt->second->update(iDt);
	}

}