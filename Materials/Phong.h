#pragma once
#include <memory>
#include "Material.h"
#include "BRDFs/Lambertian.h"
#include "BRDFs/GlossySpecular.h"

class Phong : public Material {
public:
	Phong();

	RGBColor shade(ShadeRec & sr) override;

	void set_ka(float ka);
	void set_kd(float kd);
	void set_cd(RGBColor const & c);
	void set_ks(float ks);
	void set_exp(float exp);

	Phong * clone() const override;
	Phong(Phong const & other);
	Phong & operator=(Phong const & other);

private:
	std::unique_ptr<Lambertian> ambient_brdf,
		diffuse_brdf;
	std::unique_ptr<GlossySpecular> specular_brdf;
};
