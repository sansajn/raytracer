// This file contains the declaration of the base class BRDF
#pragma once
#include <math.h>
#include "RGBColor.h"
#include "Vector3D.h"
#include "ShadeRec.h"

class BRDF {
public:
	BRDF() = default;
	BRDF(const BRDF& object) = default;

	virtual BRDF*
	clone(void) const = 0;

	virtual ~BRDF() = default;

	virtual RGBColor
	f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const;

	virtual RGBColor
	sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi) const;

	virtual RGBColor
	sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const;

	virtual RGBColor
	rho(const ShadeRec& sr, const Vector3D& wo) const;

protected:
	
	BRDF&	operator= (const BRDF& rhs) = default;
};
