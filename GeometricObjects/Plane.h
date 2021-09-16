#ifndef __PLANE__
#define __PLANE__

#include "GeometricObject.h"

//-------------------------------------------------------------------- class Plane

class Plane: public GeometricObject {
	
	public:
	
		Plane(void);   												// default constructor
		
		Plane(const Point3D& point, const Normal& normal);			// constructor	
	
		Plane(const Plane& plane); 									// copy constructor
		
		virtual Plane* 												// virtual copy constructor
		clone(void) const;

		Plane& 														// assignment operator
		operator= (const Plane& rhs);	
		
		virtual														// destructor
		~Plane() = default;
					
		virtual bool 																								 
		hit(const Ray& ray, double& tmin, ShadeRec& sr) const;

		bool shadow_hit(Ray const & ray, double & tmin) const override;
		
	private:
	
		Point3D 	a;   				// point through which plane passes 
		Normal 		n;					// normal to the plane
				
		static const double kEpsilon;   // for shadows and secondary rays
};

#endif
