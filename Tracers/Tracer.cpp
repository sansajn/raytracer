#include <string>
#include <stdexcept>
#include "Tracer.h"

using std::logic_error;
using namespace std::string_literals;

// -------------------------------------------------------------------- default constructor

Tracer::Tracer(void)
	: world_ptr(NULL)
{}


// -------------------------------------------------------------------- constructor

Tracer::Tracer(World* _worldPtr)
	: world_ptr(_worldPtr)
{}


// -------------------------------------------------------------------- destructor

Tracer::~Tracer(void) {
	if (world_ptr)
		world_ptr = NULL;
}


// -------------------------------------------------------------------- trace_ray

RGBColor Tracer::trace_ray(Ray const &) const {
	throw logic_error{"not implemented, the default implemenation of '"s + __PRETTY_FUNCTION__ + "' is ment to be override"};
}


// -------------------------------------------------------------------- trace_ray

RGBColor	Tracer::trace_ray(Ray const, int const) const {
	throw logic_error{"not implemented, the default implemenation of '"s + __PRETTY_FUNCTION__ + "' is ment to be override"};
}
