/*! 
 *  Component that checks for collisions between the entities we manage
 *  When implementing a new entity we should add the proper overloads to Collisor::check()
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

namespace PhysicsEngine
{

	class Collisor
	{
	public:
		//! Checks collision between two spheres
		//! \param iSphere_1 first sphere object
		//! \param iSphere_2 the other sphere
		//! \return Collision
		static Collision Collisor::check( const RigidBody* iRigidBody_1, const RigidBody* iRigidBody_2 )
		{
			// \todo: forward this to the right method of Collisor
			// function = mFunctorTable[ iRigidBody_1->mType ][ iRigidBody_2->mType ]
			// return function( const RigidBody* iRigidBody_1, const RigidBody* iRigidBody_2 );
			Collision* collision = new Collision();
			return *collision;
		}

		//! Checks collision between two spheres
		//! \param iSphere_1 first sphere object
		//! \param iSphere_2 the other sphere
		//! \return Collision
		static Collision Collisor::check( const Sphere& iSphere_1, const Sphere& iSphere_2 )
		{
			Collision* collision = new Collision();
			return *collision;
		}

		//! Checks collision between a sphere and an heightmap
		//! \param iSphere reference to Sphere object
		//! \param iTerrain reference to Terrain object
		//! \return Collision 
		static Collision Collisor::check( const Sphere& iSphere, const Terrain& iTerrain )
		{
			Collision* collision = new Collision();
			return *collision;
		}

		void (*foo)();

	};

}