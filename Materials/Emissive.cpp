#include "Utilities/Constants.h"
#include "Emissive.h"

Emissive::Emissive()
	: ls{1.0}
{}

void Emissive::set_ce(RGBColor const & ce) {
	this->ce = ce;
}

void Emissive::scale_radiance(const float ls) {
	this->ls = ls;
}

RGBColor	Emissive::shade(ShadeRec & sr) {
	if (-sr.normal * sr.ray.d > 0.0)
		return (ls * ce);
	else
		return (black);
}

RGBColor Emissive::area_light_shade(ShadeRec& sr) {
	if (-sr.normal * sr.ray.d > 0.0)
		return (ls * ce);
	else
		return (black);
}

RGBColor	Emissive::get_Le(ShadeRec const &) const {
	return ls * ce;
}

Material * Emissive::clone() const {
	return new Emissive{*this};
}

Emissive::Emissive(Emissive const & other)
	: Material{other}
	, ls{other.ls}
	, ce{other.ce}
{}
