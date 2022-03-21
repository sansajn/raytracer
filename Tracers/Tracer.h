// This is the declaration of the base class Tracer
// The tracer classes have no copy constructor, assignment operator. or clone function because 
// of the world pointer, which should not be assigned or copy constructed
// See comments in the World.h file.

#pragma once
#include "Constants.h"
#include "Ray.h"
#include "RGBColor.h"

class World;

class Tracer {
public:
	Tracer();
	explicit Tracer(World * world);

	virtual RGBColor trace_ray(Ray const & ray) const;
	virtual RGBColor trace_ray(Ray const ray, const int depth) const;
	virtual RGBColor trace_ray(Ray const ray, double & t, const int depth) const;  //!< To support rflection.

	virtual ~Tracer() = default;

protected:
	World * world_ptr;
};
