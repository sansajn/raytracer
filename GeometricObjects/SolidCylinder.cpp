#include "OpenCylinder.h"
#include "SolidCylinder.h"
#include "Disk.h"

SolidCylinder::SolidCylinder(const double bottom, const double top, const double radius)
	: Compound() {

	objects.push_back(new Disk(	Point3D(0, bottom, 0), 			// bottom
								Normal(0, -1, 0),
								radius));

	objects.push_back(new Disk(	Point3D(0, top, 0), 			// top
								Normal(0, 1, 0),
								radius));

	objects.push_back(new OpenCylinder(bottom, top, radius));	// wall

	bbox = BBox{
		-radius, radius,
		bottom, top,
		-radius, radius};
}

bool SolidCylinder::hit(Ray const & ray, double & tmin, ShadeRec & sr) const {
	if (bbox.hit(ray))
		return (Compound::hit(ray, tmin, sr));
	else
		return (false);
}

bool SolidCylinder::shadow_hit(Ray const & ray, double & tmin) const {
	if (!bbox.hit(ray))
		return false;
	else
		return Compound::shadow_hit(ray, tmin);
}

BBox SolidCylinder::get_bounding_box() {
	return bbox;
}

SolidCylinder::SolidCylinder(const SolidCylinder& cc)
	: Compound{cc}
	, bbox{cc.bbox}
{}

SolidCylinder * SolidCylinder::clone() const {
	return new SolidCylinder{*this};
}
