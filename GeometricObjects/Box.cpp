#include <stdexcept>
#include <boost/format.hpp>
#include "Box.h"

using std::logic_error;
using boost::format, boost::str;

const double Box::kEpsilon = 0.001;

Box::Box()
	: x0{-1}, x1{1}, y0{-1}, y1{1}, z0{-1}, z1{1}
{}

Box::Box(Point3D const & min_corner, Point3D const & max_corner)
	: x0{min_corner.x}, x1{max_corner.x}, y0{min_corner.y}, y1{max_corner.y}, z0{min_corner.z}, z1{max_corner.z}
{}

bool Box::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
	double ox = ray.o.x,
		oy = ray.o.y,
		oz = ray.o.z,
		dx = ray.d.x,
		dy = ray.d.y,
		dz = ray.d.z,
		tx_min, ty_min, tz_min,
		tx_max, ty_max, tz_max;

	double a = 1.0 / dx;
	if (a >= 0) {
		tx_min = (x0 - ox) * a;
		tx_max = (x1 - ox) * a;
	}
	else {
		tx_min = (x1 - ox) * a;
		tx_max = (x0 - ox) * a;
	}

	double b = 1.0 / dy;
	if (b >= 0) {
		ty_min = (y0 - oy) * b;
		ty_max = (y1 - oy) * b;
	}
	else {
		ty_min = (y1 - oy) * b;
		ty_max = (y0 - oy) * b;
	}

	double c = 1.0 / dz;
	if (c >= 0) {
		tz_min = (z0 - oz) * c;
		tz_max = (z1 - oz) * c;
	}
	else {
		tz_min = (z1 - oz) * c;
		tz_max = (z0 - oz) * c;
	}

	double t0, t1;

	int face_in, face_out;

	// find largest entering t value

	if (tx_min > ty_min) {
		t0 = tx_min;
		face_in = (a >= 0.0) ? 0 : 3;
	}
	else {
		t0 = ty_min;
		face_in = (b >= 0.0) ? 1 : 4;
	}

	if (tz_min > t0) {
		t0 = tz_min;
		face_in = (c >= 0.0) ? 2 : 5;
	}

	// find smallest exiting t value

	if (tx_max < ty_max) {
		t1 = tx_max;
		face_out = (a >= 0.0) ? 3 : 0;
	}
	else {
		t1 = ty_max;
		face_out = (b >= 0.0) ? 4 : 1;
	}

	if (tz_max < t1) {
		t1 = tz_max;
		face_out = (c >= 0.0) ? 5 : 2;
	}

	if (t0 < t1 && t1 > kEpsilon) {  // condition for a hit
		if (t0 > kEpsilon) {
			tmin = t0;  			// ray hits outside surface
			sr.normal = get_normal(face_in);
		}
		else {
			tmin = t1;				// ray hits inside surface
			sr.normal = get_normal(face_out);
		}

		sr.local_hit_point = ray.o + tmin * ray.d;
		return (true);
	}
	else
		return (false);
}

bool Box::shadow_hit(Ray const & ray, double & tmin) const {
	if (!casts_shadows())
		return false;

	double ox = ray.o.x,
		oy = ray.o.y,
		oz = ray.o.z,
		dx = ray.d.x,
		dy = ray.d.y,
		dz = ray.d.z,
		tx_min, ty_min, tz_min,
		tx_max, ty_max, tz_max;

	double a = 1.0 / dx;
	if (a >= 0) {
		tx_min = (x0 - ox) * a;
		tx_max = (x1 - ox) * a;
	}
	else {
		tx_min = (x1 - ox) * a;
		tx_max = (x0 - ox) * a;
	}

	double b = 1.0 / dy;
	if (b >= 0) {
		ty_min = (y0 - oy) * b;
		ty_max = (y1 - oy) * b;
	}
	else {
		ty_min = (y1 - oy) * b;
		ty_max = (y0 - oy) * b;
	}

	double c = 1.0 / dz;
	if (c >= 0) {
		tz_min = (z0 - oz) * c;
		tz_max = (z1 - oz) * c;
	}
	else {
		tz_min = (z1 - oz) * c;
		tz_max = (z0 - oz) * c;
	}

	double t0, t1;

	int face_in, face_out;

	// find largest entering t value

	if (tx_min > ty_min) {
		t0 = tx_min;
		face_in = (a >= 0.0) ? 0 : 3;
	}
	else {
		t0 = ty_min;
		face_in = (b >= 0.0) ? 1 : 4;
	}

	if (tz_min > t0) {
		t0 = tz_min;
		face_in = (c >= 0.0) ? 2 : 5;
	}

	// find smallest exiting t value

	if (tx_max < ty_max) {
		t1 = tx_max;
		face_out = (a >= 0.0) ? 3 : 0;
	}
	else {
		t1 = ty_max;
		face_out = (b >= 0.0) ? 4 : 1;
	}

	if (tz_max < t1) {
		t1 = tz_max;
		face_out = (c >= 0.0) ? 5 : 2;
	}

	if (t0 < t1 && t1 > kEpsilon) {  // condition for a hit
		if (t0 > kEpsilon)
			tmin = t0;  			// ray hits outside surface
		else
			tmin = t1;				// ray hits inside surface

		return (true);
	}
	else
		return (false);
}

Normal Box::get_normal(const int face_hit) const {
	switch (face_hit) {
		case 0:	return (Normal(-1, 0, 0));	// -x face
		case 1:	return (Normal(0, -1, 0));	// -y face
		case 2:	return (Normal(0, 0, -1));	// -z face
		case 3:	return (Normal(1, 0, 0));	// +x face
		case 4:	return (Normal(0, 1, 0));	// +y face
		case 5:	return (Normal(0, 0, 1));	// +z face
		default:
			throw logic_error{str(format("box has only six faces not %1%") % (face_hit+1))};
	}
}

BBox Box::get_bounding_box() {
	return BBox{x0, x1, y0, y1, z0, z1};
}

Box * Box::clone() const {
	return new Box{*this};
}

Box::Box(Box const & other)
	: GeometricObject{other}
	, x0{other.x0}, x1{other.x1}, y0{other.y0}, y1{other.y1}, z0{other.z0}, z1{other.z1}
{}
