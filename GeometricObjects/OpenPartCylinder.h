#pragma once
#include "GeometricObjects/GeometricObject.h"

class OpenPartCylinder : public GeometricObject {
public:
	OpenPartCylinder();
	OpenPartCylinder(double bottom, double top, double radius, double phi_min, double phi_max = 360.0);
	bool hit(Ray const & ray, double & tmin, ShadeRec & sr) const override;
	bool shadow_hit(Ray const & ray, double & tmin) const override;
	BBox get_bounding_box() override;
	OpenPartCylinder(OpenPartCylinder const & rhs);
	OpenPartCylinder * clone() const override;

private:
	double _y0,
		_y1,
		_radius,
		_phi_min,
		_phi_max,
		_inv_radius;
	BBox _bbox;
};
