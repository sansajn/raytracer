// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include "BeveledRing.h"

#include "OpenCylinder.h"
#include "Annulus.h"
#include "Instance.h"
#include "Torus.h"

using std::shared_ptr, std::make_shared;

BeveledRing::BeveledRing(	const double bottom, const double top, const double i_radius, const double o_radius, const double b_radius)
			: Compound() {
		
		
	add_object(new Annulus(Point3D(0.0,bottom,0.0),Normal(0,-1,0),i_radius + b_radius,o_radius-i_radius - 2 * b_radius));

	add_object(new Annulus(Point3D(0.0,top,0.0),Normal(0,1,0),i_radius + b_radius,o_radius-i_radius - 2 * b_radius));
	
	Instance* outer_bottom_torus_ptr = new Instance(make_shared<Torus>( ( o_radius - b_radius ) , b_radius));
	outer_bottom_torus_ptr->translate({0, 0 + b_radius, 0});
	outer_bottom_torus_ptr->transform_texture(false);
	objects.push_back(outer_bottom_torus_ptr);

	Instance* outer_top_torus_ptr = new Instance(make_shared<Torus>( ( o_radius - b_radius ), b_radius));
	outer_top_torus_ptr->translate({0, top - b_radius, 0});
	outer_top_torus_ptr->transform_texture(false);
	objects.push_back(outer_top_torus_ptr);

	Instance* inner_bottom_torus_ptr = new Instance(make_shared<Torus>( ( i_radius + b_radius ) , b_radius));
	inner_bottom_torus_ptr->translate({0, 0 + b_radius, 0});
	inner_bottom_torus_ptr->transform_texture(false);
	objects.push_back(inner_bottom_torus_ptr);

	Instance* inner_top_torus_ptr = new Instance(make_shared<Torus>( ( i_radius + b_radius ), b_radius));
	inner_top_torus_ptr->translate({0, top - b_radius, 0});
	inner_top_torus_ptr->transform_texture(false);
	objects.push_back(inner_top_torus_ptr);


	objects.push_back(new OpenCylinder(bottom + b_radius, top - b_radius, i_radius));	// iwall

	objects.push_back(new OpenCylinder(bottom + b_radius, top - b_radius, o_radius));	// owall

	bbox.x0 = -o_radius;
	bbox.y0 = bottom - ( o_radius - i_radius ) / 2;
	bbox.z0 = -o_radius;
	bbox.x1 = o_radius;
	bbox.y1 = top + ( o_radius - i_radius ) / 2;
	bbox.z1 = o_radius;
}

// ----------------------------------------------------------------  default constructor

BeveledRing::BeveledRing (void)
	: 	Compound()
{
	Instance* bottom_torus_ptr = new Instance(make_shared<Torus>( 0.95, 0.05 ) );
	bottom_torus_ptr->translate({0, 0, 0});
	bottom_torus_ptr->transform_texture(false);
	objects.push_back(bottom_torus_ptr);

	Instance* top_torus_ptr = new Instance(make_shared<Torus>( 0.95, 0.05 ));
	top_torus_ptr->translate({0, 1, 0});
	top_torus_ptr->transform_texture(false);
	objects.push_back(top_torus_ptr);
		
	objects.push_back(new OpenCylinder(0, 1, 0.9));	// iwall


	objects.push_back(new OpenCylinder(0, 1, 0.1));	// owall

	bbox.x0 = -1;
	bbox.y0 = -1.05;
	bbox.z0 = -1;
	bbox.x1 = 1;
	bbox.y1 = 1.05;
	bbox.z1 = 1;
}


// ---------------------------------------------------------------- clone

BeveledRing* 
BeveledRing::clone(void) const {
	return (new BeveledRing(*this));
}


// ---------------------------------------------------------------- copy constructor

BeveledRing::BeveledRing (const BeveledRing& c)
	: Compound(c)
{}


//------------------------------------------------------------------ hit

bool 															 
BeveledRing::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
	if (bbox.hit(ray))
		return (Compound::hit(ray, tmin, sr));
	else
		return (false);
}

// ------------------------------------------------- shadow hit

bool BeveledRing::shadow_hit(const Ray& ray, double& tmin) const {
	if (bbox.hit(ray))
		return (Compound::shadow_hit(ray, tmin));
	else
		return (false);
}

void BeveledRing::set_bottom_material(shared_ptr<Material> material_ptr) {
	objects[0]->set_material(material_ptr);
}

void BeveledRing::set_top_material(shared_ptr<Material> material_ptr) {
	objects[1]->set_material(material_ptr);
}

void BeveledRing::set_inner_wall_material(shared_ptr<Material> material_ptr) {
	objects[2]->set_material(material_ptr);
}

void BeveledRing::set_outer_wall_material(shared_ptr<Material> material_ptr) {
	objects[3]->set_material(material_ptr);
}

BBox BeveledRing::get_bounding_box() {
	return bbox;
}
