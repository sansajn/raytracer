#pragma once
#include <memory>
#include "Samplers/Sampler.h"
#include "BRDF.h"

class Lambertian: public BRDF {
public:
	Lambertian(void);

	RGBColor f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const override;
	RGBColor sample_f(ShadeRec const & sr, Vector3D const & wo, Vector3D & wi, float & pdf) const override;
	RGBColor rho(const ShadeRec& sr, const Vector3D& wo) const override;

	void set_ka(const float ka);
	void set_kd(const float kd);
	void set_cd(const RGBColor& c);

	void set_sampler(std::unique_ptr<Sampler> s);

	// Copy API.
	Lambertian(const Lambertian& lamb);
	Lambertian & operator=(const Lambertian& rhs);
	Lambertian * clone() const override;

private:
	float	kd;
	RGBColor cd;
	std::unique_ptr<Sampler> _sampler;  //!< to support path tracing (see chapter 26)
};


// -------------------------------------------------------------- set_ka

inline void
Lambertian::set_ka(const float k) {
	kd = k;
}


// -------------------------------------------------------------- set_kd

inline void
Lambertian::set_kd(const float k) {
	kd = k;
}


// -------------------------------------------------------------- set_cd

inline void
Lambertian::set_cd(const RGBColor& c) {
	cd = c;
}
