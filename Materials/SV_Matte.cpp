#include "World/World.h"
#include "SV_Matte.h"

SV_Matte::SV_Matte()
	: Material{}
	, ambient_brdf{new SV_Lambertian}
	, diffuse_brdf{new SV_Lambertian}
{}

SV_Matte::SV_Matte(float ka, float kd, Texture const * t)
	: SV_Matte{}
{
	set_ka(ka);
	set_kd(kd);
	set_cd(t);  // FIXME: memory leak, SV_Lambertian doesn't own texture (SV_Mate should)
}

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

RGBColor SV_Matte::shade(ShadeRec & sr) const {
	Vector3D const wo = -sr.ray.d;
	RGBColor L = ambient_brdf->rho(sr, wo) * sr.w.ambient_ptr->L(sr);

	for (Light * light : sr.w.lights) {
		Vector3D wi = light->get_direction(sr);
		wi.normalize();
		float const ndotwi = sr.normal * wi,
			ndotwo = sr.normal * wo;

		if (ndotwi > 0 && ndotwo > 0) {
			bool in_shadow = false;
			if (light->casts_shadows()) {
				Ray shadow_ray{sr.hit_point, wi};
				in_shadow = light->in_shadow(shadow_ray, sr);
			}

			// listing 29.5 also calls light->G(sr) to produce final light L value, but I think that
			// G() function should be called only in area_light_shade() to support area lights and
			// not there.
			if (!in_shadow)
				L += diffuse_brdf->f(sr, wo, wi) * light->L(sr) * ndotwi;
		}
	}

	return L;
}

RGBColor SV_Matte::area_light_shade(ShadeRec & sr) const {
	Vector3D const wo = -sr.ray.d;
	RGBColor L = ambient_brdf->rho(sr, wo) * sr.w.ambient_ptr->L(sr);

	for (Light * light : sr.w.lights) {
		Vector3D wi = light->get_direction(sr);
		wi.normalize();
		float const ndotwi = sr.normal * wi,
			ndotwo = sr.normal * wo;

		if (ndotwi > 0.0 && ndotwo > 0) {
			bool in_shadow = false;
			if (light->casts_shadows()) {
				Ray shadow_ray{sr.hit_point, wi};
				in_shadow = light->in_shadow(shadow_ray, sr);
			}

			if (!in_shadow)
				L += diffuse_brdf->f(sr, wo, wi) * light->L(sr) * light->G(sr) * ndotwi / light->pdf(sr);
		}
	}

	return L;
}

SV_Matte * SV_Matte::clone() const {
	return new SV_Matte{*this};
}
