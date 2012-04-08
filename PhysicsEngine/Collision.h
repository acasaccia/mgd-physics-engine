/*! 
 *  
 *  -
 *  Implementation of a simple physics engine, Physics Programming course
 *  Master in Computer Game Developement, Verona, Italy
 *  -
 *  \author Andrea Casaccia
 *  \date 23 March 2012
 */

#pragma once

#include "LinearAlgebra.h"

namespace PhysicsEngine
{
	class Collision
	{
		//! Position of the contact in world coordinates.
		vector3 mContactPoint;

		//! Direction of the contact in world coordinates.
		vector3 mContactNormal;

		//! Depth of penetration at the contact point. If both
		//! bodies are specified then the contact point should be midway
		//! between the inter-penetrating points.
		real mPenetration;
	};
}