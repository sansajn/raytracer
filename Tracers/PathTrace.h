#pragma once
#include "Tracer.h"

class PathTrace : public Tracer {
public:
	PathTrace() = default;
	PathTrace(World* world);
	RGBColor trace_ray(Ray const ray, const int depth) const override;
};
