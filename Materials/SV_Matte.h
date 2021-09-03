#pragma once
#include "Textures/Texture.h"
#include "Material.h"
#include "BRDFs/SV_Lambertian.h"

//! A simple textured (spatially varying) material.
class SV_Matte : public Material {
public:
	void set_cd(Texture const * t);
	RGBColor shade(ShadeRec & sr) override;

private:
	SV_Lambertian * ambient_brdf,
		* diffuse_brdf;
};
