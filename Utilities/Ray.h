#ifndef __RAY__
#define __RAY__

#include "Point3D.h"
#include "Vector3D.h"

class Ray {
public:
	Point3D o;  // origin
	Vector3D d;  // direction
	int depth;  // FIX: no where used (it is just set in Reflective::shade, but no where used)

	Ray();
	Ray(Point3D const & origin, Vector3D const & dir);
	Ray(Ray const & ray);

	Ray & operator=(const Ray& rhs);
};

#endif
