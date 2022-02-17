#include "World/World.h"
#include "Matte.h"

// ---------------------------------------------------------------- default constructor

Matte::Matte()
	:	Material(),
		ambient_brdf(new Lambertian),
		diffuse_brdf(new Lambertian)
{}

Matte::Matte(float ka, float kd, RGBColor const & cd)
	: Matte{}
{
	set_ka(ka);
	set_kd(kd);
	set_cd(cd);
}

// ---------------------------------------------------------------- copy constructor

Matte::Matte(const Matte& m)
	: 	Material(m)
{
	if(m.ambient_brdf)
		ambient_brdf = m.ambient_brdf->clone(); 
	else  ambient_brdf = NULL;
	
	if(m.diffuse_brdf)
		diffuse_brdf = m.diffuse_brdf->clone(); 
	else  diffuse_brdf = NULL;
}


// ---------------------------------------------------------------- clone

Material*										
Matte::clone(void) const {
	return (new Matte(*this));
}	


// ---------------------------------------------------------------- assignment operator

Matte& 
Matte::operator= (const Matte& rhs) {
	if (this == &rhs)
		return (*this);
		
	Material::operator=(rhs);
	
	if (ambient_brdf) {
		delete ambient_brdf;
		ambient_brdf = NULL;
	}

	if (rhs.ambient_brdf)
		ambient_brdf = rhs.ambient_brdf->clone();
		
	if (diffuse_brdf) {
		delete diffuse_brdf;
		diffuse_brdf = NULL;
	}

	if (rhs.diffuse_brdf)
		diffuse_brdf = rhs.diffuse_brdf->clone();

	return (*this);
}


// ---------------------------------------------------------------- destructor

Matte::~Matte(void) {

	if (ambient_brdf) {
		delete ambient_brdf;
		ambient_brdf = NULL;
	}
	
	if (diffuse_brdf) {
		delete diffuse_brdf;
		diffuse_brdf = NULL;
	}
}


// ---------------------------------------------------------------- shade

RGBColor
Matte::shade(ShadeRec& sr) const {
	Vector3D 	wo 			= -sr.ray.d;
	RGBColor 	L 			= ambient_brdf->rho(sr, wo) * sr.w.ambient_ptr->L(sr);
	
	for (Light * light : sr.w.lights) {
		Vector3D wi = light->get_direction(sr);
		float ndotwi = sr.normal * wi,
			ndotwo = sr.normal * wo;
	
		if (ndotwi > 0.0 && ndotwo > 0) {
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
		float ndotwi = sr.normal * wi,
			ndotwo = sr.normal * wo;

		if (ndotwi > 0.0 && ndotwo > 0) {
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
