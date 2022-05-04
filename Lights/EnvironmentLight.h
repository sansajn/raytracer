#pragma once
#include <memory>
#include "Light.h"
#include "Samplers/Sampler.h"
#include "Materials/Material.h"

class EnvironmentLight : public Light {
public:
	EnvironmentLight() = default;

	void set_sampler(std::unique_ptr<Sampler> s);
	void set_material(std::shared_ptr<Material> m);
	RGBColor L(ShadeRec & sr) override;
	float G(ShadeRec const & sr) const override;
	bool in_shadow(Ray const & ray, ShadeRec const & sr) const override;
	Vector3D get_direction(ShadeRec& sr) override;
	float pdf(ShadeRec const & sr) const override;

	// Copy API.
	EnvironmentLight(EnvironmentLight const & rhs);
	Light * clone() const override;

private:
	Vector3D _u, _v, _w,
		_wi;
	std::unique_ptr<Sampler> _sampler;
	std::shared_ptr<Material> _material;
};
