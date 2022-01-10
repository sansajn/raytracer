#include <memory>
#include "Light.h"
#include "Samplers/Sampler.h"

//! \note based on listings from chapter 17
class AmbientOccluder: public Light {
public:
	AmbientOccluder();

	void set_sampler(std::unique_ptr<Sampler> s);
	void set_color(RGBColor const & c);
	void set_min_amount(float amount);
	void scale_radiance(float k);
	Vector3D get_direction(ShadeRec & sr) override;
	bool in_shadow(Ray const & ray, ShadeRec const & sr) const override;
	RGBColor L(ShadeRec & sr) override;

	AmbientOccluder * clone() const override;

	AmbientOccluder(AmbientOccluder const & rhs);

private:
	float		ls;
	RGBColor	color;
	float 		min_amount;
	Vector3D 	u, v, w;
	std::unique_ptr<Sampler> sampler_ptr;
};
