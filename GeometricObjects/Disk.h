#pragma once
#include "GeometricObjects/GeometricObject.h"

class Disk : public GeometricObject {
public:
	Disk();
	Disk(Point3D const & center, Normal const & normal, double radius);
	bool hit(Ray const & ray, double & tmin, ShadeRec & sr) const override;
	bool shadow_hit(Ray const & ray, double & tmin) const override;

	// Area Lights API
	void set_sampler(std::unique_ptr<Sampler> s) override;
	Point3D sample() override;
	Normal get_normal(Point3D const & p) override;
	float pdf(ShadeRec const & sr) const override;

	// Copy API.
	Disk(Disk const & rhs);
	Disk * clone() const override;

private:
	Point3D _center;
	Normal _normal;
	double _r,
		_r_squared,
		_inv_area;
	Vector3D _u, _v;  // to support sampling on disk
	std::unique_ptr<Sampler> _sampler;
};
