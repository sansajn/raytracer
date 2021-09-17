#pragma once
#include "GeometricObjects/GeometricObject.h"

//! Axis aligned box
class Box : public GeometricObject {
public:
	double x0, x1, y0, y1, z0, z1;

	bool hit(Ray const & ray, double & tmin, ShadeRec & sr) const override;
	Normal get_normal(const int face_hit) const;

private:
	static const double kEpsilon;
};
