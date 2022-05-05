// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include "OpenCylinder.h"
#include "Annulus.h"
#include "ThickRing.h"

using std::shared_ptr;

ThickRing::ThickRing(	const double bottom, const double top, const double i_radius, const double o_radius)
			: Compound() {
		
		
	objects.push_back(new Annulus(Point3D(0.0,bottom,0.0),Normal(0,-1,0),i_radius,o_radius-i_radius));

	objects.push_back(new Annulus(Point3D(0.0,top,0.0),Normal(0,1,0),i_radius,o_radius-i_radius));  
		
	objects.push_back(new OpenCylinder(bottom, top, i_radius));	// iwall

	objects.push_back(new OpenCylinder(bottom, top, o_radius));	// owall

	bbox.x0 = -o_radius;
	bbox.y0 = bottom;
	bbox.z0 = -o_radius;
	bbox.x1 = o_radius;
	bbox.y1 = top;
	bbox.z1 = o_radius;
}

// ----------------------------------------------------------------  default constructor

ThickRing::ThickRing (void)
	: 	Compound()
{
	objects.push_back(new Annulus(Point3D(0.0,0,0.0),Normal(0,-1,0),0.9,0.1));

	objects.push_back(new Annulus(Point3D(0.0,1,0.0),Normal(0,1,0),0.9,0.1));  
		
	objects.push_back(new OpenCylinder(0, 1, 0.9));	// iwall


	objects.push_back(new OpenCylinder(0, 1, 0.1));	// owall

	bbox.x0 = -1;
	bbox.y0 = -1;
	bbox.z0 = -1;
	bbox.x1 = 1;
	bbox.y1 = 1;
	bbox.z1 = 1;
}


// ---------------------------------------------------------------- clone

ThickRing* 
ThickRing::clone(void) const {
	return (new ThickRing(*this));
}


// ---------------------------------------------------------------- copy constructor

ThickRing::ThickRing (const ThickRing& c)
	: Compound(c)
{}

//------------------------------------------------------------------ hit

bool 															 
ThickRing::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
	if (bbox.hit(ray))
		return (Compound::hit(ray, tmin, sr));
	else
		return (false);
}

// ------------------------------------------------- shadow hit

bool 																						 
ThickRing::shadow_hit(const Ray& ray, double & tmin) const
{
	if (bbox.hit(ray))
		return (Compound::shadow_hit(ray, tmin));
	else
		return (false);
}

void 
ThickRing::set_bottom_material(shared_ptr<Material> material_ptr)
{
	objects[0]->set_material(material_ptr);
}	//19.29

void 
ThickRing::set_top_material(shared_ptr<Material> material_ptr)
{
	objects[1]->set_material(material_ptr);
}	//19.29

void 
ThickRing::set_inner_wall_material(shared_ptr<Material> material_ptr)
{
	objects[2]->set_material(material_ptr);
}//19.29

void 
ThickRing::set_outer_wall_material(shared_ptr<Material> material_ptr)
{
	objects[3]->set_material(material_ptr);
}//19.29

BBox ThickRing::get_bounding_box() {
	return bbox;
}
