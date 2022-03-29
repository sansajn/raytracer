// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// The OpenCone class is based on Excercise 19.12

#pragma once
#include "GeometricObject.h"

class OpenCone: public GeometricObject {
public:
	OpenCone();
	OpenCone(const double radius, const double height);

	bool hit(Ray const & ray, double & t, ShadeRec & sr) const override;
	bool shadow_hit(const Ray & ray, double & tmin) const override;

	// Copy API.
	OpenCone * clone() const override;

protected:
	double h,
		r;
};
