#include "Light.h"

#include "Constants.h"

// ---------------------------------------------------------------------- default constructor

Light::Light(void)
	: _shadows{false}
{}

// ---------------------------------------------------------------------- dopy constructor

Light::Light(const Light& ls)
	: _shadows{ls._shadows}
{}


// ---------------------------------------------------------------------- assignment operator

Light& 
Light::operator= (const Light& rhs) {
	if (this == &rhs)
		return (*this);

	_shadows = rhs._shadows;

	return (*this);
}


// ---------------------------------------------------------------------- destructor

Light::~Light(void) {} 

bool Light::casts_shadows() const {
	return _shadows;
}

void Light::set_shadows(bool shadows) {
	_shadows = shadows;
}

bool Light::in_shadow(Ray const & ray, ShadeRec const & sr) const {
	return false;
}


// ---------------------------------------------------------------------- L
// returns the radiance

RGBColor								
Light::L(ShadeRec &) {
	return (black);
}

float Light::G(ShadeRec &) const {
	return 1.0;
}


