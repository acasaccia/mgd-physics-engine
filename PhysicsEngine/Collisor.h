/*! 
 *  Component that checks for collisions between the entities we manage
 *  When implementing a new entity we should add the proper functions
 *  -
 *  Implementation of a simple physics engine, Physics Programming course
 *  Master in Computer Game Developement, Verona, Italy
 *  -
 *  \author Andrea Casaccia
 *  \date 23 March 2012
 */

#pragma once

#include "LinearAlgebra.h"
#include "Sphere.h"
#include "Terrain.h"
#include "Collision.h"
#include <string>
#include <map>
#include <iostream>
#include <cmath>
#include <utility>

namespace PhysicsEngine
{

	class Collisor
	{
	public:

		//! Through the routing table we instruct the collisor on how to handle each kind of collision
		typedef std::map<int, std::map<int, void (*)(RigidBody*, RigidBody*)>> functionPointersTable;
		functionPointersTable mRoutingTable;

		//! Constructor initializes the routing table
		Collisor::Collisor()
		{
			mRoutingTable [RIGID_BODY_TYPE_SPHERE]	[RIGID_BODY_TYPE_TERRAIN]	= &Collisor::checkSphereWithTerrain;
			mRoutingTable [RIGID_BODY_TYPE_TERRAIN]	[RIGID_BODY_TYPE_SPHERE]	= &Collisor::checkTerrainWithSphere;
			mRoutingTable [RIGID_BODY_TYPE_SPHERE]	[RIGID_BODY_TYPE_SPHERE]	= &Collisor::checkSphereWithSphere;
		}

		//! Checks collision between generic rigid bodies
		//! \param iRigidBody_1 first sphere object
		//! \param iRigidBody_2 the other object
		void Collisor::check( RigidBody* iRigidBody_1, RigidBody* iRigidBody_2 )
		{
			void (*functionToCall)(RigidBody*, RigidBody*) = mRoutingTable [ iRigidBody_1->getType() ] [ iRigidBody_2->getType() ];
			return functionToCall( iRigidBody_1, iRigidBody_2 );
		}

		//! Checks collision between two spheres
		//! \param iSphere_1 first sphere object
		//! \param iSphere_2 the other sphere
		//! \return Collision
		static void Collisor::checkSphereWithTerrain( RigidBody* iRigidBody_1, RigidBody* iRigidBody_2 )
		{
			Sphere *sphere = dynamic_cast<Sphere *>(iRigidBody_1);
			Terrain *terrain = dynamic_cast<Terrain *>(iRigidBody_2);
			Collision collision;

			// project center of the sphere on terrain to
			// find which square sphere is over at the moment
			// pivot vertex is the vertex by which we identify
			// a cell on the heightmap

			// find which triangles could be colliding with sphere
			// ASSUMPTION: sphere radius < terrain triangle cathetus:
			// we check at most 18 neighbour triangles
			//  _ _ _ 
			// |_|_|_|
			// |_|X|_|
			// |_|_|_|
			//
			real halfTerrainSize = terrain->mVertexes.rows() * terrain->mCellSize / 2;
			int x = (int) floor( (sphere->mPosition.x() + halfTerrainSize) / terrain->mCellSize );
			int z = (int) floor( (sphere->mPosition.z() + halfTerrainSize) / terrain->mCellSize );

			// first member of the pair is the number of triangles we actually found
			std::pair<int,Triangle*> trianglesToCheck = terrain->getNeighbourTriangles(x, z);

			for(int c=0; c<trianglesToCheck.first; c++)
				if ( Collisor::checkTriangleWithSphere(trianglesToCheck.second[c], sphere) )
					// ASSUMPTION: terrain has infinite mass
					// we compute forces for the sphere only
					Collisor::resolveCollision( collision, iRigidBody_1, iRigidBody_2 );

			// Simplified version: treats terrain as a stack of voxels
			real height = terrain->mVertexes(x,z);
			if ( sphere->mPosition.y() - sphere->mRadius < height )
			{
				collision.mContactPoint = vector3(sphere->mPosition.x(), height, sphere->mPosition.z());;
				collision.mContactNormal = vector3(0,1,0);
				collision.mPenetration = height - (sphere->mPosition.y() - sphere->mRadius);
				// ASSUMPTION: terrain has infinite mass
				// we compute forces for the sphere only
				Collisor::resolveCollision( collision, iRigidBody_1, iRigidBody_2 );
			}

		}

		//! Checks collision between a sphere and an heightmap
		//! \param iSphere reference to Sphere object
		//! \param iTerrain reference to Terrain object
		//! \return Collision 
		static void Collisor::checkTerrainWithSphere( RigidBody* iRigidBody_1, RigidBody* iRigidBody_2 )
		{
			return Collisor::checkSphereWithTerrain( iRigidBody_2, iRigidBody_1 );
		}

		static void Collisor::checkSphereWithSphere( RigidBody* iRigidBody_1, RigidBody* iRigidBody_2 )
		{
			Sphere *sphere_1 = dynamic_cast<Sphere *>(iRigidBody_1);
			Sphere *sphere_2 = dynamic_cast<Sphere *>(iRigidBody_2);

			// distance between spheres centre
			vector3 distanceVector = sphere_1->mPosition - sphere_2->mPosition;
			real distance = (distanceVector).norm();
			vector3 distanceDirection = distanceVector / distance;
			real penetration = sphere_1->mRadius + sphere_2->mRadius - distance;
			if ( penetration > 0 )
			{
				Collision collision = Collision (distanceVector, distanceDirection, penetration);
				Collisor::resolveCollision( collision, iRigidBody_1, iRigidBody_2 );

				distanceVector*=-1;
				distanceDirection*=-1;
				collision = Collision (distanceVector, distanceDirection, penetration);
				Collisor::resolveCollision( collision, iRigidBody_2, iRigidBody_1 );
			}
		}

		static void Collisor::resolveCollision( Collision& iCollision, RigidBody* iRigidBody_1, RigidBody* iRigidBody_2 )
		{
			vector3 force = Collisor::computeForce(iCollision, iRigidBody_1, iRigidBody_2);
			iRigidBody_1->applyForceAtPoint(force, iCollision.mContactPoint);
		}

		static vector3 Collisor::computeForce( Collision& iCollision, RigidBody* iRigidBody_1, RigidBody* iRigidBody_2 )
		{
			vector3 force(0,0,0);
			vector3 relativeVelocity = iRigidBody_1->mVelocity - iRigidBody_2->mVelocity;

			//real f = relativeVelocity.dot( iCollision.mContactNormal );
			//vector3 vTang = iCollision.mContactNormal * f;
			//vTang = vrel_1_2 - vTang;
			//f = K*d - L*f;

			real f = iRigidBody_1->mResistanceToDeformation * iCollision.mPenetration
			         - iRigidBody_1->mElasticity * relativeVelocity.dot( iCollision.mContactNormal );

			if (f < 0)
				f = 0;
			
			force = iCollision.mContactNormal * f;

			//f *= M;
			//real ModVtang = vTang.norm();
			//vTang *= -f;
			//if(ModVtang < 9.8f * 0.02 ) vTang /= 9.8f * 0.02;
			//else vTang /= ModVtang;
			//Fout += vTang;
			return force;
		}

		static bool Collisor::checkTriangleWithSphere( const Triangle& iTriangle, const Sphere* iSphere )
		{
			
		}

	};

}