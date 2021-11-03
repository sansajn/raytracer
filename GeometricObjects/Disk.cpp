#include "Disk.h"

Disk::Disk()
	: r_squared{0}
{}

Disk::Disk(Point3D const & center, Normal const & normal, double radius)
	: center{center}
	, normal{normal}
	, r_squared{radius * radius}
{}

bool Disk::hit(Ray const & ray, double & tmin, ShadeRec & sr) const {
	double t = (center - ray.o) * normal / (ray.d * normal);
		
	if (t <= kEpsilon)
		return (false);
		
	Point3D p = ray.o + t * ray.d;
		
	if (center.d_squared(p) < r_squared) {
		tmin 				= t;
		sr.normal 			= normal;
		sr.local_hit_point	= p; 
		return (true);	
	}
	else
		return (false);
}

bool Disk::shadow_hit(Ray const & ray, double & tmin) const {
	double t = (center - ray.o) * normal / (ray.d * normal);

	if (t <= kEpsilon)
		return false;

	Point3D p = ray.o + t * ray.d;

	if (center.d_squared(p) < r_squared) {
		tmin = t;
		return true;
	}
	else
		return false;
}

Disk::Disk(Disk const & rhs)
	: center{rhs.center}
	, normal{rhs.normal}
	, r_squared{rhs.r_squared}
{}

Disk * Disk::clone() const {
	return new Disk{*this};
}
