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
#include <iostream>

int main()
{
	PhysicsEngine::Simulation* simulation = new PhysicsEngine::Simulation;
	
	vector3 gravity( 0.0f, -9.8f, 0.0f );
	simulation->addGlobalForce("gravity", gravity);

	PhysicsEngine::RigidBody* sphere = new PhysicsEngine::Sphere(1.0f);
	simulation->addRigidBody("sphere_1", sphere);

	//Eigen::MatrixXi heightMap;

	//heightMap << 1, 2, 3,
	//			 4, 5, 6,
	//			 7, 8, 9;
								 
	int i = 0;
	while( ++i < 100 )
	{
		simulation->update(0.2f);
		std::cout << sphere->mPosition << std::endl;
	}
}