/*! \file
This file contains the declaration of the class ShadeRec. */
#pragma once

class Material;
class World;

#include <vector>
#include "Point3D.h"
#include "Normal.h"
#include "Ray.h"
#include "RGBColor.h"

struct ShadeRec {
	bool				hit_an_object;		// Did the ray hit an object?
	Material const * material_ptr;		// Pointer to the nearest object's material
	Point3D 			hit_point;			// World coordinates of intersection
	Point3D				local_hit_point;	// World coordinates of hit point on generic object (used for texture transformations)
	Normal				normal;				// Normal at hit point
	Ray					ray;				// Required for specular highlights and area lights
	int					depth;				// recursion depth
	Vector3D dir;  // for area lights
	World&				w;					// World reference
	float	t;  //! ray parameter (from ray equation)
	float u, v;  //!< uv mapping coordinates used by Flat|SmoothUVMeshTriangle

	RGBColor color;  // only used in chapter 3

	explicit ShadeRec(World & wr);
	ShadeRec(ShadeRec const & sr);
};
