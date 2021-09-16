#include <string>
#include <stdexcept>
#include "Light.h"
#include "Constants.h"

using std::logic_error;
using namespace std::string_literals;

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
	throw logic_error{"not implemented, the default implemenation of '"s + __PRETTY_FUNCTION__ + "' is not ment to be called"};
}

float Light::G(ShadeRec const &) const {
	return 1.0;
}

float Light::pdf(ShadeRec const &) const {
	throw logic_error{"not implemented, the default implemenation of '"s + __PRETTY_FUNCTION__ + "' is not ment to be called"};
}
