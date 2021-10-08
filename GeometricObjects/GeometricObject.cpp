// this file contains the definition of the class GeometricObject 

#include <string>
#include <stdexcept>
#include "Constants.h"
#include "Material.h"
#include "Utilities/exception.hpp"
#include "GeometricObject.h"

// ---------------------------------------------------------------------- default constructor


GeometricObject::GeometricObject(void)
	: material_ptr(NULL)
{}


// ---------------------------------------------------------------------- copy constructor

GeometricObject::GeometricObject (const GeometricObject& object) {
	if(object.material_ptr)
		material_ptr = object.material_ptr->clone(); 
	else  material_ptr = NULL;
}	


// ---------------------------------------------------------------------- assignment operator

GeometricObject&														
GeometricObject::operator= (const GeometricObject& rhs) {
	if (this == &rhs)
		return (*this);
			
	if (material_ptr) {
		delete material_ptr;
		material_ptr = NULL;
	}

	if (rhs.material_ptr)
		material_ptr = rhs.material_ptr->clone();

	return (*this);
}


// ---------------------------------------------------------------------- destructor

GeometricObject::~GeometricObject (void) {	
	if (material_ptr) {
		delete material_ptr;
		material_ptr = NULL;
	}
}


// ---------------------------------------------------------------- set_material

Material * GeometricObject::get_material() const {
	return material_ptr;
}

void 
GeometricObject::set_material(Material* mPtr) {
	material_ptr = mPtr;
}

RGBColor const & GeometricObject::get_color() const {
	return color;
}

void GeometricObject::set_color(RGBColor const & c) {
	color = c;
}

void GeometricObject::set_color(float r, float g, float b) {
	color = {r, g, b};
}

void GeometricObject::set_sampler(std::shared_ptr<Sampler>) {
	throw default_implementation{__PRETTY_FUNCTION__};
}

Point3D GeometricObject::sample() {
	throw default_implementation{__PRETTY_FUNCTION__};
}

Normal GeometricObject::get_normal(Point3D const &) {
	throw default_implementation{__PRETTY_FUNCTION__};
}

float GeometricObject::pdf(ShadeRec const &) const {
	throw default_implementation{__PRETTY_FUNCTION__};
}

BBox GeometricObject::get_bounding_box() {
	throw default_implementation{__PRETTY_FUNCTION__};
}

void GeometricObject::add_object(GeometricObject *) {
	throw default_implementation{__PRETTY_FUNCTION__};
}

Normal GeometricObject::get_normal() const {
	throw default_implementation{__PRETTY_FUNCTION__};
}
