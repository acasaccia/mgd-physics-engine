
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

	std::pair<int,Triangle*> Terrain::getNeighbourTriangles( int iX, int iY )
	{
		Triangle neighboursTriangle[18];
		int collisorsCount = 0;
		
		for (int r = iX-1; r<=iX+1; r++)
			for (int c = iY-1; c<=iY+1; c++)
				if (r>0 && c>0 && r<mVertexes.rows() && c<mVertexes.cols())
				{
					neighboursTriangle[collisorsCount] = Triangle(
						mVertexes(r,c),
						mVertexes(r+1,c),
						mVertexes(r+1,c+1)
					);

					collisorsCount++;

					neighboursTriangle[collisorsCount] = Triangle(
						mVertexes(r,c),
						mVertexes(r+1,c+1),
						mVertexes(r,c+1)
					);

					collisorsCount++;
				}
		
		return std::pair<int,Triangle*>(collisorsCount, neighboursTriangle);
	}

	Triangle::Triangle()
	{
		vertexes[0] = 0;
		vertexes[1] = 0;
		vertexes[2] = 0;
	}

	Triangle::Triangle( real iA, real iB, real iC )
	{
		vertexes[0] = iA;
		vertexes[1] = iB;
		vertexes[2] = iC;
	}

}