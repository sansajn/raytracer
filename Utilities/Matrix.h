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
	

	Matrix(void);									// default constructor

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

	Matrix(Vector3D const & x, Vector3D const & y, Vector3D const & z, Vector3D const & p = {0,0,0});

	Matrix& 										// assignment operator
	operator= (const Matrix& rhs);

	Matrix 											// multiplication of two matrices
	operator* (const Matrix& mat) const;

	Matrix 											// divsion by a double
	operator/ (const double d);

	void											// set to the identity matrix
	set_identity(void);
};

Matrix transpose(Matrix const & m);

#endif
