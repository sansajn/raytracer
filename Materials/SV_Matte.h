#pragma once
#include <memory>
#include "Textures/Texture.h"
#include "Material.h"
#include "BRDFs/SV_Lambertian.h"

//! A simple textured (spatially varying) material.
class SV_Matte : public Material {
public:
	SV_Matte();
	SV_Matte(SV_Matte const & other);
	void set_ka(float const k);
	void set_kd(float const k);
	void set_cd(Texture const * t);
	RGBColor shade(ShadeRec & sr) override;

	~SV_Matte() = default;
	Material * clone() const override;

private:
	std::unique_ptr<SV_Lambertian> ambient_brdf,  // TODO: netreba implementovat aj SV_Light?
		diffuse_brdf;
};
