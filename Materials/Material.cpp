#include <string>
#include <stdexcept>
#include "Material.h"

using std::logic_error;
using namespace std::string_literals;

Material & Material::operator=(Material const & rhs) {
	if (this == &rhs)
		return (*this);

	return *this;
}

RGBColor Material::shade(ShadeRec &) {
	throw logic_error{"not implemented, the default implemenation of '"s + __PRETTY_FUNCTION__ + "' is not ment to be called"};
}

RGBColor Material::area_light_shade(ShadeRec &) {
	throw logic_error{"not implemented, the default implemenation of '"s + __PRETTY_FUNCTION__ + "' is not ment to be called"};
}

RGBColor Material::get_Le(ShadeRec const &) const {
	return black;
}
