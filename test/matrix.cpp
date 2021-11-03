// Matrix related unit tests
#include <iostream>
#include <catch.hpp>
#include "Utilities/Matrix.h"
#include "Utilities/Vector3D.h"
#include "Utilities/Constants.h"
#include "Utilities/math_disp.hpp"
#include "approx.hpp"

TEST_CASE("we can translate vector by matrix multiplication", "[Matrix]") {
	Vector3D const expected = {1, 2, 3};

	Matrix T = {
		1, 0, 0, 1,  // xx, xy, xz, xw
		0, 1, 0, 2,  // yx, yy, yz, yw
		0, 0, 1, 3};  // zx, zy, zz, zw
	Vector3D v = {0, 0, 0};

	REQUIRE(T*v == expected);

	Matrix T2 = {
		{1, 0, 0},  // x
		{0, 1, 0},  // y
		{0, 0, 1},  // z
		{1, 2, 3}   // p
	};

	REQUIRE(T2*v == expected);
}

TEST_CASE("we can compose translate transformation with translate function", "[Matrix]") {
	Vector3D const expected = {1,2,3};

	Matrix I;
	Matrix T = translate(I, {1,2,3});

	Vector3D p0 = {0,0,0};
	Vector3D p1 = T*p0;
	REQUIRE(p1 == expected);
}

TEST_CASE("Vector3D can be approximaetd in REQUIRE checks", "[approx_vec3]") {
	Vector3D a = {1,2,3},
		b = {4,5,6};

	approx_vec3{a};
	approx_vec3{a} == b;
	b == approx_vec3{a};

	REQUIRE(approx_vec3{a} == a);
	REQUIRE(a == approx_vec3{a});
	REQUIRE_FALSE(a == b);
	REQUIRE_FALSE(approx_vec3{a} == b);
}

TEST_CASE("we can rotate vector by matrix multiplication",
	"[Matrix][rotation]") {

	SECTION("around x-axis") {
		Vector3D const expected = {0,0,1};

		Matrix R = eulerAngleX(PI<double>/2.0);   // positive rotation is counter-clockwise

		Vector3D p0 = {0,1,0};
		Vector3D p1 = R*p0;

		REQUIRE(approx_vec3{p1} == expected);
	}

	SECTION("around y-axis") {
		Vector3D const expected = {0,0,-1};

		Matrix R = eulerAngleY(PI<double>/2.0);   // positive rotation is counter-clockwise

		Vector3D p0 = {1,0,0};
		Vector3D p1 = R*p0;

		REQUIRE(approx_vec3{p1} == expected);
	}

	SECTION("around z-axis") {
		Vector3D const expected = {0,1,0};

		Matrix R = eulerAngleZ(PI<double>/2.0);   // positive rotation is counter-clockwise

		Vector3D p0 = {1,0,0};
		Vector3D p1 = R*p0;

		REQUIRE(approx_vec3{p1} == expected);
	}
}

TEST_CASE("we can compose matrix transformations", "[Matrix]") {
	Vector3D const expected = {0,0,0};

	Vector3D p0 = {1,0,0};

	// rotate -> translate
	Matrix I;
	Matrix T = rotateZ(I, PI<double>/2.0);
	T = translate(T, Vector3D{0,-1,0});

	Vector3D p1 = T*p0;

	REQUIRE(approx_vec3{p1} == expected);
}
