/*! 
 *  Represents a sphere.
 *  Physics Programming, Master in Computer Game Developement, Verona, Italy
 *  \author Andrea Casaccia
 *  \date 23 Marzo 2012
 */

#pragma once

#include "EntityInterface.h"
#include "Utilities.h"

namespace PhysicsEngine
{

	class Sphere : public EntityInterface
	{
	public:
		Sphere( const float iRadius, const float iMass, const Vector3 iPosition, const Vector3 iSpeed ) :
		  radius( iRadius ),
		  mass( iMass ),
		  position( iPosition ),
		  speed( iSpeed )
		{};
		void update();

	private:
		float radius;
		float mass;
		Vector3 position;
		Vector3 speed;
	};

	void Sphere::update()
	{
		return;
	}

}