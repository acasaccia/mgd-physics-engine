/*! 
 *  Linear algebra library for the engine.
 *  We wrap http://eigen.tuxfamily.org/index.php?title=Main_Page for matrix calculation.
 *  -
 *  Implementation of a simple physics engine, Physics Programming course
 *  Master in Computer Game Developement, Verona, Italy
 *  -
 *  \author Andrea Casaccia
 *  \date 23 March 2012
 */

#pragma once

#include "Eigen\Core"
#include "Eigen\Geometry"
#include "Eigen\StdVector"
#include <cfloat>
#include <cmath>

#if 1

    /*!
     * Defines we're in single precision mode, for any code
     * that needs to be conditionally compiled.
     */
    #define PHYSICS_ENGINE_SINGLE_PRECISION

    /*!
     * Defines a real number precision. PhxEngine can be compiled in
     * single or double precision versions. By default single precision is
     * provided.
     */
    typedef float real;

    /*! Defines the highest value for the real number. */
    #define REAL_MAX	FLT_MAX

    /*! Defines the precision of the square root operator. */
    #define real_sqrt	sqrtf
    /*! Defines the precision of the absolute magnitude operator. */
    #define real_abs	fabsf
    /*! Defines the precision of the sine operator. */
    #define real_sin	sinf

    /*! Defines the precision of the cosine operator. */
    #define real_cos	cosf

    /*! Defines the precision of the exponent operator. */
    #define real_exp	expf
    /*! Defines the precision of the power operator. */
    #define real_pow	powf

    /*! Defines the precision of the floating point modulo operator. */
    #define real_fmod	fmodf

    #define PI			3.14159f

	typedef Eigen::Vector3f vector3;
	typedef Eigen::Quaternionf quaternion;
	typedef Eigen::Matrix4f matrix4;
	typedef Eigen::Matrix3f matrix3;
	typedef Eigen::MatrixXf matrixN;

#else

    #define PHYSICS_ENGINE_DOUBLE_PRECISION

    typedef double real;

    #define REAL_MAX	DBL_MAX
    #define real_sqrt	sqrt
    #define real_abs	fabs
    #define real_sin	sin
    #define real_cos	cos
    #define real_exp	exp
    #define real_pow	pow
    #define real_fmod	fmod
    #define R_PI		3.14159265358979

	typedef Eigen::Vector3d vector3;
	typedef Eigen::Quaterniond quaternion;
	typedef Eigen::Matrix4d matrix4;
	typedef Eigen::Matrix3d matrix3;
	typedef Eigen::MatrixXd matrixN;

#endif
