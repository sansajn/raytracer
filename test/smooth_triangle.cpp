#include <catch.hpp>
#include "GeometricObjects/SmoothTriangle.h"


TEST_CASE("normals needs to be set explicitly", "[SmoothTriangle]") {
	// s algoritmu pre teselaciu gule
	Point3D const v0 = {0,1,0},
		v1 = {0,0,1},
		v2 = {0.8660254037844387, 0, -0.4999999999999998};

	SmoothTriangle t{v0, v1, v2};
	t.n0 = v0;
	t.n1 = v1;
	t.n2 = v2;
}
