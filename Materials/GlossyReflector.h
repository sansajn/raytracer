#pragma once
#include "Phong.h"

class GlossyReflector : public Phong
{
public:
	GlossyReflector();
	GlossyReflector(const GlossyReflector& re);
	GlossyReflector& operator=(const GlossyReflector& rhs);

	GlossyReflector * clone() const override;

	void set_sampler(Sampler * sp, const float exp);
	void set_samples(const int numSamples, const float exp);
	void set_kr(const float k);
	void set_cr(const RGBColor r);
	void set_cr(const float r, const float g, const float b);
	void set_cr(const float c);
	void set_exponent(const float exp);

	RGBColor area_light_shade(ShadeRec& sr) const override;

private:
	std::shared_ptr<GlossySpecular> _glossy_specular_BRDF;
};
