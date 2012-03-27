/*! 
 *  Main class of the engine.
 *  Entities are added with addEntity()
 *  Forces who act globally (e.g. gravity) are registered with addGlobalForce()
 *  Simulation advances using update()
 *  -
 *  Implementation of a simple physics engine, Physics Programming course
 *  Master in Computer Game Developement, Verona, Italy
 *  -
 *  \author Andrea Casaccia
 *  \date 23 March 2012
 */

#pragma once

#include "Collisor.h"
#include "Sphere.h"
#include "HeightMap.h"
#include "Eigen\Core"
#include <vector>
#include <map>
#include <string>

namespace PhysicsEngine
{

	class Simulation
	{
	public:
		Simulation() :
		  entities() {};

		//! Adds an entity to be managed by the engine
		//! \param iEntity a pointer to a physical entity implementing EntityInterface
		//! \return void
		void addEntity( EntityInterface* const );

		//! Adds a force that acts on all entites (except those who explicitly ask to be skipped)
		//! then updates their internal state
		//! \param iForceName a label associated to the force for future retrieval
		//! \param iForce the vector representing the force
		//! \return void
		void addGlobalForce( const std::string, const Eigen::Vector3f );

		//! Applies registered global forces to entities
		//! then updates their internal state advancing time by dt seconds
		//! \param dt simulation step in seconds
		//! \return void
		void update( const float );

	private:
		std::vector<EntityInterface*> entities;
		std::map<std::string,Eigen::Vector3f> globalForces;
	};

	void Simulation::addGlobalForce( const std::string iForceName, const Eigen::Vector3f iForce )
	{
		globalForces[ iForceName ] = iForce;
	}

	void Simulation::addEntity( EntityInterface* const iEntity )
	{
		entities.push_back( iEntity );
	}

	void Simulation::update( const float dt )
	{
		std::map<std::string,Eigen::Vector3f>::iterator it;
		for (it = globalForces.begin(); it != globalForces.end(); ++it)
		{
			Eigen::Vector3f force = it->second;
			for(unsigned int i=0; i<entities.size(); ++i)
			{
				entities[i]->applyForce( force );
			}
		}

		for(unsigned int i=0; i<entities.size(); ++i)
		{
			entities[i]->update( dt );
		}
	}

}