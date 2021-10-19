// Matrix related unit tests
#include <iostream>
#include <catch.hpp>
#include "Utilities/Matrix.h"
#include "Utilities/Vector3D.h"

TEST_CASE("we can translate vector by matrix multiplication", "[Matrix]") {
	Vector3D const expected = {1, 2, 3};

	Matrix T = {
		1, 0, 0, 1,
		0, 1, 0, 2,
		0, 0, 1, 3};
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
