#include "OpenCylinder.h"
#include "SolidCylinder.h"
#include "Disk.h"

SolidCylinder::SolidCylinder() {
	add_object(new Disk(	Point3D(0, -1, 0), 			// bottom
									Normal(0, -1, 0),
									1));

	add_object(new Disk(	Point3D(0, 1, 0), 			// top
									Normal(0, 1, 0),
									1));

	add_object(new OpenCylinder(-1, 1, 1));	// wall

	bbox.x0 = -1;
	bbox.y0 = -1;
	bbox.z0 = -1;
	bbox.x1 = 1;
	bbox.y1 = 1;
	bbox.z1 = 1;
}

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

void SolidCylinder::set_bottom_material(std::shared_ptr<Material> m) {
	objects[0]->set_material(m);
}

void SolidCylinder::set_top_material(std::shared_ptr<Material> m) {
	objects[1]->set_material(m);
}

void SolidCylinder::set_wall_material(std::shared_ptr<Material> m) {
	objects[2]->set_material(m);
}
