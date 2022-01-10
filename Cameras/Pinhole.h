/*! \file
Pinhole camera declaration. */
#pragma once
#include "Point2D.h"
#include "World.h"

class Pinhole: public Camera {
public:
	Pinhole();
	void set_view_distance(const float vpd);
	void set_zoom(const float zoom_factor);
	Vector3D	get_direction(const Point2D& p) const;

	void render_scene(const World& w) override;

	Pinhole * clone() const override;
	Pinhole & operator=(const Pinhole& rhs);
	Pinhole(const Pinhole & ph);

private:
	float	d;		// view plane distance
	float	zoom;	// zoom factor
};

inline void
Pinhole::set_view_distance(float _d) {
	d = _d;
}	
	
inline void
Pinhole::set_zoom(float zoom_factor) {
	zoom = zoom_factor;
}	
