#include "World/World.h"
#include "SV_Matte.h"

SV_Matte::SV_Matte()
	: Material{}
	, ambient_brdf{new SV_Lambertian}
	, diffuse_brdf{new SV_Lambertian}
{}

SV_Matte::SV_Matte(SV_Matte const & other)
	: Material{other}
{
	if (other.ambient_brdf)
		ambient_brdf.reset(static_cast<SV_Lambertian *>(other.ambient_brdf->clone()));
	else
		ambient_brdf.reset();

	if (other.diffuse_brdf)
		diffuse_brdf.reset(static_cast<SV_Lambertian *>(other.diffuse_brdf->clone()));
	else
		diffuse_brdf.reset();
}

void SV_Matte::set_ka(float const k) {
	ambient_brdf->set_kd(k);  // \note this sets Lambertian::kd for ambient light, there is no Lambertian::ka data member
}

void SV_Matte::set_kd(float const k) {
	diffuse_brdf->set_kd(k);
}

void SV_Matte::set_cd(Texture const * t) {
	ambient_brdf->set_cd(t);
	diffuse_brdf->set_cd(t);
}

RGBColor SV_Matte::shade(ShadeRec & sr) {
	Vector3D const wo = -sr.ray.d;
	RGBColor L = ambient_brdf->rho(sr, wo) * sr.w.ambient_ptr->L(sr);

	int const num_lights = sr.w.lights.size();
	for (int j = 0; j < num_lights; ++j) {
		Light * light_ptr = sr.w.lights[j];
		Vector3D wi = light_ptr->get_direction(sr);
		wi.normalize();
		float const ndotwi = sr.normal * wi,
			ndotwo = sr.normal * wo;

		if (ndotwi > 0.0 && ndotwo > 0) {
			bool in_shadow = false;
			if (light_ptr->casts_shadows()) {
				Ray shadow_ray{sr.hit_point, wi};
				in_shadow = light_ptr->in_shadow(shadow_ray, sr);
			}

			if (!in_shadow)
				L += diffuse_brdf->f(sr, wo, wi) * light_ptr->L(sr) * light_ptr->G(sr) * ndotwi;
		}
	}

	return L;
}

RGBColor SV_Matte::area_light_shade(ShadeRec & sr) {
	Vector3D const wo = -sr.ray.d;
	RGBColor L = ambient_brdf->rho(sr, wo) * sr.w.ambient_ptr->L(sr);

	int const num_lights = sr.w.lights.size();
	for (int j = 0; j < num_lights; ++j) {
		Light * const light_ptr = sr.w.lights[j];
		Vector3D wi = light_ptr->get_direction(sr);
		wi.normalize();
		float const ndotwi = sr.normal * wi,
			ndotwo = sr.normal * wo;

		if (ndotwi > 0.0 && ndotwo > 0) {
			bool in_shadow = false;
			if (light_ptr->casts_shadows()) {
				Ray shadow_ray{sr.hit_point, wi};
				in_shadow = light_ptr->in_shadow(shadow_ray, sr);
			}

			if (!in_shadow)
				L += diffuse_brdf->f(sr, wo, wi) * light_ptr->L(sr) * light_ptr->G(sr) * ndotwi / light_ptr->pdf(sr);
		}
	}

	return L;
}

SV_Matte * SV_Matte::clone() const {
	return new SV_Matte{*this};
}
