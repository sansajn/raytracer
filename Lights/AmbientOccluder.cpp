#include <algorithm>
#include <cassert>
#include "World.h"
#include "GeometricObjects/GeometricObject.h"
#include "Constants.h"
#include "AmbientOccluder.h"

using std::any_of, std::unique_ptr, std::move;

AmbientOccluder::AmbientOccluder()
	: ls{1.0}
	, color{white}
	, min_amount{0.1}
{}

void AmbientOccluder::set_sampler(unique_ptr<Sampler> s) {
	assert(s);
	sampler_ptr = move(s);
	sampler_ptr->map_samples_to_hemisphere(1);
}

void AmbientOccluder::set_min_amount(float amount) {
	min_amount = amount;
}

void AmbientOccluder::scale_radiance(float k) {
	ls = k;
}

Vector3D AmbientOccluder::get_direction(ShadeRec &) {
	assert(sampler_ptr);
	Point3D sp = sampler_ptr->sample_hemisphere();
	return (sp.x * u + sp.y * v + sp.z * w);
}

bool AmbientOccluder::in_shadow(Ray const & ray, ShadeRec const & sr) const {
	return any_of(begin(sr.w.objects), end(sr.w.objects),
		[&ray](GeometricObject const * obj){
			double t;
			return obj->shadow_hit(ray, t);
	});
}

RGBColor AmbientOccluder::L(ShadeRec & sr) {
	w = sr.normal;
	v = w ^ Vector3D(0.0072, 1.0, 0.0034);  // jitter the up vector in case normal is vertical
	v.normalize();
	u = v ^ w;

	Ray shadow_ray;
	shadow_ray.o = sr.hit_point;
	shadow_ray.d = get_direction(sr);

	if (in_shadow(shadow_ray, sr))
		return (min_amount * ls * color);
	else
		return (ls * color);
}

AmbientOccluder * AmbientOccluder::clone() const {
	return new AmbientOccluder{*this};
}

AmbientOccluder::AmbientOccluder(AmbientOccluder const & rhs)
	: Light{rhs}
	, ls{rhs.ls}
	, color{rhs.color}
	, min_amount{rhs.min_amount}
	, u{rhs.u}, v{rhs.v}, w{rhs.w}
{
	if (rhs.sampler_ptr)
		sampler_ptr.reset(rhs.sampler_ptr->clone());
}
