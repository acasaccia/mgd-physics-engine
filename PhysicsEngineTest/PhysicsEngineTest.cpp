/*! 
 *  Simple test for PhysicsEngine library
 *  -
 *  Implementation of a simple physics engine, Physics Programming course
 *  Master in Computer Game Developement, Verona, Italy
 *  -
 *  \author Andrea Casaccia
 *  \date 23 March 2012
 */

#include "PhysicsEngine.h"
#include "Eigen\Core"
#include <iostream>

int main()
{
	PhysicsEngine::Simulation* simulation = new PhysicsEngine::Simulation;
	
	Eigen::Vector3f gravity( 0.0f, -9.8f, 0.0f );
	simulation->addGlobalForce("gravity", gravity);

	Eigen::Vector3f position( 0.0f, 100.0f, 0.0f );
	Eigen::Vector3f linearMomentum( 0.0f, 0.0f, 0.0f );
	PhysicsEngine::EntityInterface* sphere = new PhysicsEngine::Sphere(1.0f, 5.0f, position, linearMomentum);
	simulation->addEntity(sphere);

	Eigen::MatrixX2i heightMap;

	heightMap << 1, 2, 3,
				 4, 5, 6,
				 7, 8, 9;
								 
	PhysicsEngine::EntityInterface* heightmap = new PhysicsEngine::HeightMap(heightMap, Eigen::Vector3f::Zero(), 10.0f);

	int i = 0;
	while( ++i < 100 )
	{
		simulation->update(0.2f);
		std::cout << sphere->getPosition() << std::endl;
	}
}