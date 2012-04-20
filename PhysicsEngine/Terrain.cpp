
#pragma once

#include "LinearAlgebra.h"
#include "Terrain.h"
#include "Constants.h"

namespace PhysicsEngine
{

	Terrain::Terrain( const int iCellsNumber, const real iCellSize, const real iMaxHeight ) :
		RigidBody(),
		mCellSize( iCellSize )
	{
		// Initialize with values between -1 and 1
		mVertexes = matrixN::Random(iCellsNumber,iCellsNumber);
		// Linear mapping to get values between 0 and iMaxHeight
		mVertexes = (mVertexes + matrixN::Constant(iCellsNumber,iCellsNumber,1)) * iMaxHeight;
		mInverseMass = 0.0f;
		mMaxHeight = iMaxHeight;
		mCellsNumber = iCellsNumber;
	}

	int Terrain::getType()
	{
		return RIGID_BODY_TYPE_TERRAIN;
	}

}