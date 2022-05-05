// 	Copyright (C) Kevin Suffern 2000-2007.
//	Revised by mp77 at 2012
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This file contains the declaration of the class ConvexPartSphere
// This is a part sphere where the surface normal always points outwards
// If you study the code here you should be able to implement other part objects

#pragma once

#include "GeometricObject.h"
#include <math.h>

//-------------------------------------------------------------------------------- class ConvexPartSphere

class ConvexPartSphere: public GeometricObject {	
public:
	
	Point3D 	center;   			// center coordinates
	double 		radius;				// sphere radius
	double 		phi_min;			// minimum azimiuth angle in degrees measured counter clockwise from the +ve z axis
	double 		phi_max;			// maximum azimiuth angle in degrees measured counter clockwise from the +ve z axis
	double 		theta_min;			// minimum polar angle in degrees measured down from the +ve y axis
	double 		theta_max;			// maximum polar angle in degrees measured down from the +ve y axis

	double		cos_theta_min;		// stored to avoid repeated calculations
	double		cos_theta_max;		// stored to avoid repeated calculations

public:

	ConvexPartSphere(void);

	ConvexPartSphere(	const Point3D 	c,
							const double 	r,
							const double 	azimuth_min,	// in degrees
							const double 	azimuth_max,	// in degrees
							const double 	polar_min,		// in degrees measured from top
							const double 	polar_max);		// in degrees measured from top

	ConvexPartSphere(const Point3D c, const double radius);

	bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const override;
	bool shadow_hit(const Ray& ray, double & tmin) const override;

	// Copy API.
	ConvexPartSphere * clone() const override;
	ConvexPartSphere(const ConvexPartSphere& cp);
	ConvexPartSphere & operator= (const ConvexPartSphere& rhs);

	virtual ~ConvexPartSphere(void);
};
