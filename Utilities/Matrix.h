#ifndef __MATRIX__
#define __MATRIX__

// this file contains the declaration of the class Matrix
// Matrix is a 4 x 4 square matrix that is used to represent affine transformations
// we don't need a general m x n matrix

#include "Vector3D.h"

//----------------------------------------- class Matrix

// TODO: replace Matrix with glm implementation

class Matrix {
	
public:
	
	double	m[4][4];								// elements
	

	Matrix();

	Matrix(const Matrix& mat);						// copy constructor

	Matrix(
		double xx, double xy, double xz, double px,
		double yx, double yy, double yz, double py,
		double zx, double zy, double zz, double pz);

	Matrix(
		double xx, double xy, double xz, double xw,
		double yx, double yy, double yz, double yw,
		double zx, double zy, double zz, double zw,
		double wx, double wy, double wz, double ww);

	/*! param[in] p origin position */
	Matrix(Vector3D const & x, Vector3D const & y, Vector3D const & z, Vector3D const & p = {0,0,0});

	Matrix& 										// assignment operator
	operator= (const Matrix& rhs);

	Matrix 											// multiplication of two matrices
	operator* (const Matrix& mat) const;

	Matrix 											// divsion by a double
	operator/ (const double d);

	void set_identity();
};

/*! \defgroup matt Matrix transformations
Matrix transformations.
\note Angles are in radians.
\{ */

Matrix transpose(Matrix const & m);
Matrix translate(Matrix const & M, Vector3D const & v);

Matrix rotateX(Matrix const & M, double angle_r);
Matrix rotateY(Matrix const & M, double angle_r);
Matrix rotateZ(Matrix const & M, double angle_r);

Matrix eulerAngleX(double angle_r);
Matrix eulerAngleY(double angle_r);
Matrix eulerAngleZ(double angle_r);

/*! \} */

#endif
