#pragma once

#include <ostream>
#include "Vector3D.h"
#include "Point3D.h"
#include "Ray.h"
#include "RGBColor.h"

inline std::ostream & operator<<(std::ostream & out, Vector3D const & v) {
	out << "(" << v.x << ", " << v.y << ", " << v.z << ")";
	return out;
}

inline std::ostream & operator<<(std::ostream & out, Point3D const & p) {
	out << "(" << p.x << ", " << p.y << ", " << p.z << ")";
	return out;
}

inline std::ostream & operator<<(std::ostream & out, Ray const & p) {
	out << "{o:" << p.o << ", d:" << p.d << "}\n";
	return out;
}

inline std::ostream & operator<<(std::ostream & out, RGBColor const & c) {
	out << "(" << c.r << ", " << c.g << ", " << c.b << ")\n";
	return out;
}
