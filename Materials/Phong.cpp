#include "World/World.h"
#include "Phong.h"

using std::make_unique;

Phong::Phong()
	: Material{}
	, ambient_brdf{make_unique<Lambertian>()}
	, diffuse_brdf{make_unique<Lambertian>()}
	, specular_brdf{make_unique<GlossySpecular>()}
{}

RGBColor Phong::shade(ShadeRec& sr) const {
	Vector3D 	wo 			= -sr.ray.d;
	RGBColor 	L 			= ambient_brdf->rho(sr, wo) * sr.w.ambient_ptr->L(sr);

	for (Light * light : sr.w.lights) {
		Vector3D wi = light->get_direction(sr);
		float const ndotwi = sr.normal * wi;

		if (ndotwi > 0.0) {
			bool in_shadow = false;
			if (light->casts_shadows()) {
				Ray shadow_ray{sr.hit_point, wi};
				in_shadow = light->in_shadow(shadow_ray, sr);
			}

			if (!in_shadow)
				L += (diffuse_brdf->f(sr, wo, wi) + specular_brdf->f(sr, wo, wi)) * light->L(sr) * ndotwi;
		}
	}

	return L;
}

RGBColor Phong::area_light_shade(ShadeRec & sr) const {
	Vector3D wo = -sr.ray.d;
	RGBColor L = ambient_brdf->rho(sr, wo) * sr.w.ambient_ptr->L(sr);

	for (Light * light : sr.w.lights) {
		Vector3D wi = light->get_direction(sr);
		float const ndotwi = sr.normal * wi;

		if (ndotwi > 0.0) {
			bool in_shadow = false;

			if (light->casts_shadows()) {
				Ray shadow_ray{sr.hit_point, wi};
				in_shadow = light->in_shadow(shadow_ray, sr);
			}

			if (!in_shadow)
				L += (diffuse_brdf->f(sr, wo, wi) + specular_brdf->f(sr, wo, wi)) * light->L(sr) * light->G(sr) * ndotwi / light->pdf(sr);
		}
	}

	return L;
}


void Phong::set_ka(float ka) {
	ambient_brdf->set_kd(ka);  // \note this sets Lambertian::kd for ambient light, there is no Lambertian::ka data member
}

void Phong::set_kd(float kd) {
	diffuse_brdf->set_kd(kd);
}

void Phong::set_cd(RGBColor const & c) {
	ambient_brdf->set_cd(c);
	diffuse_brdf->set_cd(c);
}

void Phong::set_ks(float ks) {
	specular_brdf->set_ks(ks);
}

void Phong::set_exp(float exp) {
	specular_brdf->set_exp(exp);
}

void Phong::set_cs(RGBColor const & cs) {
	specular_brdf->set_cs(cs);
}

Phong::Phong(Phong const & other)
	: Material{other}
{
	if (other.ambient_brdf)
		ambient_brdf.reset(other.ambient_brdf->clone());
	else
		ambient_brdf.reset();

	if (other.diffuse_brdf)
		diffuse_brdf.reset(other.diffuse_brdf->clone());
	else
		diffuse_brdf.reset();
}

Phong & Phong::operator=(Phong const & other) {
	if (this == &other)
		return *this;

	Material::operator=(other);

	if (other.ambient_brdf)
		ambient_brdf.reset(other.ambient_brdf->clone());
	else
		ambient_brdf.reset();

	if (other.diffuse_brdf)
		diffuse_brdf.reset(other.diffuse_brdf->clone());
	else
		diffuse_brdf.reset();

	return *this;
}

Phong * Phong::clone() const {
	return new Phong{*this};
}
