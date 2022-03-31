// 	Copyright (C) Mp77 2012
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

//WireframeBox class only used in Listing 8.22, Here I have implemented a simple demo, and It seems to be OK according to source pictures.

#pragma once
#include <vector>
#include "Compound.h"
#include "Instance.h"

class WireframeBox: public Compound {
public:
	WireframeBox();
	WireframeBox(const Point3D	bottom_,
					 const Point3D 	top_,
					 const float	bevel_radius);

	bool hit(const Ray& ray, double& tmin, ShadeRec& s) const override;
	bool shadow_hit(const Ray& ray, double & tmin) const override;

	WireframeBox * clone() const override;

private:
	BBox		bbox;	// the bounding box
	Point3D p0;
	Point3D p1;
	float br;
};
