/*! 
 *  Component that checks for collisions between the entities we manage
 *  When implementing a new entity we should add the proper functions
 *  -
 *  Implementation of a simple physics engine, Physics Programming course
 *  Master in Computer Game Developement, Verona, Italy
 *  -
 *  \author Andrea Casaccia
 *  \date 23 March 2012
 */

#pragma once

#include "LinearAlgebra.h"
#include "Sphere.h"
#include "Terrain.h"
#include "Collision.h"
#include <string>
#include <map>

namespace PhysicsEngine
{

	class Collisor
	{
	public:

		//! Through the routing table we instruct the collisor on how to handle each kind of collision check
		typedef std::map<int, std::map<int, void (*)(RigidBody*, RigidBody*)>> functionPointersTable;
		functionPointersTable mRoutingTable;

		//! Constructor initializes the routing table
		Collisor::Collisor()
		{
			mRoutingTable [RIGID_BODY_TYPE_SPHERE]	[RIGID_BODY_TYPE_TERRAIN]	= &Collisor::checkSphereWithTerrain;
			mRoutingTable [RIGID_BODY_TYPE_TERRAIN]	[RIGID_BODY_TYPE_SPHERE]	= &Collisor::checkTerrainWithSphere;
			mRoutingTable [RIGID_BODY_TYPE_SPHERE]	[RIGID_BODY_TYPE_SPHERE]	= &Collisor::checkSphereWithSphere;
		}

		//! Checks collision between two spheres
		//! \param iSphere_1 first sphere object
		//! \param iSphere_2 the other sphere
		//! \return Collision
		void Collisor::check( RigidBody* iRigidBody_1, RigidBody* iRigidBody_2 )
		{
			void (*functionToCall)(RigidBody*, RigidBody*) = mRoutingTable [ iRigidBody_1->getType() ] [ iRigidBody_2->getType() ];
			return functionToCall( iRigidBody_1, iRigidBody_2 );
		}

		//! Checks collision between two spheres
		//! \param iSphere_1 first sphere object
		//! \param iSphere_2 the other sphere
		//! \return Collision
		static void Collisor::checkSphereWithTerrain( RigidBody* iRigidBody_1, RigidBody* iRigidBody_2 )
		{
			Sphere *sphere = dynamic_cast<Sphere *>(iRigidBody_1);
			Terrain *terrain = dynamic_cast<Terrain *>(iRigidBody_2);
		}

		//! Checks collision between a sphere and an heightmap
		//! \param iSphere reference to Sphere object
		//! \param iTerrain reference to Terrain object
		//! \return Collision 
		static void Collisor::checkTerrainWithSphere( RigidBody* iRigidBody_1, RigidBody* iRigidBody_2 )
		{
			return Collisor::checkSphereWithTerrain( iRigidBody_2, iRigidBody_1 );
		}

		static void Collisor::checkSphereWithSphere( RigidBody* iRigidBody_1, RigidBody* iRigidBody_2 )
		{
			Sphere *sphere_1 = dynamic_cast<Sphere *>(iRigidBody_1);
			Sphere *sphere_2 = dynamic_cast<Sphere *>(iRigidBody_2);
		}

	};

}