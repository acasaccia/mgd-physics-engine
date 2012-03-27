/*! 
 *  Component who checks for collisions between the entities we can manage
 *  When implementing a new entity we should add the proper overloads to Collisor::check()
 *  -
 *  Implementation of a simple physics engine, Physics Programming course
 *  Master in Computer Game Developement, Verona, Italy
 *  -
 *  \author Andrea Casaccia
 *  \date 23 March 2012
 */

#pragma once

#include "Sphere.h"
#include "HeightMap.h"

namespace PhysicsEngine
{

	class Collisor
	{
	public:
		//! Checks collision between two spheres
		//! \param iSphere_1 first sphere object
		//! \param iSphere_2 the other sphere
		//! \return 
		float Collisor::check( const Sphere& iSphere_1, const Sphere& iSphere_2 )
		{
			return 0.0f;
		}

		//! Checks collision between a sphere and an heightmap
		//! \param iSphere reference to Sphere object
		//! \param iHeightMap reference to HeightMap object
		//! \return float 
		float Collisor::check( const Sphere& iSphere, const HeightMap& iHeightMap )
		{
			return 0.0f;
		}

	};

}