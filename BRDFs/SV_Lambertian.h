#pragma once
#include <memory>
#include "BRDFs/BRDF.h"
#include "Textures/Texture.h"

//! Textured (spatially varying) lambertian (see Chapter 29).
class SV_Lambertian : public BRDF {
public:
	SV_Lambertian();
	void set_ka(float const k);
	void set_kd(float const k);
	void set_cd(Texture const * t);
	RGBColor rho(ShadeRec const & sr, Vector3D const & wo) const override;
	RGBColor f(ShadeRec const & sr, Vector3D const & wo, Vector3D const & wi) const override;
	RGBColor sample_f(ShadeRec const & sr, Vector3D const & wo, Vector3D & wi) const override;

	//! Copy API.
	SV_Lambertian(SV_Lambertian const & lamb);
	SV_Lambertian * clone() const override;

private:
	float kd;
	Texture const * cd;  // TODO: Find out who own texture, SV_Matte?
};
