/*! 
 *  Represents an height map.
 *  Physics Programming, Master in Computer Game Developement, Verona, Italy
 *  \author Andrea Casaccia
 *  \date 23 Marzo 2012
 */

#pragma once

#include "EntityInterface.h"

namespace PhysicsEngine
{

	class HeightMap : public EntityInterface
	{
	public:
		void update();
	private:
		int position;
		int speed;
		int acceleration;
	};

}