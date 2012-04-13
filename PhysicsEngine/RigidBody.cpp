#pragma once

#include "LinearAlgebra.h"
#include "RigidBody.h"

namespace PhysicsEngine
{

	void RigidBody::resetNetForce()
	{
		mNetForce = vector3::Zero();
	}

	void RigidBody::resetNetTorque()
	{
		mNetTorque = vector3::Zero();
	}

	void RigidBody::update( const real iDt )
	{
		// Linear momentum variation
		mLinearMomentum += mNetForce * iDt;

		// Angular momentum variation
		mAngularMomentum += mNetTorque * iDt;

		// Velocity and position update
		mVelocity = mLinearMomentum * mInverseMass;
		mPosition += mVelocity * iDt;

		// Convert angular velocity to local space
		mAngularVelocity = mRotationMatrix * mAngularVelocity;

		// Angular velocity update
		mAngularVelocity = mInverseInertiaTensor * mAngularVelocity;

		// Store orientation change in a temporary quaternion
		quaternion temp = quaternion(
			1,
			mAngularVelocity(0) * iDt / 2,
			mAngularVelocity(1) * iDt / 2,
			mAngularVelocity(2) * iDt / 2
		);

		temp.normalize();

		// Orientation update
		mOrientation = mOrientation * temp;

		mOrientation.normalize();

		// Convert angular velocity back to global space
		mAngularVelocity = mRotationMatrix.transpose() * mAngularVelocity;
		
		// Get rotation matrix from quaternion
		mRotationMatrix = mOrientation.toRotationMatrix();
		
		// Clear accumulators.
		resetNetForce();
		resetNetTorque();
	}

	void RigidBody::applyForce( const vector3& iForce )
	{
		mNetForce += iForce;
	}

	void RigidBody::applyForceAtPoint( const vector3& iForce, const vector3& iPoint )
	{
		mNetForce += iForce;
		vector3 temp = iPoint - mPosition;
		mNetTorque += temp.cross(iForce);
	}

}