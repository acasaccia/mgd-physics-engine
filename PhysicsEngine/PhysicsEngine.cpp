
#include "LinearAlgebra.h"
#include "PhysicsEngine.h"
#include "RigidBody.h"
#include "Collisor.h"

using namespace PhysicsEngine;

Simulation::Simulation() :
	mCollisor( Collisor() )
{}

Simulation::~Simulation()
{
	stringToRigidBodyMap::iterator bodiesIt;
	for (bodiesIt = mRigidBodies.begin(); bodiesIt != mRigidBodies.end(); ++bodiesIt)
		delete bodiesIt->second;
	stringToForceMap::iterator forcesIt;
	for (forcesIt = mGlobalForces.begin(); forcesIt != mGlobalForces.end(); ++forcesIt)
		delete forcesIt->second;
}

void Simulation::addGlobalForce( std::string iForceName, vector3* const iForce )
{
	mGlobalForces[iForceName] = iForce;
}

void Simulation::addRigidBody( std::string iRigidBodyName, RigidBody* iRigidBody )
{
	mRigidBodies[iRigidBodyName] = iRigidBody;
}

void Simulation::update( const float iDt )
{
	stringToRigidBodyMap::iterator bodiesIt;

	// Check collisions between registered entities:
	// we check each pair of entities only once, order doesn't count
	stringToRigidBodyMap::iterator bodiesIt_2;
	for (bodiesIt = mRigidBodies.begin(); bodiesIt != mRigidBodies.end(); ++bodiesIt)
		for (bodiesIt_2 = mRigidBodies.begin(); bodiesIt_2 != mRigidBodies.end(); ++bodiesIt_2)
			if (bodiesIt != bodiesIt_2)
				mCollisor.check(bodiesIt->second, bodiesIt_2->second);

	// Apply global forces
	stringToForceMap::iterator forcesIt;

	for (forcesIt = mGlobalForces.begin(); forcesIt != mGlobalForces.end(); ++forcesIt)
		for (bodiesIt = mRigidBodies.begin(); bodiesIt != mRigidBodies.end(); ++bodiesIt)
			if (bodiesIt->second->mInverseMass > 0)
				bodiesIt->second->applyForce(*(forcesIt->second));

	// Update all bodies
	for (bodiesIt = mRigidBodies.begin(); bodiesIt != mRigidBodies.end(); ++bodiesIt)
		if (bodiesIt->second->mInverseMass > 0)
			bodiesIt->second->update(iDt);
}
