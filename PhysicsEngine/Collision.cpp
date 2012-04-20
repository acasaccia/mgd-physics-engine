#include "LinearAlgebra.h"
#include "Collision.h"

using namespace PhysicsEngine;

Collision::Collision() :
	mContactPoint( vector3(0,0,0) ),
	mContactNormal( vector3(0,0,0) ),
	mPenetration( 0 )
{}

Collision::Collision( vector3& iContactPoint, vector3& iContactNormal, real iPenetration) :
	mContactPoint( vector3(0,0,0) ),
	mContactNormal( vector3(0,0,0) ),
	mPenetration( 0 )
{}