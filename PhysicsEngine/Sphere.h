/*! 
 *  A physical sphere with a radius, a mass, a position and a linear momentum
 *  -
 *  Implementation of a simple physics engine, Physics Programming course
 *  Master in Computer Game Developement, Verona, Italy
 *  -
 *  \author Andrea Casaccia
 *  \date 23 March 2012
 */

#pragma once

#include "EntityInterface.h"
#include "Eigen\Core"

namespace PhysicsEngine
{

	class Sphere : public EntityInterface
	{
	public:
		Sphere( const float iRadius, const float iMass, const Eigen::Vector3f iPosition, const Eigen::Vector3f iLinearMomentum ) :
		  radius( iRadius ),
		  mass( iMass ),
		  position( iPosition ),
		  linearMomentum( iLinearMomentum ),
		  netForce(0.0f, 0.0f, 0.0f)
		{};

		//! Updates internal state advancing time by dt seconds
		//! \param dt simulation step in seconds
		//! \return void
		void update( const float dt );

		//! \param force a force to apply for this frame to this entity (will be added to net force)
		//! \return void
		void applyForce( const Eigen::Vector3f& force );

		//! \return Eigen::Vector3f& representing current position of the sphere
		const Eigen::Vector3f& getPosition();

	private:
		float radius;
		float mass;
		Eigen::Vector3f position;
		Eigen::Vector3f linearMomentum;
		Eigen::Vector3f netForce;
	};

	void Sphere::update( const float dt )
	{
		linearMomentum += netForce * dt;
		Eigen::Vector3f speed = linearMomentum / mass;
		position += speed * dt;
		
		// reset resulting force
		netForce = Eigen::Vector3f::Zero();

		return;
	}

	void Sphere::applyForce( const Eigen::Vector3f& force )
	{
		netForce += force;
		return;
	}

	const Eigen::Vector3f& Sphere::getPosition()
	{
		return position;
	}

}