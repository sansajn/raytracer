#include "Light.h"
#include "Samplers/Sampler.h"

class AmbientOccluder: public Light {
public:
	AmbientOccluder();
	void set_sampler(Sampler * s_ptr);
	Vector3D get_direction(ShadeRec & sr) override;
	bool in_shadow(Ray const & ray, ShadeRec const & sr) const override;
	RGBColor L(ShadeRec & sr) override;

private:
	float		ls;
	RGBColor	color;
	float 		min_amount;
	Vector3D 	u, v, w;
	Sampler * sampler_ptr;  // TODO: unique_ptr
};
