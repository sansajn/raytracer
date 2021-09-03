#include "SV_Matte.h"

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
		Vector3D wi = light_ptr->compute_direction(sr);
		wi.normalize();
		float const ndotwi = sr.normal * wi,
			ndotwo = sr.normal * wo;

		if (ndotwi > 0.0 && ndotwo > 0) {
			bool in_shadow = false;
			if (light_ptr->casts_shadows()) {
				Ray shadow_ray{sr.hit_point, wi};
				in_shadow = light_ptr->in_shadow(shadow_ray, sr.w.objects);
			}

			if (!in_shadow)
				L += diffuse_brdf->f(sr, wo, wi) * light_ptr->L(sr) * light_ptr->G(sr) * ndotwi;
		}
	}

	return L;
}
