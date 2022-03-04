#include <cassert>
#include "World/World.h"
#include "Matte.h"

using std::make_unique, std::move;

Matte::Matte()
	: ambient_brdf{make_unique<Lambertian>()}
	, diffuse_brdf{make_unique<Lambertian>()}
{}

Matte::Matte(float ka, float kd, RGBColor const & cd)
	: Matte{} {

	set_ka(ka);
	set_kd(kd);
	set_cd(cd);
}

Matte::Matte(const Matte& m)
	: 	Material(m)
	, ambient_brdf{m.ambient_brdf->clone()}
	, diffuse_brdf{m.diffuse_brdf->clone()} {

	assert(ambient_brdf && diffuse_brdf);
}

Material * Matte::clone() const {
	return (new Matte(*this));
}	

Matte & Matte::operator=(Matte const & rhs) {
	if (this == &rhs)
		return *this;
		
	Material::operator=(rhs);

	assert(rhs.ambient_brdf && rhs.diffuse_brdf);

	ambient_brdf.reset(rhs.ambient_brdf->clone());
	diffuse_brdf.reset(rhs.diffuse_brdf->clone());
	
	return *this;
}

RGBColor Matte::shade(ShadeRec & sr) const {
	Vector3D 	wo 			= -sr.ray.d;
	RGBColor 	L 			= ambient_brdf->rho(sr, wo) * sr.w.ambient_ptr->L(sr);
	
	for (Light * light : sr.w.lights) {
		Vector3D wi = light->get_direction(sr);
		float ndotwi = sr.normal * wi;
	
		if (ndotwi > 0.0) {
			bool in_shadow = false;
			if (light->casts_shadows()) {
				Ray shadow_ray{sr.hit_point, wi};
				in_shadow = light->in_shadow(shadow_ray, sr);
			}

			if (!in_shadow)
				L += diffuse_brdf->f(sr, wo, wi) * light->L(sr) * ndotwi;
		}
	}
	
	return L;
}

RGBColor Matte::area_light_shade(ShadeRec & sr) const {
	Vector3D wo = -sr.ray.d;
	RGBColor L = ambient_brdf->rho(sr, wo) * sr.w.ambient_ptr->L(sr);

	for (Light * light : sr.w.lights) {
		Vector3D wi = light->get_direction(sr);
		float const ndotwi = sr.normal * wi;

		if (ndotwi > 0.0) {
			bool in_shadow = false;

			if (light->casts_shadows()) {
				Ray shadow_ray(sr.hit_point, wi);
				in_shadow = light->in_shadow(shadow_ray, sr);
			}

			if (!in_shadow)
				L += diffuse_brdf->f(sr, wo, wi) * light->L(sr) * light->G(sr) * ndotwi / light->pdf(sr);
		}
	}

	return L;
}
