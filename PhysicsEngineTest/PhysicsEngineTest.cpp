#include "PhysicsEngine.h"

int main()
{
	PhysicsEngine::Simulation* test = new PhysicsEngine::Simulation;
	
	PhysicsEngine::Vector3 gravity = { 0.0f, -9.8f, 0.0f };

	test->addGlobalForce("gravity", gravity);

	PhysicsEngine::Vector3 position = { 0.0f, 0.0f, 0.0f };
	PhysicsEngine::Vector3 speed = { 0.0f, 0.0f, 0.0f };

	PhysicsEngine::EntityInterface* sphere_1 = new PhysicsEngine::Sphere(1.0f, 5.0f, position, speed);
	
	test->addEntity(sphere_1);
}