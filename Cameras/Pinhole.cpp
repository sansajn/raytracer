// This file contains the definition of the Pinhole class

#include <utility>
#include <math.h>
#include "Constants.h" 
#include "Point3D.h"
#include "Vector3D.h"
#include "Pinhole.h"

// ----------------------------------------------------------------------------- default constructor

Pinhole::Pinhole(void)		
	:	_d(500),
		_zoom(1.0)
{}

Pinhole::Pinhole(Point3D const & eye, Point3D const & lookat, float distance)
	: Camera{eye, lookat}
	, _d{distance}
	, _zoom{1.0}
{}


Pinhole * Pinhole::clone() const {
	return (new Pinhole(*this));
}

// ----------------------------------------------------------------------------- get_direction

void Pinhole::set_view_distance(float vpd) {
	_d = vpd;
}

void Pinhole::set_zoom(float zoom_factor) {
	_zoom = zoom_factor;
}

Vector3D
Pinhole::get_direction(const Point2D& p) const {
	Vector3D dir = p.x * u + p.y * v - _d * w;
	dir.normalize();
	
	return(dir);
}



// ----------------------------------------------------------------------------- render_scene

void 												
Pinhole::render_scene(const World& w) {
	RGBColor	L;
	ViewPlane	vp(w.vp);
	Ray			ray;
	int 		depth = 0;  
	Point2D 	pp;		// sample point on a pixel
	int const n = (int)sqrt((float)vp.num_samples);
		
	vp.s /= _zoom;
	ray.o = eye;
		
	for (int r = 0; r < vp.vres; r++) {			// up
		for (int c = 0; c < vp.hres; c++) {		// across
			L = black;
			
			for (int p = 0; p < n; p++)			// up pixel
				for (int q = 0; q < n; q++) {	// across pixel
					Point2D sp = vp.sampler_ptr->sample_unit_square();
					pp.x = vp.s * (c - 0.5 * vp.hres + sp.x);
					pp.y = vp.s * (r - 0.5 * vp.vres + sp.y);
					ray.d = get_direction(pp);
					L += w.tracer_ptr->trace_ray(ray, depth);
				}
											
			L /= vp.num_samples;
			L *= exposure_time;
			w.display_pixel(r, c, L);
		}
	}
}
