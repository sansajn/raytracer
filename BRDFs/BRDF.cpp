// This file contians the definition of the class BRDF
#include "Constants.h"
#include "Utilities/exception.hpp"
#include "BRDF.h"

RGBColor
BRDF::f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const {
//	return black;
	throw default_implementation{__PRETTY_FUNCTION__};
}

RGBColor BRDF::sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi) const {
//	return black;
	throw default_implementation{__PRETTY_FUNCTION__};
}

RGBColor BRDF::sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const {
//	return black;
	throw default_implementation{__PRETTY_FUNCTION__};
}

RGBColor
BRDF::rho(const ShadeRec& sr, const Vector3D& wo) const {
//	return black;
	throw default_implementation{__PRETTY_FUNCTION__};
}

