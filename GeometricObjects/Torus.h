#ifndef __TORUS__
#define __TORUS__

// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "GeometricObject.h"

class Torus: public GeometricObject {
	public:
		
		Torus();
		
		Torus(const double _a, const double _b);

		Torus * clone() const override;
	
		Torus(const Torus& torus);
		
		Torus& 
		operator= (Torus& rhs);	
		
		Normal 					
		compute_normal(const Point3D& p) const;  												
		
		bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const override;
		bool shadow_hit(Ray const & ray, double & tmin) const override;
		
	private:
	
		double 		a;	 	// swept radius 
		double		b;	 	// tube radius
		BBox		bbox;	// the bounding box
};

#endif
