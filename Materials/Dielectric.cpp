// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include "Dielectric.h"
#include "World/World.h"

using std::make_unique;

Dielectric::Dielectric()
	: fresnel_brdf{make_unique<FresnelReflector>()}
	, fresnel_btdf{make_unique<FresnelTransmitter>()}
	, shadows{true}
{}

Dielectric::Dielectric(const Dielectric& m)
	: Phong{m}
	, fresnel_brdf{m.fresnel_brdf->clone()}
	, fresnel_btdf{m.fresnel_btdf->clone()}
	, shadows{m.shadows}
{}

Dielectric * Dielectric::clone() const {
	return (new Dielectric(*this));
}	

Dielectric & Dielectric::operator=(const Dielectric& rhs) {
	if (this == &rhs)
		return (*this);
		
	Phong::operator=(rhs);

	fresnel_brdf.reset(rhs.fresnel_brdf->clone());
	fresnel_btdf.reset(rhs.fresnel_btdf->clone());

	shadows = rhs.shadows;

	return (*this);
}


// --------------------------------------------------

RGBColor Dielectric::shade(ShadeRec& sr) const {
	RGBColor L(Phong::shade(sr));
		
	Vector3D 	wi;
	Vector3D 	wo(-sr.ray.d);
	RGBColor 	fr = fresnel_brdf->sample_f(sr, wo, wi);  	// computes wi
	Ray 		reflected_ray(sr.hit_point, wi); 
	double 		t;
	RGBColor 	Lr, Lt;
	float 		ndotwi =  sr.normal * wi;
		
	if(fresnel_btdf->tir(sr)) {								// total internal reflection
		if (ndotwi < 0.0) {  	
			// reflected ray is inside
			
			Lr = sr.w.tracer_ptr->trace_ray(reflected_ray, t, sr.depth + 1);
			L += cf_in.powc(t) * Lr;   						// inside filter color
		}
		else {				
			// reflected ray is outside
			
			Lr = sr.w.tracer_ptr->trace_ray(reflected_ray, t, sr.depth + 1);   // kr = 1  
			L += cf_out.powc(t) * Lr;   					// outside filter color
		}
	}
	else { 													// no total internal reflection
		Vector3D wt;
		RGBColor ft = fresnel_btdf->sample_f(sr, wo, wt);  	// computes wt
		Ray transmitted_ray(sr.hit_point, wt);
		float ndotwt = sr.normal * wt;
							
		if (ndotwi < 0.0) {
			// reflected ray is inside
						
			Lr = fr * sr.w.tracer_ptr->trace_ray(reflected_ray, t, sr.depth + 1) * fabs(ndotwi);
			L += cf_in.powc(t) * Lr;     					// inside filter color
				
			// transmitted ray is outside
							
			Lt = ft * sr.w.tracer_ptr->trace_ray(transmitted_ray, t, sr.depth + 1) * fabs(ndotwt); 
			L += cf_out.powc(t) * Lt;   					// outside filter color
		}
		else {				
			// reflected ray is outside

			Lr = fr * sr.w.tracer_ptr->trace_ray(reflected_ray, t, sr.depth + 1) * fabs(ndotwi); 
			L += cf_out.powc(t) * Lr;						// outside filter color
				
			// transmitted ray is inside
			
			Lt = ft * sr.w.tracer_ptr->trace_ray(transmitted_ray, t, sr.depth + 1) * fabs(ndotwt); 
			L += cf_in.powc(t) * Lt; 						// inside filter color
		}		
	}	
	
	return (L);
}  

//RGBColor
//Dielectric::area_light_shade(ShadeRec& sr)			//this is for chapter 18 page one image ad-hoc
//{
//	Vector3D 	wo 			= -sr.ray.d;
//	RGBColor 	L 			= ambient_brdf->rho(sr, wo) * sr.w.ambient_ptr->L(sr);
//	int 		num_lights	= sr.w.lights.size();

//	for (int j = 0; j < num_lights; j++) {
//		Vector3D 	wi 		= sr.w.lights[j]->get_direction(sr);
//		float 		ndotwi 	= sr.normal * wi;

//		if (ndotwi > 0.0) {
//			bool in_shadow = false;

//			if (sr.w.lights[j]->casts_shadows()) {
//				Ray shadowRay(sr.hit_point, wi);
//				in_shadow = sr.w.lights[j]->in_shadow(shadowRay, sr);
//			}

//			if (!in_shadow)
//				L += (	diffuse_brdf->f(sr, wo, wi)
//						  + specular_brdf->f(sr, wo, wi)) * sr.w.lights[j]->L(sr) * ndotwi * sr.w.lights[j]->G(sr) / sr.w.lights[j]->pdf(sr);
//		}
//	}
//	return (L);
//}
