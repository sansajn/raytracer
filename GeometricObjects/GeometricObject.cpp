// this file contains the definition of the class GeometricObject 

#include <string>
#include <stdexcept>
#include "Constants.h"
#include "Material.h"
#include "Utilities/exception.hpp"
#include "GeometricObject.h"

using std::shared_ptr, std::unique_ptr;

GeometricObject::GeometricObject()
	: _shadows{true}
{}

// ---------------------------------------------------------------------- assignment operator

GeometricObject&														
GeometricObject::operator= (const GeometricObject& rhs) {
	if (this == &rhs)
		return (*this);
			
	material_ptr = rhs.material_ptr;
	_shadows = rhs._shadows;
	color = rhs.color;

	return (*this);
}

// ---------------------------------------------------------------- set_material


bool GeometricObject::casts_shadows() const {
	return _shadows;
}

void GeometricObject::set_shadows(bool shadows) {
	_shadows = shadows;
}

Material const * GeometricObject::get_material() const {
	return material_ptr.get();
}

void GeometricObject::get_material(std::shared_ptr<Material> & m) const {
	m = material_ptr;
}

void 
GeometricObject::set_material(shared_ptr<Material> mPtr) {
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

void GeometricObject::set_sampler(unique_ptr<Sampler>) {
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
