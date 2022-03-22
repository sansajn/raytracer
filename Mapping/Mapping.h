#pragma once

// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include <math.h>
#include "Point3D.h"

class Mapping {		
public:
	Mapping() = default;
	virtual ~Mapping() = default;

	// Copy API.
	virtual Mapping * clone() const = 0;
	Mapping(Mapping const & m) = default;
	Mapping & operator=(Mapping const & rhs) = default;

	/*! Calculate texture coordinates.
		\param [in] hit_point local hit point */
	virtual void
	get_texel_coordinates(	const 	Point3D& 	hit_point,
									const 	int 		xres,
									const 	int 		yres,
									int& 		row,
									int& 		column) const = 0;
};
