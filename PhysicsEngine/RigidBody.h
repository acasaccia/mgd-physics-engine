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
	class RigidBody
	{
	public:
		
		vector3 mLinearMomentum;
		vector3 mAngularMomentum;

		real mInverseMass;
		matrix3 mInverseInertiaTensor;
		real mLinearDamping;
		real mAngularDamping;

		vector3 mPosition;
		quaternion mOrientation;
		vector3 mVelocity;
		vector3 mAngularVelocity;
		
		vector3 mNetForce;
		vector3 mNetTorque;
		
		matrix3 mRotationMatrix;

		RigidBody() :
			mLinearMomentum(0,0,0),
			mAngularMomentum(0,0,0),
			mInverseMass(1.0),
			mInverseInertiaTensor(matrix3::Identity()),
			mLinearDamping(0),
			mAngularDamping(0),
			mPosition(0,0,0),
			mOrientation(1,0,0,0),
			mVelocity(0,0,0),
			mAngularVelocity(0,0,0),
			mNetForce(0,0,0),
			mNetTorque(0,0,0),
			mRotationMatrix(matrix3::Identity())
			{}


		//! Updates internal state advancing time by dt seconds
		//! \param iDt simulation step in seconds
		//! \return void
		void update( const real iDt );

		//! Applies a force for the duration of this simulation step on the center of mass of this entity
		//! \param iForce a vector representing the force to be applied
		void applyForce( const vector3& iForce );

		//! Applies a force for the duration of this simulation step on a point of this rigidBody
		//! This results in a force and a torque to be applied
		//! \param iPoint a vector representing the point of application
		//! \param iForce a vector representing the force to be applied
		void applyForceAtPoint( const vector3& iForce, const vector3& iPoint );

		//! Resets forces applied to the entity
		void resetNetForce();

		//! Resets torques applied to the entity
		void resetNetTorque();

	};

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