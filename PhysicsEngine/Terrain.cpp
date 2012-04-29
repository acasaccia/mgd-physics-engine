
#pragma once

#include "LinearAlgebra.h"
#include "Terrain.h"

namespace PhysicsEngine
{

	Terrain::Terrain( const unsigned int iSquaresNumber, const real iSquareSize, const real iMaxHeight ) :
		RigidBody(),
		mSquareSize( iSquareSize )
	{
		// Initialize with values between -1 and 1
		mVertexes = matrixN::Random(iSquaresNumber,iSquaresNumber);
		// Linear mapping to get values between 0 and iMaxHeight
		mVertexes = (mVertexes + matrixN::Constant(iSquaresNumber,iSquaresNumber,1)) / 2 * iMaxHeight;
		mInverseMass = 0.0f;
		mMaxHeight = iMaxHeight;
		mSquaresNumber = iSquaresNumber;
		mFieldSize = (iSquaresNumber - 1) * iSquareSize;
	}

	int Terrain::getType()
	{
		return RIGID_BODY_TYPE_TERRAIN;
	}

	real* Terrain::getVertexPosition( const int iColumn, const int iRow, real* const iPosition) const
	{
		iPosition[0] = mFieldSize/2 - iRow*mSquareSize;
		iPosition[1] = mVertexes(iRow, iColumn);
		iPosition[2] = iColumn*mSquareSize - mFieldSize/2;
		return iPosition;
	}

	int* Terrain::getTesselationIndexes( const int iColumn, const int iRow, int* const iTesselation) const
	{
		// @toodo: implement me
		iTesselation[0] = 1;
		iTesselation[1] = 2;
		iTesselation[2] = 3;
		iTesselation[3] = 4;
		iTesselation[4] = 5;
		iTesselation[5] = 6;
		return iTesselation;
	}

	std::pair<int,Triangle*> Terrain::getTrianglesAroundVertex( int iX, int iY, Triangle* neighboursTriangle )
	{
		int collisorsCount = 0;
		
		real fieldSize = mSquareSize * mSquaresNumber;
		real halfFieldsize = fieldSize / 2;

		for (int r = iX-1; r<=iX+1; r++) {
			for (int c = iY-1; c<=iY+1; c++) {

				if (r>=0 && c>=0 && r<mVertexes.rows()-1 && c<mVertexes.cols()-1)
				{
					neighboursTriangle[collisorsCount] = Triangle(
						vector3( halfFieldsize - (r * mSquareSize), mVertexes(r,c), c * mSquareSize - halfFieldsize ),
						vector3( halfFieldsize - (r+1) * mSquareSize, mVertexes(r+1,c), c * mSquareSize - halfFieldsize ),
						vector3( halfFieldsize - (r+1) * mSquareSize, mVertexes(r+1,c+1), (c+1) * mSquareSize - halfFieldsize )
					);

					collisorsCount++;

					neighboursTriangle[collisorsCount] = Triangle(
						vector3( halfFieldsize - r * mSquareSize, mVertexes(r,c), c * mSquareSize - halfFieldsize ),
						vector3( halfFieldsize - (r+1) * mSquareSize, mVertexes(r+1,c+1), (c+1) * mSquareSize - halfFieldsize ),
						vector3( halfFieldsize - r * mSquareSize, mVertexes(r,c+1), (c+1) * mSquareSize - halfFieldsize )
					);

					collisorsCount++;
				}

			}
		}
		
		return std::pair<int,Triangle*>(collisorsCount, neighboursTriangle);
	}

}