#include "Ray.h"

Ray::Ray()
	: o{0.0}
	, d{0.0, 0.0, 1.0}
	, depth{0}
{}

Ray::Ray(Point3D const & origin, Vector3D const & dir)
	: o{origin}
	, d{dir}
	, depth{0}
{}

Ray::Ray (const Ray& ray)
	: 	o(ray.o), 
		d(ray.d),
		depth{0}
{}

Ray & Ray::operator=(Ray const & rhs) {
	
	if (this == &rhs)
		return (*this);
		
	o = rhs.o; 
	d = rhs.d;
	depth = rhs.depth;

	return (*this);	
}
