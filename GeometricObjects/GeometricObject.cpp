// this file contains the definition of the class GeometricObject 

#include "Constants.h"
#include "Material.h"
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
