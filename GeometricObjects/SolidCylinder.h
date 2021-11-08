#pragma once
#include "GeometricObjects/Compound.h"

class SolidCylinder: public Compound {
public:
	SolidCylinder();
	SolidCylinder(const double bottom, const double top, const double radius);
	bool hit(Ray const & ray, double & tmin, ShadeRec & sr) const override;
	bool shadow_hit(Ray const & ray, double & tmin) const override;
	BBox get_bounding_box() override;
	SolidCylinder(const SolidCylinder& rhs);
	SolidCylinder * clone() const override;

private:
	BBox bbox;
};

