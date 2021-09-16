#pragma once
#include <memory>
#include "Textures/Texture.h"
#include "Material.h"
#include "BRDFs/SV_Lambertian.h"

//! A simple textured (spatially varying) material.
class SV_Matte : public Material {
public:
	SV_Matte();

	RGBColor shade(ShadeRec & sr) override;
	RGBColor area_light_shade(ShadeRec & sr) override;

	void set_ka(float const k);
	void set_kd(float const k);
	void set_cd(Texture const * t);

	SV_Matte * clone() const override;

	SV_Matte(SV_Matte const & other);

private:
	std::unique_ptr<SV_Lambertian> ambient_brdf,
		diffuse_brdf;
};
