#pragma once
#include "GeometricObject.h"

class Sphere: public GeometricObject {	
public:
	Sphere();
	Sphere(Point3D center, double r);

	void set_center(const Point3D& c);
	void set_radius(double r);
	bool hit(const Ray& ray, double& t, ShadeRec& s) const override;
	bool shadow_hit(Ray const & ray, double & tmin) const override;

	// Area Lights API
	void set_sampler(std::unique_ptr<Sampler> sampler) override;
	Point3D sample() override;
	Normal get_normal(Point3D const & p) override;
	float pdf(ShadeRec const & sr) const override;

	BBox get_bounding_box() override;

	// Copy API
	Sphere(Sphere const & rhs);
	Sphere &	operator=(const Sphere& sphere);
	Sphere *	clone() const override;

private:
	Point3D _center;
	double _radius,
		_inv_area;
	std::unique_ptr<Sampler> _sampler;

	static const double kEpsilon;   // for shadows and secondary rays
};
