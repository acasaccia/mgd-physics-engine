/*! 
 *  Implementation of a simple Physics Engine
 *  Physics Programming course,
 *  Master in Computer Game Developement, Verona, Italy
 *  \author Andrea Casaccia
 *  \date 23 Marzo 2012
 */

#pragma once

#include "Collisor.h"
//#include "Integrator.h"
#include "Sphere.h"
#include "HeightMap.h"
#include "Utilities.h"
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
		void addEntity( EntityInterface* const );
		void addGlobalForce( const std::string, const Vector3 );
		void update( const unsigned int );
	private:
		std::vector<EntityInterface*> entities;
		std::map<std::string,Vector3> globalForces;
	};

	//! Adds a 
	//! then updates their internal state
	//! \param iForceName a label associated to the force for future retrieval
	//! \param iForce the vector representing the force
	//! \return void
	void Simulation::addGlobalForce( const std::string iForceName, const Vector3 iForce )
	{
		globalForces[ iForceName ] = iForce;
	}

	//! Adds an entity to be managed
	//! \param iEntity a pointer to a physical entity implementing EntityInterface
	//! \return void
	void Simulation::addEntity( EntityInterface* const iEntity )
	{
		entities.push_back( iEntity );
	}

	//! Applies registered global forces to all entities
	//! then updates their internal state
	//! \param dt simulation step in milliseconds
	//! \return void
	void Simulation::update( const unsigned int dt )
	{
		for(unsigned int i=0; i<entities.size(); ++i)
		{
			entities[i]->update();
		}
	}

}