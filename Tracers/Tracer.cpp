#include "Utilities/exception.hpp"
#include "Tracer.h"

Tracer::Tracer()
	: world_ptr{nullptr}
{}

Tracer::Tracer(World* _worldPtr)
	: world_ptr(_worldPtr)
{}

RGBColor Tracer::trace_ray(Ray const &) const {
	throw default_implementation{__PRETTY_FUNCTION__};
//	return black;
}

RGBColor	Tracer::trace_ray(Ray const, int const) const {
	throw default_implementation{__PRETTY_FUNCTION__};
//	return black;
}

RGBColor Tracer::trace_ray(Ray const ray, double & t, const int depth) const {
	throw default_implementation{__PRETTY_FUNCTION__};
//return white;
}
