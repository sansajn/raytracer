/*! \file
Pinhole camera declaration. */
#pragma once
#include "Point2D.h"
#include "World.h"

class Pinhole: public Camera {
public:
	Pinhole();
	Pinhole(Point3D const & eye, Point3D const & lookat, float distance = 500);
	void set_view_distance(const float vpd);
	void set_zoom(const float zoom_factor);
	Vector3D	get_direction(const Point2D& p) const;
	void render_scene(const World& w) override;
	float view_plane_distance() const {return _d;}
	float zoom() const {return _zoom;}

	Pinhole * clone() const override;

private:
	float	_d;		// view plane distance
	float	_zoom;	// zoom factor
};
