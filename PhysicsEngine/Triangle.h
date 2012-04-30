/*! 
 *  Represents a 3D triangle
 *  -
 *  Implementation of a simple physics engine, Physics Programming course
 *  Master in Computer Game Developement, Verona, Italy
 *  -
 *  \author Andrea Casaccia
 *  \date 23 March 2012
 */

#pragma once

#include "LinearAlgebra.h"

class Triangle
{
public:
	vector3 mVertexes[3];
	Triangle();
	Triangle( vector3, vector3, vector3 );
	static vector3 normal( const vector3&, const vector3& );
	static vector3 closestPointToPoint( const vector3&, const vector3&, const vector3&, const vector3& );
};