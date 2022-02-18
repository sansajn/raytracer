#pragma once
#include "GeometricObjects/Compound.h"

class SolidCylinder: public Compound {
public:
	SolidCylinder();
	SolidCylinder(const double bottom, const double top, const double radius);
	bool hit(Ray const & ray, double & tmin, ShadeRec & sr) const override;
	bool shadow_hit(Ray const & ray, double & tmin) const override;
	BBox get_bounding_box() override;
	void set_bottom_material(std::shared_ptr<Material> m);
	void set_top_material(std::shared_ptr<Material> m);
	void set_wall_material(std::shared_ptr<Material> m);

	// Copy API.
	SolidCylinder(const SolidCylinder& rhs);
	SolidCylinder * clone() const override;

private:
	BBox bbox;
};

