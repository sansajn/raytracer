#include <string>
#include <stdexcept>
#include "Material.h"
#include "Utilities/exception.hpp"

using std::logic_error;
using namespace std::string_literals;

Material & Material::operator=(Material const & rhs) {
	if (this == &rhs)
		return (*this);

	return *this;
}

RGBColor Material::shade(ShadeRec &) const {
	throw default_implementation{__PRETTY_FUNCTION__};
}

RGBColor Material::area_light_shade(ShadeRec &) const {
	throw default_implementation{__PRETTY_FUNCTION__};
}

RGBColor Material::get_Le(ShadeRec const &) const {
	throw default_implementation{__PRETTY_FUNCTION__};
}
