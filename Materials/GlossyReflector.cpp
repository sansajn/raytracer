#include "World/World.h"
#include "GlossyReflector.h"

using std::make_shared;

GlossyReflector::GlossyReflector()
	: _glossy_specular_BRDF(std::make_shared<GlossySpecular>())
{}

GlossyReflector::GlossyReflector(const GlossyReflector& re)
	: Phong(re) {

	if (re._glossy_specular_BRDF)
		_glossy_specular_BRDF.reset(re._glossy_specular_BRDF->clone());
	else
		_glossy_specular_BRDF = make_shared<GlossySpecular>();
}

GlossyReflector& GlossyReflector::operator=(const GlossyReflector& rhs) {
	if (this == &rhs)
		return *this;

	Phong::operator=(rhs);

	_glossy_specular_BRDF = nullptr;

	if (rhs._glossy_specular_BRDF)
		_glossy_specular_BRDF = rhs._glossy_specular_BRDF;

	return *this;
}

GlossyReflector * GlossyReflector::clone() const {
	return new GlossyReflector{*this};
}

void GlossyReflector::set_sampler(Sampler * sp, const float exp) {
	_glossy_specular_BRDF->set_sampler(sp, exp);
}

void GlossyReflector::set_samples(const int numSamples, const float exp) {
	_glossy_specular_BRDF->set_samples(numSamples, exp);
}

void GlossyReflector::set_kr(const float k) {
	_glossy_specular_BRDF->set_ks(k);
}

void GlossyReflector::set_cr(const RGBColor r) {
	_glossy_specular_BRDF->set_cs(r);
}

void GlossyReflector::set_cr(const float r, const float g, const float b) {
	_glossy_specular_BRDF->set_cs(r, g, b);
}

void GlossyReflector::set_cr(const float c) {
	_glossy_specular_BRDF->set_cs(c);
}

void GlossyReflector::set_exponent(const float exp) {
	_glossy_specular_BRDF->set_exp(exp);
}

RGBColor GlossyReflector::area_light_shade(ShadeRec& sr) const {
	RGBColor L(Phong::area_light_shade(sr));
	Vector3D wo(-sr.ray.d);
	Vector3D wi;
	float pdf;
	RGBColor fr(_glossy_specular_BRDF->sample_f(sr, wo, wi, pdf));
	Ray reflectedRay(sr.hit_point, wi);

	L += fr * sr.w.tracer_ptr->trace_ray(reflectedRay, sr.depth + 1) *
		(sr.normal * wi) / pdf;

	return L;
}
