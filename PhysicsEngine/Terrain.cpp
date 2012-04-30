
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

	real* Terrain::getVertex3DPosition( const int iColumn, const int iRow, real* const iPosition) const
	{
		iPosition[0] = mFieldSize/2 - iRow*mSquareSize;
		iPosition[1] = mVertexes(iRow, iColumn);
		iPosition[2] = iColumn*mSquareSize - mFieldSize/2;
		return iPosition;
	}

	int* Terrain::getTessellationIndexes( const int iColumn, const int iRow, int* const iIndexes) const
	{
		// @todo: implement me
		iIndexes[0] = iRow;
		iIndexes[1] = iColumn;

		iIndexes[2] = iRow + 1;
		iIndexes[3] = iColumn;

		iIndexes[4] = iRow;
		iIndexes[5] = iColumn + 1;

		iIndexes[6] = iRow;
		iIndexes[7] = iColumn + 1;

		iIndexes[8] = iRow + 1;
		iIndexes[9] = iColumn;

		iIndexes[10] = iRow + 1;
		iIndexes[11] = iColumn + 1;

		return iIndexes;
	}

	std::pair<int,Triangle*> Terrain::getTrianglesAroundVertex( int iX, int iY, Triangle* neighboursTriangle )
	{
		int collisorsCount = 0;
		int tessellationIndexes[12];

		for (int r = iX-1; r<=iX+1; r++) {
			for (int c = iY-1; c<=iY+1; c++) {

				if (r>=0 && c>=0 && r<mSquaresNumber-1 && c<mSquaresNumber-1)
				{
					getTessellationIndexes(r,c,tessellationIndexes);

					neighboursTriangle[collisorsCount] = Triangle(
						vector3( getVertex3DPosition(tessellationIndexes[0], tessellationIndexes[1]) ),
						vector3( getVertex3DPosition(tessellationIndexes[2], tessellationIndexes[3]) ),
						vector3( getVertex3DPosition(tessellationIndexes[4], tessellationIndexes[5]) )
					);

					collisorsCount++;

					neighboursTriangle[collisorsCount] = Triangle(
						vector3( getVertex3DPosition(tessellationIndexes[6], tessellationIndexes[7]) ),
						vector3( getVertex3DPosition(tessellationIndexes[8], tessellationIndexes[9]) ),
						vector3( getVertex3DPosition(tessellationIndexes[10], tessellationIndexes[11]) )
					);

					collisorsCount++;
				}

			}
		}
		
		return std::pair<int,Triangle*>(collisorsCount, neighboursTriangle);
	}

}