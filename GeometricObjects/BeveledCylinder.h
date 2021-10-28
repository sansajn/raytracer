#pragma once
#include "Compound.h"

class BeveledCylinder : public Compound {
public:
	BeveledCylinder() = default;
	BeveledCylinder(double bottom, double top, double radius, double bevel_radius);
	bool hit(Ray const & ray, double & tmin, ShadeRec & sr) const override;
	bool shadow_hit(Ray const & ray, double & tmin) const override;
	BBox get_bounding_box() override;
	BeveledCylinder(BeveledCylinder const & rhs);
	BeveledCylinder * clone() const override;

private:
	BBox _bbox;
};
