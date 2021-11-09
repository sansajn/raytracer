#include "OpenPartCylinder.h"

OpenPartCylinder::OpenPartCylinder()
	: _y0{-1.0}
	, _y1{1.0}
	, _radius{1.0}
	, _phi_min{0.0}
	, _phi_max{360.0}
	, _inv_radius{1.0}
{}

OpenPartCylinder::OpenPartCylinder(double bottom, double top, double radius, double phi_min, double phi_max)
	: _y0{bottom}
	, _y1{top}
	, _radius{radius}
	, _phi_min{phi_min}
	, _phi_max{phi_max}
	, _inv_radius{1.0 / radius}
{
	// TODO: computing bounding box can be improved there take phi_min/max into account
	_bbox = BBox{
		-radius, radius,
		bottom, top,
		-radius, radius};
}

bool OpenPartCylinder::hit(Ray const & ray, double & tmin, ShadeRec & sr) const {
	double t;
	double ox = ray.o.x;
	double oy = ray.o.y;
	double oz = ray.o.z;
	double dx = ray.d.x;
	double dy = ray.d.y;
	double dz = ray.d.z;

	double a = dx * dx + dz * dz;
	double b = 2.0 * (ox * dx + oz * dz);
	double c = ox * ox + oz * oz - _radius * _radius;
	double disc = b * b - 4.0 * a * c ;


	if (disc < 0.0)
		return false;
	else {
		double e = sqrt(disc);
		double denom = 2.0 * a;
		t = (-b - e) / denom;    // smaller root

		if (t > kEpsilon) {
			double yhit = oy + t * dy;

			if (yhit > _y0 && yhit < _y1) {
				tmin = t;

				// FIX:
				Point3D hit_point = ray.o + tmin * ray.d;

				double phi = atan2(hit_point.x, hit_point.z);
				if (phi < 0.0)
					phi += TWO_PI<double>;

				phi = degrees(phi);

				if (phi >= _phi_min && phi <= _phi_max) {
					sr.normal = Normal((ox + t * dx) * _inv_radius, 0.0, (oz + t * dz) * _inv_radius);

					// test for hitting from inside

					if (-ray.d * sr.normal < 0.0)
						sr.normal = -sr.normal;

					sr.local_hit_point = hit_point;

					return true;
				}
				else {
					int __i = 101;
				}
			}
		}

		t = (-b + e) / denom;    // larger root

		if (t > kEpsilon) {
			double yhit = oy + t * dy;

			if (yhit > _y0 && yhit < _y1) {
				tmin = t;

				Point3D hit_point = ray.o + tmin * ray.d;

				double phi = atan2(hit_point.x, hit_point.z);
				if (phi < 0.0)
					phi += TWO_PI<double>;

				phi = degrees(phi);

				if (phi >= _phi_min && phi <= _phi_max) {

					sr.normal = Normal((ox + t * dx) * _inv_radius, 0.0, (oz + t * dz) * _inv_radius);

					// test for hitting inside surface

					if (-ray.d * sr.normal < 0.0)
						sr.normal = -sr.normal;

					sr.local_hit_point = hit_point;

					return true;
				}
				else {
					int __i = 102;
				}
			}
		}
	}

	return false;
}

bool OpenPartCylinder::shadow_hit(Ray const & ray, double & tmin) const {
	double t;
	double ox = ray.o.x;
	double oy = ray.o.y;
	double oz = ray.o.z;
	double dx = ray.d.x;
	double dy = ray.d.y;
	double dz = ray.d.z;

	double a = dx * dx + dz * dz;
	double b = 2.0 * (ox * dx + oz * dz);
	double c = ox * ox + oz * oz - _radius * _radius;
	double disc = b * b - 4.0 * a * c ;


	if (disc < 0.0)
		return false;
	else {
		double e = sqrt(disc);
		double denom = 2.0 * a;
		t = (-b - e) / denom;    // smaller root

		if (t > kEpsilon) {
			double yhit = oy + t * dy;

			if (yhit > _y0 && yhit < _y1) {
				tmin = t;

				Point3D hit_point = ray.o + tmin * ray.d;

				double phi = atan2(hit_point.x, hit_point.z);
				if (phi < 0.0)
					phi += TWO_PI<double>;

				phi = degrees(phi);

				if (phi >= _phi_min && phi <= _phi_max)
					return true;
			}
		}

		t = (-b + e) / denom;    // larger root

		if (t > kEpsilon) {
			double yhit = oy + t * dy;

			if (yhit > _y0 && yhit < _y1) {
				tmin = t;

				Point3D hit_point = ray.o + tmin * ray.d;

				double phi = atan2(hit_point.x, hit_point.z);
				if (phi < 0.0)
					phi += TWO_PI<double>;

				phi = degrees(phi);

				if (phi >= _phi_min && phi <= _phi_max)
					return true;
			}
		}
	}

	return false;
}

BBox OpenPartCylinder::get_bounding_box() {
	return _bbox;
}

OpenPartCylinder::OpenPartCylinder(OpenPartCylinder const & rhs)
	: _y0{rhs._y0}
	, _y1{rhs._y1}
	, _radius{rhs._radius}
	, _phi_min{rhs._phi_min}
	, _phi_max{rhs._phi_max}
	, _inv_radius{rhs._inv_radius}
	, _bbox{rhs._bbox}
{}

OpenPartCylinder * OpenPartCylinder::clone() const {
	return new OpenPartCylinder{*this};
}
