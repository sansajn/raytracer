#pragma once
#include <memory>
#include "Textures/Texture.h"
#include "Material.h"
#include "BRDFs/SV_Lambertian.h"

//! A simple textured (spatially varying) material.
class SV_Matte : public Material {
public:
	SV_Matte();
	SV_Matte(float ka, float kd, Texture const * t);

	RGBColor shade(ShadeRec & sr) const override;
	RGBColor area_light_shade(ShadeRec & sr) const override;

	void set_ka(float const k);
	void set_kd(float const k);
	void set_cd(Texture const * t);  // TODO: use shared_ptr for texture

	SV_Matte * clone() const override;

	SV_Matte(SV_Matte const & other);

private:
	std::unique_ptr<SV_Lambertian> ambient_brdf,
		diffuse_brdf;
};
