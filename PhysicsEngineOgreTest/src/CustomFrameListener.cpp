
#include "CustomFrameListener.h"

CustomFrameListener::CustomFrameListener(Ogre::SceneManager* iSceneManager, PhysicsEngine::Simulation* iSimulation)
{
	mSceneManager = iSceneManager;
	mSimulation = iSimulation;
}

//-------------------------------------------------------------------------------------
bool CustomFrameListener::frameStarted(const Ogre::FrameEvent &evt)
{
	// Advance simulation
	mSimulation->update( evt.timeSinceLastFrame );

	// Update position of Ogre entities based on physics simulation
	PhysicsEngine::stringToRigidBodyMap::iterator it;
	for (it = mSimulation->mRigidBodies.begin(); it != mSimulation->mRigidBodies.end(); ++it)
	{
		std::string entityName = it->first;
		PhysicsEngine::RigidBody* body = it->second;
		// It's useless to check for immovable entities
		if (body->mInverseMass != 0)
		{
			Ogre::Vector3 position = Ogre::Vector3( body->mPosition.data() );

			// Collision check with plane @todo: organize this into a collisor
			if ( position.y - 12.5f < -50 )
			{
				body->mLinearMomentum *= -body->mRestitutionCoefficient;
				body->mPosition.y() = -50.0f + 12.5f;
			}

			mSceneManager->getEntity(entityName)->getParentNode()->setPosition( position );
		}
	}
	return true;
}