#include <algorithm>
#include <cassert>
#include "Utilities/Constants.h"
#include "GeometricObjects/GeometricObject.h"
#include "World/World.h"
#include "EnvironmentLight.h"

using std::any_of, std::unique_ptr;

void EnvironmentLight::set_sampler(unique_ptr<Sampler> s) {
	assert(s);
	_sampler = move(s);
	_sampler->map_samples_to_hemisphere(1);
}

void EnvironmentLight::set_material(std::shared_ptr<Material> m) {
	assert(m);
	_material = m;
}

Vector3D EnvironmentLight::get_direction(ShadeRec & sr) {
	_w = sr.normal;
	_v = Vector3D{0.0034, 1, 0.0071} ^ _w;
	_v.normalize();
	_u = _v ^ _w;
	Point3D sp = _sampler->sample_hemisphere();
	_wi = sp.x * _u + sp.y * _v + sp.z * _w;
	return _wi;
}

RGBColor EnvironmentLight::L(ShadeRec& sr) {
	return _material->get_Le(sr);
}

float EnvironmentLight::G(ShadeRec const & sr) const {
	return 1.0f;
}

bool EnvironmentLight::in_shadow(Ray const & ray, ShadeRec const & sr) const {
	return any_of(begin(sr.w.objects), end(sr.w.objects),
		[&ray](GeometricObject const * obj){
			double t;
			return obj->shadow_hit(ray, t);
	});
}

float EnvironmentLight::pdf(ShadeRec const & sr) const {
	return sr.normal * _wi * invPI<float>;
}

Light * EnvironmentLight::clone() const {
	return new EnvironmentLight{*this};
}

EnvironmentLight::EnvironmentLight(EnvironmentLight const & rhs)
	: Light{rhs}
	, _u{rhs._u}, _v{rhs._v}, _w{rhs._w}
	, _wi{rhs._wi}
	, _material{rhs._material}
{
	if (rhs._sampler)
		_sampler.reset(rhs._sampler->clone());
}
