#pragma once
#include "Tracer.h"

class RayCast: public Tracer {
public:
	RayCast() = default;
	RayCast(World * world);
	RGBColor trace_ray(Ray const & ray) const override;
	RGBColor trace_ray(Ray const ray, const int depth) const override;
};
