#include <cassert>
#include "Lambertian.h"
#include "Constants.h"

// ---------------------------------------------------------------------- default constructor

Lambertian::Lambertian(void) 
	: kd(0.0)
	, cd(0.0)
{}


// ---------------------------------------------------------------------- copy constructor

Lambertian::Lambertian(const Lambertian& lamb) 
	:   BRDF(lamb),
		kd(lamb.kd), 
		cd(lamb.cd)
{
	if (lamb._sampler)
		_sampler.reset(lamb._sampler->clone());
}


// ---------------------------------------------------------------------- clone

Lambertian* 
Lambertian::clone(void) const {
	return (new Lambertian(*this));
}	

// ---------------------------------------------------------------------- assignment operator

Lambertian& 
Lambertian::operator= (const Lambertian& rhs) {
	if (this == &rhs)
		return (*this);
		
	BRDF::operator= (rhs);
	
	kd = rhs.kd; 
	cd = rhs.cd;

	if (rhs._sampler)
		_sampler.reset(rhs._sampler->clone());
	
	return (*this);
}


// ---------------------------------------------------------------------- f

RGBColor
Lambertian::f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const {
	return (kd * cd * invPI<float>);
}

RGBColor Lambertian::sample_f(ShadeRec const & sr, Vector3D const & wo, Vector3D & wi, float & pdf) const {
	assert(_sampler && "set_sampler() not called");

	Vector3D w = sr.normal;
	Vector3D v = Vector3D{0.0034, 1, 0.0071} ^ w;
	v.normalize();
	Vector3D u = v ^ w;

	Point3D sp = _sampler->sample_hemisphere();
	wi = sp.x*u + sp.y*v + sp.z*w;
	wi.normalize();
	pdf = sr.normal * wi * invPI<double>;

	return {kd * cd * invPI<double>};
}

// ---------------------------------------------------------------------- rho

RGBColor
Lambertian::rho(const ShadeRec& sr, const Vector3D& wo) const {
	return (kd * cd);
}

void Lambertian::set_sampler(std::unique_ptr<Sampler> s) {
	assert(s);
	_sampler = move(s);
	_sampler->map_samples_to_hemisphere(1);
}
