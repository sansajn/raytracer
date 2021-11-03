#pragma once
#include "GeometricObjects/GeometricObject.h"

class Disk : public GeometricObject {
public:
	Disk();
	Disk(Point3D const & center, Normal const & normal, double radius);

	bool hit(Ray const & ray, double & tmin, ShadeRec & sr) const override;
	bool shadow_hit(Ray const & ray, double & tmin) const override;

	Disk(Disk const & rhs);
	Disk * clone() const override;

private:
	Point3D center;
	Normal normal;
	double r_squared;
};
