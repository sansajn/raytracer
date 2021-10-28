// This is updated version of the code in Listing 21.9
#include "Disk.h"
#include "Instance.h"
#include "ConvexPartCylinder.h"
#include "Torus.h"
#include "BeveledCylinder.h"


BeveledCylinder::BeveledCylinder(double bottom, double top, double radius, double bevel_radius) {
	// construct the bottom, top, and curved surface
	
	objects.push_back(new Disk(Point3D(0, bottom, 0), Normal(0, -1, 0), r - br));  	// bottom
	objects.push_back(new Disk(Point3D(0, top, 0), Normal(0, 1, 0), r - br));   	// top
	objects.push_back(new ConvexPartCylinder(bottom + br, top - br, r));   		  	// curved surface
	
	// have to use instances for the tori because they have to be translated
	
	Instance* bottom_torus_ptr = new Instance(new Torus(r - br, br));
	bottom_torus_ptr->translate(0, bottom + br, 0);
	bottom_torus_ptr->transform_texture(false);        
	objects.push_back(bottom_torus_ptr);
	
	Instance* top_torus_ptr = new Instance(new Torus(r - br, br));
	top_torus_ptr->translate(0, top  - br, 0);
	top_torus_ptr->transform_texture(false);	
	objects.push_back(top_torus_ptr);

	_bbox = BBox{
		-radius, radius,
		bottom, top,
		-radius, radius};
}

bool BeveledCylinder::hit(Ray const & ray, double & tmin, ShadeRec & sr) const {
	if (!_bbox.hit(ray))
		return false;
	else
		return Compound::hit(ray, tmin, sr);
}

bool BeveledCylinder::shadow_hit(Ray const & ray, double & tmin) const {
	if (!_bbox.hit(ray))
		return false;
	else
		return Compound::shadow_hit(ray, tmin);
}

BBox BeveledCylinder::get_bounding_box() {
	return _bbox;
}

BeveledCylinder::BeveledCylinder(BeveledCylinder const & rhs)
	: Compound{rhs}
	, _bbox{rhs._bbox}
{}

BeveledCylinder * BeveledCylinder::clone() const {
	return new BeveledCylinder{*this};
}
