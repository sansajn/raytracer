// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include "Constants.h"
#include "ConcavePartCylinder.h"

// ----------------------------------------------------------------  default constructor
// a default ConcavePartCylinder is a whole sphere

ConcavePartCylinder::ConcavePartCylinder (void)	
	: 	GeometricObject(),
		y0(-1.0),
		y1(1.0),
		radius(1.0),
		inv_radius(1.0),	
		polar_min(0.0),			// in radians
		polar_max(TWO_PI<double>)		// in radians
{
}


// ---------------------------------------------------------------- donstructor

ConcavePartCylinder::ConcavePartCylinder (const double 	bottom, 
							const double 	top, 
							const double 	r,
							const double 	polar_min,		// in degrees measured from top
							const double 	polar_max)		// in degrees measured from top
	: 	GeometricObject(),
		y0(bottom),			// bottom
		y1(top),			// top
		radius(r),
		polar_min(polar_min*PI_ON_180<double>),			// in radians
		polar_max(polar_max*PI_ON_180<double>)		// in radians
{
	inv_radius = 1/r;
}

ConcavePartCylinder::ConcavePartCylinder(	const double 	bottom, 
							const double 	top, 
							const double 	r)
	: 	GeometricObject(),
		radius(r),
		y0(bottom),			// bottom
		y1(top),			// top
		polar_min(0),			// in radians
		polar_max(TWO_PI<double>)		// in radians
{
	inv_radius = 1/r;
}

// ---------------------------------------------------------------- clone

ConcavePartCylinder* 
ConcavePartCylinder::clone(void) const {
	return (new ConcavePartCylinder(*this));
}


// ---------------------------------------------------------------- copy constructor

ConcavePartCylinder::ConcavePartCylinder (const ConcavePartCylinder& ps)
	: 	GeometricObject(ps),
		radius(ps.radius),
		y0(ps.y0),			// bottom
		y1(ps.y1),			// top
		polar_min(ps.polar_min),			// in radians
		polar_max(ps.polar_max),		// in radians
		inv_radius(ps.inv_radius)
{}


// ---------------------------------------------------------------- assignment operator

ConcavePartCylinder& 
ConcavePartCylinder::operator= (const ConcavePartCylinder& rhs)		
{
	if (this == &rhs)
		return (*this);

	GeometricObject::operator=(rhs);

	radius = rhs.radius;
	y0 = rhs.y0;			// bottom
	y1 = rhs.y1;			// top
	polar_min = rhs.polar_min;			// in radians
	polar_max = rhs.polar_max;	// in radians	
	inv_radius = rhs.inv_radius;

	return (*this);
}


// ---------------------------------------------------------------- destructor

ConcavePartCylinder::~ConcavePartCylinder(void) {}


// ------------------------------------------------------------------------------ hit

bool 															 
ConcavePartCylinder::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
	double t;
	double ox = ray.o.x;
	double oy = ray.o.y;
	double oz = ray.o.z;
	double dx = ray.d.x;
	double dy = ray.d.y;
	double dz = ray.d.z;
	
	double a = dx * dx + dz * dz;  	
	double b = 2.0 * (ox * dx + oz * dz);					
	double c = ox * ox + oz * oz - radius * radius;
	double disc = b * b - 4.0 * a * c ;

			
	if (disc < 0.0)
		return(false);
	else {	
		double e = sqrt(disc);
		double denom = 2.0 * a;
		t = (-b - e) / denom;    // smaller root
		
		if (t > kEpsilon) {
			double yhit = oy + t * dy;
			
			if (yhit > y0 && yhit < y1) {

				Point3D hit = ray.o + t * ray.d;
				
				double phi = atan2(hit.x, hit.z);
				
				if (phi < 0.0)
					phi += TWO_PI<double>;

				if(  phi >= polar_min && phi <= polar_max  )
				{
					tmin = t;
					sr.normal = Normal((ox + t * dx) * inv_radius, 0.0, (oz + t * dz) * inv_radius);
					// test for hitting from inside			
					if (-ray.d * sr.normal < 0.0)
						sr.normal = -sr.normal;				
					sr.local_hit_point = ray.o + tmin * ray.d;
					return (true);
				}
			}
		} 
		
		t = (-b + e) / denom;    // larger root
		
		if (t > kEpsilon) {
			double yhit = oy + t * dy;
			
			if (yhit > y0 && yhit < y1) {

				Point3D hit = ray.o + t * ray.d;
				
				double phi = atan2(hit.x, hit.z);
				
				if (phi < 0.0)
					phi += TWO_PI<double>;

				if(  phi >= polar_min && phi <= polar_max  )
				{
					tmin = t;
					sr.normal = Normal((ox + t * dx) * inv_radius, 0.0, (oz + t * dz) * inv_radius);
					// test for hitting from inside			
					if (-ray.d * sr.normal < 0.0)
						sr.normal = -sr.normal;					
					sr.local_hit_point = ray.o + tmin * ray.d;				
					return (true);
				}
			}
		} 
	}
	return (false);
}

// ------------------------------------------------------------------ shadow hit
	
bool 																						 
ConcavePartCylinder::shadow_hit(const Ray& ray, double & tmin) const
{
	double t;
	double ox = ray.o.x;
	double oy = ray.o.y;
	double oz = ray.o.z;
	double dx = ray.d.x;
	double dy = ray.d.y;
	double dz = ray.d.z;
	
	double a = dx * dx + dz * dz;
	double b = 2.0 * (ox * dx + oz * dz);
	double c = ox * ox + oz * oz - radius * radius;
	double disc = b * b - 4.0 * a * c ;

			
	if (disc < 0.0)
		return(false);
	else {	
		double e = sqrt(disc);
		double denom = 2.0 * a;
		t = (-b - e) / denom;    // smaller root
		
		if (t > kEpsilon) {
			double yhit = oy + t * dy;
			
			if (yhit > y0 && yhit < y1) {

				Point3D hit = ray.o + t * ray.d;
				
				double phi = atan2(hit.x, hit.z);
				
				if (phi < 0.0)
					phi += TWO_PI<double>;

				if(  phi >= polar_min && phi <= polar_max  )
				{
					if( t < tmin )
					{
						tmin = t;
						return (true);
					}
					Vector3D normal = - Normal((ox + t * dx) * inv_radius, 0.0, (oz + t * dz) * inv_radius);
					if( ray.d * normal < 0.0 )
					{
						tmin = 10;
						return true;
					}
				}
			}
		} 
		
		t = (-b + e) / denom;    // larger root
		
		if (t > kEpsilon) {
			double yhit = oy + t * dy;
			
			if (yhit > y0 && yhit < y1) {

				Point3D hit = ray.o + t * ray.d;
				
				double phi = atan2(hit.x, hit.z);
				
				if (phi < 0.0)
					phi += TWO_PI<double>;

				if(  phi >= polar_min && phi <= polar_max  )
				{
					if( t < tmin )
					{
						tmin = t;
						return (true);
					}
					Vector3D normal = - Normal((ox + t * dx) * inv_radius, 0.0, (oz + t * dz) * inv_radius);
					if( ray.d * normal < 0.0 )
					{
						tmin = 10;
						return true;
					}
				}
			}
		} 
	}	
	return (false);	
}
