/*! 
 *  Component that checks for collisions between the entities we manage
 *  When implementing a new entity we should add the proper functions
 *  and update the routing table
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

		//! Through the routing table we instruct the collisor on how to handle each couple of rigid bodies
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

			// find which triangles could be colliding with sphere
			// ASSUMPTION: sphere radius < terrain triangle cathetus:
			// we check at most 18 neighbour triangles
			//  _ _ _ 
			// |_|_|_|
			// |_|X|_|
			// |_|_|_|
			//
			real halfFieldsize = terrain->mFieldSize / 2;
			
			int x = (int) floor( ( sphere->mPosition.x() + halfFieldsize ) / terrain->mSquareSize );
			int z = (int) floor( ( halfFieldsize - sphere->mPosition.z() ) / terrain->mSquareSize );

#if 1
			// Sphere to heightmap collision
			// first member of the pair is the number of triangles we actually found
			Triangle* neighboursTriangle = new Triangle[18];
			std::pair<int,Triangle*> trianglesToCheck = terrain->getTrianglesAroundVertex(x, z, neighboursTriangle);

			for(int c=0; c<trianglesToCheck.first; c++)	{

				//std::cout << "Checking for contact..." << std::endl;
				//std::cout << "Sphere position  : [" << sphere->mPosition(0) << ", " << sphere->mPosition(1) << ", " << sphere->mPosition(2) << "]" << std::endl;
				//std::cout << "Triangle vertex 1: [" << trianglesToCheck.second[c].mVertexes[0](0) << ", " << trianglesToCheck.second[c].mVertexes[0](1) << ", " << trianglesToCheck.second[c].mVertexes[0](2) << "]" << std::endl;
				//std::cout << "Triangle vertex 2: [" << trianglesToCheck.second[c].mVertexes[1](0) << ", " << trianglesToCheck.second[c].mVertexes[1](1) << ", " << trianglesToCheck.second[c].mVertexes[1](2) << "]" << std::endl;
				//std::cout << "Triangle vertex 3: [" << trianglesToCheck.second[c].mVertexes[2](0) << ", " << trianglesToCheck.second[c].mVertexes[2](1) << ", " << trianglesToCheck.second[c].mVertexes[2](2) << "]" << std::endl;
				//system("cls");

				if ( Collisor::checkTriangleWithSphere(trianglesToCheck.second[c], sphere, collision) ) {
					// ASSUMPTION: terrain has infinite mass
					// we compute forces for the sphere only
					Collisor::resolveCollision( collision, iRigidBody_1, iRigidBody_2 );
				}
			}

			delete[] neighboursTriangle;
#else
			// Simplified version: treats terrain as a stack of voxels (ignores triangles tessellation)
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
#endif

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
			real penetration = sphere_1->mRadius - sphere_2->mRadius - distance;
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

			real f = relativeVelocity.dot( iCollision.mContactNormal );
			//vector3 vTang = iCollision.mContactNormal * f;
			//vTang -= relativeVelocity;

			f = iRigidBody_1->mResistanceToDeformation * iCollision.mPenetration - iRigidBody_1->mElasticity * f;

			if (f < 0)
				f = 0;
			
			force = iCollision.mContactNormal * f;

			//f *= iRigidBody_1->mFriction;
			//real ModVtang = vTang.norm();
			//vTang *= -f;

			//if(ModVtang < 0.2 )
			//	vTang /= 0.2;
			//else
			//	vTang /= ModVtang;

			//force += vTang;
			return force;
		}

		static bool Collisor::checkTriangleWithSphere( Triangle& iTriangle, Sphere* iSphere, Collision& iCollision )
		{
			vector3 closestPointToSphere = Triangle::closestPointToPoint(iSphere->mPosition, iTriangle.mVertexes[0], iTriangle.mVertexes[1], iTriangle.mVertexes[2]);

			// Sphere and triangle intersect if the distance from sphere
			// center to point p is less than the sphere radius
			vector3 triangleSphereVector = closestPointToSphere - iSphere->mPosition;
			real triangleSphereDistance = triangleSphereVector.norm();

			if ( triangleSphereDistance < iSphere->mRadius ) {

				// update collision
				iCollision.mContactNormal = Triangle::normal( iTriangle.mVertexes[1] - iTriangle.mVertexes[0], iTriangle.mVertexes[2] - iTriangle.mVertexes[1] );
				iCollision.mContactPoint = closestPointToSphere;
				iCollision.mPenetration = iSphere->mRadius - triangleSphereDistance;

				//system("cls");
				//std::cout << "Contact!" << std::endl;
				//std::cout << "Sphere position  : [" << iSphere->mPosition(0) << ", " << iSphere->mPosition(1) << ", " << iSphere->mPosition(2) << "]" << std::endl;
				//std::cout << "Triangle vertex 1: [" << iTriangle.mVertexes[0](0) << ", " << iTriangle.mVertexes[0](1) << ", " << iTriangle.mVertexes[0](2) << "]" << std::endl;
				//std::cout << "Triangle vertex 2: [" << iTriangle.mVertexes[1](0) << ", " << iTriangle.mVertexes[1](1) << ", " << iTriangle.mVertexes[1](2) << "]" << std::endl;
				//std::cout << "Triangle vertex 3: [" << iTriangle.mVertexes[2](0) << ", " << iTriangle.mVertexes[2](1) << ", " << iTriangle.mVertexes[2](2) << "]" << std::endl;
				//std::cout << "Closest point to sphere: [" << iCollision.mContactPoint << "]" << std::endl;
				//std::cout << "Contact normal: [" << iCollision.mContactNormal(0) << ", " << iCollision.mContactNormal(1) << ", " << iCollision.mContactNormal(2) << "]" << std::endl;
				//std::cout << "Contact point:  [" << iCollision.mContactPoint(0) << ", " << iCollision.mContactPoint(1) << ", " << iCollision.mContactPoint(2) << "]" << std::endl;
				//std::cout << "Penetration:    [" << iCollision.mPenetration << "]" << std::endl;

				return true;
			} else {
				return false;
			}
		}

	};

}