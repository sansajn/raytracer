// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include "Constants.h"
#include "Disk.h"
#include "ConvexPartSphere.h"
#include "ConcavePartSphere.h"
#include "Instance.h"
#include "RoundRimmedBowl.h"
#include "Annulus.h"
#include "Torus.h"

using std::shared_ptr, std::make_shared;

// ------------------------------------------------------------------------------ default constructor

RoundRimmedBowl::RoundRimmedBowl(void)
	: 	Compound(),
		inner_radius(0.9),
		outer_radius(1.0),
		openning(90)
{	
	build_components();														
}


// ------------------------------------------------------------------------------ constructor

RoundRimmedBowl::RoundRimmedBowl(	const double i, const double o)
	: 	Compound(),
		inner_radius(i),
		outer_radius(o),
		openning(90)
{	
	build_components();														
}


RoundRimmedBowl::RoundRimmedBowl(	const double i, const double o, const double a)
	: 	Compound(),
		inner_radius(i),
		outer_radius(o),
		openning(a/2)
{
	build_components();
}
																																																											

// ------------------------------------------------------------------------------ copy constructor

RoundRimmedBowl::RoundRimmedBowl(const RoundRimmedBowl& fb)  			
	: 	Compound(fb),
		inner_radius(fb.inner_radius),
		outer_radius(fb.outer_radius),
		openning(fb.openning)
{}


// ------------------------------------------------------------------------------ clone

RoundRimmedBowl* 
RoundRimmedBowl::clone(void) const {
	return(new RoundRimmedBowl(*this));
}


// ------------------------------------------------------------------------------ assignment operator

RoundRimmedBowl& 
RoundRimmedBowl::operator= (const RoundRimmedBowl& rhs) {
	if (this == &rhs)
		return (*this);

	Compound::operator=(rhs); 
	
	inner_radius = rhs.inner_radius;
	outer_radius = rhs.outer_radius;
	openning = rhs.openning;

	return (*this) ;
}


// ------------------------------------------------------------------------------ destructor
 
RoundRimmedBowl::~RoundRimmedBowl(void) {}


// ------------------------------------------------------------------------------ build_components

void 
RoundRimmedBowl::build_components(void) {
	
	double outer_angle = acos(cos(openning * PI_ON_180<double>) * inner_radius / outer_radius );

	add_object(new ConvexPartSphere(	Point3D(0.0),
											outer_radius,
											0, 360,  				// azimuth angle range - full circle
											outer_angle * 180 * invPI<double>,  					// minimum polar angle measured from top
											180));                 	// maximum polar angle measured from top


	add_object(new ConcavePartSphere(Point3D(0.0),
											inner_radius,
											0, 360, 				// azimuth angle - full circle
											openning,    // mimimum polar angle measured from top
											180));   			// maximum polar angle measured from top

	add_object(new Torus(
								fabs(openning / 90) * (inner_radius + outer_radius) / 2.0,	// a
								fabs(openning / 90) * (outer_radius - inner_radius) / 2.0		// b
								));   			// maximum polar angle measured from top
}

void
RoundRimmedBowl::set_material(shared_ptr<Material> m_ptr) {
	for (auto * object : objects)
		object->set_material(m_ptr);
}
