#include <string>
#include "Utilities/exception.hpp"
#include "Tracer.h"

// -------------------------------------------------------------------- default constructor

Tracer::Tracer(void)
	: world_ptr{nullptr}
{}


// -------------------------------------------------------------------- constructor

Tracer::Tracer(World* _worldPtr)
	: world_ptr(_worldPtr)
{}


// -------------------------------------------------------------------- destructor

Tracer::~Tracer(void) {
	if (world_ptr)
		world_ptr = nullptr;
}


// -------------------------------------------------------------------- trace_ray

RGBColor Tracer::trace_ray(Ray const &) const {
	throw default_implementation{__PRETTY_FUNCTION__};
}


// -------------------------------------------------------------------- trace_ray

RGBColor	Tracer::trace_ray(Ray const, int const) const {
	throw default_implementation{__PRETTY_FUNCTION__};
}
