#include <stdexcept>
#include "Directional.h"
#include "Utilities/exception.hpp"

using std::logic_error;

// ---------------------------------------------------------------------- default constructor

Directional::Directional(void)
	: 	Light(),
		ls(1.0),
		color(1.0),
		dir(0, 1, 0)			
{}


// ---------------------------------------------------------------------- clone

Light* 
Directional::clone(void) const {
	return (new Directional(*this));
}


// ---------------------------------------------------------------------- assignment operator

Directional& 
Directional::operator= (const Directional& rhs) 	
{
	if (this == &rhs)
		return (*this);
			
	Light::operator= (rhs);
	
	ls		= rhs.ls;
	color 	= rhs.color;
	dir 	= rhs.dir;

	return (*this);
}

// ---------------------------------------------------------------------- get_direction
// as this function is virtual, it shouldn't be inlined 

Vector3D								
Directional::get_direction(ShadeRec& sr) {
	return (dir);
}	

// ------------------------------------------------------------------------------  L

RGBColor
Directional::L(ShadeRec& s) {	
	return (ls * color);
}

float Directional::G(ShadeRec const & sr) const {
	return 1.0;  // just return default value there
}

bool Directional::in_shadow(Ray const & ray, ShadeRec const & sr) const {
	if (_shadows) {
		for (GeometricObject * g : sr.w.objects) {
			if (double t; g->shadow_hit(ray, t))
				return true;
		}

		return false;
	}
	else
		return false;  // shadows off
}

float Directional::pdf(ShadeRec const & sr) const {
	return 1.0f;
}
