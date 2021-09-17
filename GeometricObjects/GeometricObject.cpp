// this file contains the definition of the class GeometricObject 

#include <string>
#include <stdexcept>
#include "Constants.h"
#include "Material.h"
#include "GeometricObject.h"

using std::logic_error;
using namespace std::string_literals;

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
	throw logic_error{"not implemented, the default implemenation of '"s + __PRETTY_FUNCTION__ + "' is not ment to be called"};
}

Point3D GeometricObject::sample() {
	throw logic_error{"not implemented, the default implemenation of '"s + __PRETTY_FUNCTION__ + "' is not ment to be called"};
}

Normal GeometricObject::get_normal(Point3D const &) {
	throw logic_error{"not implemented, the default implemenation of '"s + __PRETTY_FUNCTION__ + "' is not ment to be called"};
}

float GeometricObject::pdf(ShadeRec const &) const {
	throw logic_error{"not implemented, the default implemenation of '"s + __PRETTY_FUNCTION__ + "' is not ment to be called"};
}

BBox GeometricObject::get_bounding_box() {
	throw logic_error{"not implemented, the default implemenation of '"s + __PRETTY_FUNCTION__ + "' is not ment to be called"};
}

void GeometricObject::add_object(GeometricObject *) {
	throw logic_error{"not implemented, the default implemenation of '"s + __PRETTY_FUNCTION__ + "' is not ment to be called"};
}

Normal GeometricObject::get_normal() const {
	throw logic_error{"not implemented, the default implemenation of '"s + __PRETTY_FUNCTION__ + "' is not ment to be called"};
}
