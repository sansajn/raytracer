#include <cassert>
#include "RayCast.h"
#include "World.h"
#include "ShadeRec.h"
#include "Material.h"

RayCast::RayCast(World * world)
	: Tracer{world}
{}

RGBColor	RayCast::trace_ray(Ray const & ray) const {
	assert(world_ptr);
	ShadeRec sr{world_ptr->hit_objects(ray)};
		
	if (sr.hit_an_object) {
		sr.ray = ray;			// used for specular shading
		return (sr.material_ptr->shade(sr));
	}   
	else
		return (world_ptr->background_color);
}


//! \note this ignores the depth argument
RGBColor	RayCast::trace_ray(const Ray ray, const int depth) const {
	ShadeRec sr(world_ptr->hit_objects(ray));
		
	if (sr.hit_an_object) {
		sr.ray = ray;			// used for specular shading
		return (sr.material_ptr->shade(sr));
	}   
	else
		return (world_ptr->background_color);
}

