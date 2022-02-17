#include <cassert>
#include "Disk.h"

Disk::Disk()
	: _r{0}
	, _r_squared{0}
	, _inv_area{0}
{}

Disk::Disk(Point3D const & center, Normal const & normal, double radius)
	: _center{center}
	, _normal{normal}
	, _r{radius}
	, _r_squared{radius * radius}
	, _inv_area{1.0 / (PI<double> * _r_squared)}
{
	Vector3D w = _normal;
	_v = w ^ Vector3D{0.0072, 1.0, 0.0034};  // jitter the up vector in case normal is vertical
	_v.normalize();
	_u = _v ^ w;
}

bool Disk::hit(Ray const & ray, double & tmin, ShadeRec & sr) const {
	double t = (_center - ray.o) * _normal / (ray.d * _normal);
		
	if (t <= kEpsilon)
		return (false);
		
	Point3D p = ray.o + t * ray.d;
		
	if (_center.d_squared(p) < _r_squared) {
		tmin = t;
		sr.normal = _normal;
		sr.local_hit_point = p;
		return (true);	
	}
	else
		return (false);
}

bool Disk::shadow_hit(Ray const & ray, double & tmin) const {
	if (!casts_shadows())
		return false;

	double t = (_center - ray.o) * _normal / (ray.d * _normal);

	if (t <= kEpsilon)
		return false;

	Point3D p = ray.o + t * ray.d;

	if (_center.d_squared(p) < _r_squared) {
		tmin = t;
		return true;
	}
	else
		return false;
}

void Disk::set_sampler(std::unique_ptr<Sampler> s) {
	assert(s);
	_sampler = move(s);
	_sampler->map_samples_to_unit_disk();
}

Point3D Disk::sample() {
	Point2D sp = _sampler->sample_unit_disk();
	return _center + sp.x * _u + sp.y * _v;  // NOTE: just my guess how to calculate sampling point
}

Normal Disk::get_normal(Point3D const & p) {
	return _normal;
}

float Disk::pdf(ShadeRec const & sr) const {
	return _inv_area;
}

Disk::Disk(Disk const & rhs)
	: GeometricObject{rhs}
	, _center{rhs._center}
	, _normal{rhs._normal}
	, _r{rhs._r}
	, _r_squared{rhs._r_squared}
	, _inv_area{rhs._inv_area}
	, _u{rhs._u}
	, _v{rhs._v}
{
	if (rhs._sampler)
		_sampler.reset(rhs._sampler->clone());
}

Disk * Disk::clone() const {
	return new Disk{*this};
}
