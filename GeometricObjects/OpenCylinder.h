#pragma once

// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// An open cylinder is defined by its extent in the y direction and its radius.
// It is centered on the y axis.
// The classes ConcaveOpenCylinder and ConvexOpenCylinder can inherit from OpenCylinder.
// The classes ConcavePartCylinder and ConvexPartCylinder can in turn inherit from these.

#include "GeometricObject.h"

class OpenCylinder: public GeometricObject {
public:
	OpenCylinder();
	OpenCylinder(const double bottom, const double top, const double radius);

	bool hit(Ray const & ray, double & tmin, ShadeRec & sr) const override;
	bool shadow_hit(Ray const & ray, double & tmin) const override;

	OpenCylinder(const OpenCylinder& c);
	OpenCylinder & operator=(const OpenCylinder& rhs);
	OpenCylinder *	clone() const override;

	~OpenCylinder();

protected:
	double		y0;				// bottom y value
	double		y1;				// top y value
	double		radius;			// radius
	double		inv_radius;  	// one over the radius
};
