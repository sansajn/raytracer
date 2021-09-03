#include <cassert>
#include "Utilities/Constants.h"
#include "SV_Lambertian.h"

SV_Lambertian::SV_Lambertian()
	: kd{0}
	, cd{nullptr}
{}

void SV_Lambertian::set_cd(Texture const * t) {
	cd = t;  // TODO: check ownership
}

RGBColor SV_Lambertian::rho(ShadeRec const & sr, Vector3D const & wo) const {
	assert(cd);
	return kd * cd->get_color(sr);
}

RGBColor SV_Lambertian::f(ShadeRec const & sr, Vector3D const & wo, Vector3D const & wi) const {
	assert(cd);
	return kd * cd->get_color(sr) * invPI;
}

RGBColor SV_Lambertian::sample_f(ShadeRec const & sr, Vector3D const & wo, Vector3D & wi) const {
	// TODO: implement
}
