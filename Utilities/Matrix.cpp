// This file contains the definition of the class Matrix

#include <cmath>
#include "Matrix.h"

// ----------------------------------------------------------------------- default constructor
// a default matrix is an identity matrix

Matrix::Matrix(void) {	
	for (int x = 0; x < 4; x++)
		for (int y = 0; y < 4; y++) {
			if (x == y)
				m[x][y] = 1.0;
			else
				m[x][y] = 0.0;
		}
}


// ----------------------------------------------------------------------- copy constructor

Matrix::Matrix (const Matrix& mat) {
	for (int x = 0; x < 4; x++)				
		for (int y = 0; y < 4; y++)			
			m[x][y] = mat.m[x][y];	
}


// ----------------------------------------------------------------------- destructor

Matrix::Matrix(
	double xx, double xy, double xz, double px,
	double yx, double yy, double yz, double py,
	double zx, double zy, double zz, double pz)
{
	m[0][0] = xx; m[0][1] = xy; m[0][2] = xz;	m[0][3] = px;
	m[1][0] = yx; m[1][1] = yy; m[1][2] = yz; m[1][3] = py;
	m[2][0] = zx; m[2][1] = zy; m[2][2] = zz; m[2][3] = pz;
	m[3][0] = 0;  m[3][1] = 0;  m[3][2] = 0;  m[3][3] = 1;
}

Matrix::Matrix(
	double xx, double xy, double xz, double xw,
	double yx, double yy, double yz, double yw,
	double zx, double zy, double zz, double zw,
	double wx, double wy, double wz, double ww) {

	m[0][0] = xx; m[0][1] = xy; m[0][2] = xz;	m[0][3] = xw;
	m[1][0] = yx; m[1][1] = yy; m[1][2] = yz; m[1][3] = yw;
	m[2][0] = zx; m[2][1] = zy; m[2][2] = zz; m[2][3] = zw;
	m[3][0] = wx; m[3][1] = wy; m[3][2] = wz; m[3][3] = ww;
}

Matrix::Matrix(Vector3D const & x, Vector3D const & y, Vector3D const & z, Vector3D const & p) {
	m[0][0] = x.x; m[0][1] = x.y; m[0][2] = x.z;	m[0][3] = p.x;
	m[1][0] = y.x; m[1][1] = y.y; m[1][2] = y.z; m[1][3] = p.y;
	m[2][0] = z.x; m[2][1] = z.y; m[2][2] = z.z; m[2][3] = p.z;
	m[3][0] = 0;   m[3][1] = 0;   m[3][2] = 0;   m[3][3] =  1;
}

// ----------------------------------------------------------------------- assignment operator

Matrix& 
Matrix::operator= (const Matrix& rhs) {
	if (this == &rhs)
		return (*this);

	for (int x = 0; x < 4; x++)				
		for (int y = 0; y < 4; y++)			
			m[x][y] = rhs.m[x][y];	

	return (*this);
}


// ----------------------------------------------------------------------- operator*
// multiplication of two matrices

Matrix 
Matrix::operator* (const Matrix& mat) const {
	Matrix 	product;
	
	for (int y = 0; y < 4; y++)
		for (int x = 0; x < 4; x++) {
			double sum = 0.0;

			for (int j = 0; j < 4; j++)
				sum += m[x][j] * mat.m[j][y];
 
			product.m[x][y] = sum;			
		}
	
	return (product);
}


// ----------------------------------------------------------------------- operator/
// division by a scalar

Matrix 
Matrix::operator/ (const double d) {
	for (int x = 0; x < 4; x++)				
		for (int y = 0; y < 4; y++)			
			m[x][y] = m[x][y] / d;	

	return (*this);
}



// ----------------------------------------------------------------------- set_identity
// set matrix to the identity matrix

void											
Matrix::set_identity() {
    for (int x = 0; x < 4; x++)
		for (int y = 0; y < 4; y++) {
			if (x == y)
				m[x][y] = 1.0;
			else
				m[x][y] = 0.0;
		}
}

Matrix transpose(Matrix const & m) {
	return Matrix{
		m.m[0][0], m.m[1][0], m.m[2][0], m.m[3][0],
		m.m[0][1], m.m[1][1], m.m[2][1], m.m[3][1],
		m.m[0][2], m.m[1][2], m.m[2][2], m.m[3][2],
		m.m[0][3], m.m[1][3], m.m[2][3], m.m[3][3]
	};
}

Matrix translate(Matrix const & M, Vector3D const & v) {
	Matrix T{
		{1,0,0},
		{0,1,0},
		{0,0,1},
		v};

	return T*M;  // T=T_n*T_{n-1}*...T_1  (see equation 20.10)
}

Matrix rotateX(Matrix const & M, double angle_r) {
	Matrix R = eulerAngleX(angle_r);
	return R*M;
}

Matrix rotateY(Matrix const & M, double angle_r) {
	Matrix R = eulerAngleY(angle_r);
	return R*M;
}

Matrix rotateZ(Matrix const & M, double angle_r) {
	Matrix R = eulerAngleZ(angle_r);
	return R*M;
}

Matrix eulerAngleX(double angle_r) {
	double cos_angle = cos(angle_r),
		sin_angle = sin(angle_r);

	return {
		{1, 0, 0},  // x
		{0, cos_angle, -sin_angle},  // y
		{0, sin_angle, cos_angle}  // z
	};
}

Matrix eulerAngleY(double angle_r) {
	double cos_angle = cos(angle_r),
		sin_angle = sin(angle_r);

	return {
		{cos_angle, 0, sin_angle},  // x
		{0, 1, 0},  // y
		{-sin_angle, 0, cos_angle}  // z
	};
}

Matrix eulerAngleZ(double angle_r) {
	double cos_angle = cos(angle_r),
		sin_angle = sin(angle_r);

	return {
		{cos_angle, -sin_angle, 0},  // x
		{sin_angle, cos_angle, 0},  // y
		{0, 0, 1}  // z
	};
}


