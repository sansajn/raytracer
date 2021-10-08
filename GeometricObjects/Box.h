#pragma once
#include "GeometricObjects/GeometricObject.h"

//! Axis aligned box
class Box : public GeometricObject {
public:
	double x0, x1, y0, y1, z0, z1;

	Box();
	Box(Point3D const & min_corner, Point3D const & max_corner);
	bool hit(Ray const & ray, double & tmin, ShadeRec & sr) const override;
	bool shadow_hit(Ray const & ray, double & tmin) const override;
	Normal get_normal(const int face_hit) const;
	BBox get_bounding_box() override;

	Box * clone() const override;

	Box(Box const & other);

private:
	static const double kEpsilon;
};
