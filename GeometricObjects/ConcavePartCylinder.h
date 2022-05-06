// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This file contains the declaration of the class ConcavePartCylinder
// This is a part sphere where the surface normal always points outwards
// If you study the code here you should be able to implement other part objects

#pragma once

#include "GeometricObject.h"
#include <math.h>

//-------------------------------------------------------------------------------- class ConcavePartCylinder

class ConcavePartCylinder: public GeometricObject {	
	public:
	
		double		y0;				// bottom y value
		double		y1;				// top y value
		double		radius;			// radius
		double		inv_radius;  	// one over the radius	
		double polar_min;
		double polar_max;
								  	
	public:
		
		ConcavePartCylinder(void);   									    
		
		ConcavePartCylinder(	const double 	bottom, 
							const double 	top, 
							const double 	radius,
							const double 	polar_min,		// in degrees measured from top
							const double 	polar_max);		// in degrees measured from top

		ConcavePartCylinder(	const double 	bottom, 
							const double 	top, 
							const double 	radius);
						
		ConcavePartCylinder * clone() const override;
	
		ConcavePartCylinder(const ConcavePartCylinder& cp); 						

		virtual												
		~ConcavePartCylinder(void);   									

		ConcavePartCylinder& 											
		operator= (const ConcavePartCylinder& rhs);								
				
		bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const override;
		bool shadow_hit(const Ray& ray, double & tmin) const override;
};
