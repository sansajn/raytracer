#include "Light.h"
#include "Constants.h"
#include "Utilities/exception.hpp"

// ---------------------------------------------------------------------- default constructor

Light::Light()
	: _shadows{false}
{}

Light& 
Light::operator= (const Light& rhs) {
	if (this == &rhs)
		return (*this);

	_shadows = rhs._shadows;

	return (*this);
}


// ---------------------------------------------------------------------- destructor

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
//	return black;
	throw default_implementation{__PRETTY_FUNCTION__};
}

float Light::G(ShadeRec const &) const {
//	return 1.0f;
	throw default_implementation{__PRETTY_FUNCTION__};
}

float Light::pdf(ShadeRec const &) const {
//	return 1.0f;
	throw default_implementation{__PRETTY_FUNCTION__};
}
