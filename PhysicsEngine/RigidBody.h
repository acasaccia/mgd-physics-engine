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
#include "Constants.h"

namespace PhysicsEngine
{
	class RigidBody
	{
	public:

		real mResistanceToDeformation;
		real mElasticity;
		//real M=0.5;

		vector3 mLinearMomentum;
		vector3 mAngularMomentum;

		real mInverseMass;
		matrix3 mInverseInertiaTensor;

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
			mInverseMass(50.0f),
			mResistanceToDeformation(10),
			mElasticity(0.1f),
			mInverseInertiaTensor(matrix3::Identity()),
			mPosition(0,0,0),
			mOrientation(1,0,0,0),
			mVelocity(0,0,0),
			mAngularVelocity(0,0,0),
			mNetForce(0,0,0),
			mNetTorque(0,0,0),
			mRotationMatrix(matrix3::Identity())
		{}

		virtual int getType() = 0;

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

		//! http://eigen.tuxfamily.org/dox-devel/TopicStructHavingEigenMembers.html
		EIGEN_MAKE_ALIGNED_OPERATOR_NEW

	};

}