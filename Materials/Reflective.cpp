// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include "World/World.h"
#include "Reflective.h"

using std::make_unique;

Reflective::Reflective()
	: reflective_brdf{make_unique<PerfectSpecular>()}
{}

Reflective::Reflective(const Reflective& rm)
	: Phong(rm)
	, reflective_brdf{rm.reflective_brdf->clone()}
{}

Reflective& 
Reflective::operator= (const Reflective& rhs) {
	if (this == &rhs)
		return (*this);
		
	Phong::operator=(rhs);
	reflective_brdf.reset(rhs.reflective_brdf->clone());
	return *this;
}

Reflective * Reflective::clone() const {
	return new Reflective{*this};
}	

// ------------------------------------------------------------------------------------ shade 

RGBColor
Reflective::shade(ShadeRec& sr) const {
	RGBColor L(Phong::shade(sr));  // direct illumination
	
	Vector3D wo = -sr.ray.d;
	Vector3D wi;	
	RGBColor fr = reflective_brdf->sample_f(sr, wo, wi); 
	Ray reflected_ray(sr.hit_point, wi); 
	reflected_ray.depth = sr.depth + 1;
	
	L += fr * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1) * (sr.normal * wi);
					
	return (L);
}

RGBColor Reflective::area_light_shade(ShadeRec & sr) const {
	// FIXME: shade() copy-paste, find out proper implementation (pdf should be somehow used there)
	RGBColor L(Phong::shade(sr));  // direct illumination

	Vector3D wo = -sr.ray.d;
	Vector3D wi;
	RGBColor fr = reflective_brdf->sample_f(sr, wo, wi);
	Ray reflected_ray(sr.hit_point, wi);
	reflected_ray.depth = sr.depth + 1;

	L += fr * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1) * (sr.normal * wi);

	return L;
}

RGBColor Reflective::path_shade(ShadeRec & sr) const {
	Vector3D	wo = -sr.ray.d;
	Vector3D	wi;
	float pdf;
	RGBColor	fr = reflective_brdf->sample_f(sr, wo, wi, pdf);
	Ray reflected_ray(sr.hit_point, wi);

	return (fr * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1) * (sr.normal * wi) / pdf);
}
