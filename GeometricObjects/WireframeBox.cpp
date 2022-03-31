// 	Copyright (C) Mp77 2012
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include <memory>
#include "Instance.h"
#include "OpenCylinder.h"
#include "WireframeBox.h"

using std::make_shared;

WireframeBox::WireframeBox(const Point3D	bottom_,
							const Point3D 	top_,
							const float	bevel_radius
									)
			: Compound(),
			p0(bottom_),
			p1(top_),
			br(bevel_radius){
		
	double width = p1.z - p0.z;
	double length = p1.x - p0.x;
	double height = p1.y - p0.y;

	auto ocd = make_shared<OpenCylinder>(p0.y,p1.y,br);
	
	Instance * part1 = new Instance(ocd);
	part1->translate({-width/2+br/2,0,-length/2});
	add_object(part1);

	Instance * part2 = new Instance(ocd);
	part2->translate({-width/2+br/2,0,length/2});
	add_object(part2);

	Instance * part3 = new Instance(ocd);
	part3->translate({width/2-br/2,0,length/2});
	add_object(part3);

	Instance * part4 = new Instance(ocd);
	part4->translate({width/2-br/2,0,-length/2});
	add_object(part4);
	
	Instance * part5 = new Instance(ocd);
	part5->translate({0,-(p0.y + p1.y)/2,0});
	part5->rotate_z(90);
	part5->translate({0,height/2-br/2,width/2});
	add_object(part5);

	Instance * part6 = new Instance(ocd);
	part6->translate({0,-(p0.y + p1.y)/2,0});
	part6->rotate_z(90);
	part6->translate({0,-height/2+br/2,width/2});
	add_object(part6);

	Instance * part7 = new Instance(ocd);
	part7->translate({0,-(p0.y + p1.y)/2,0});
	part7->rotate_z(90);
	part7->translate({0,-height/2+br/2,-width/2});
	add_object(part7);

	Instance * part8 = new Instance(ocd);
	part8->translate({0,-(p0.y + p1.y)/2,0});
	part8->rotate_z(90);
	part8->translate({0,height/2-br/2,-width/2});
	add_object(part8);

	Instance * part9 = new Instance(ocd);
	part9->translate({0,-(p0.y + p1.y)/2,0});
	part9->rotate_x(90);
	part9->translate({-length/2+br/2,height/2-br/2,0});
	add_object(part9);

	Instance * part10 = new Instance(ocd);
	part10->translate({0,-(p0.y + p1.y)/2,0});
	part10->rotate_x(90);
	part10->translate({-length/2+br/2,-height/2+br/2,0});
	add_object(part10);

	Instance * part11 = new Instance(ocd);
	part11->translate({0,-(p0.y + p1.y)/2,0});
	part11->rotate_x(90);
	part11->translate({length/2-br/2,-height/2+br/2,0});
	add_object(part11);

	Instance * part12 = new Instance(ocd);
	part12->translate({0,-(p0.y + p1.y)/2,0});
	part12->rotate_x(90);
	part12->translate({length/2-br/2,height/2-br/2,0});
	add_object(part12);

	bbox.x0 = p0.x - bevel_radius;
	bbox.y0 = p0.y - bevel_radius;
	bbox.z0 = p0.z - bevel_radius;
	bbox.x1 = p1.x + bevel_radius;
	bbox.y1 = p1.y + bevel_radius;
	bbox.z1 = p1.z + bevel_radius;
}

// ----------------------------------------------------------------  default constructor

WireframeBox::WireframeBox()
	: br{0}
{}


// ---------------------------------------------------------------- clone

WireframeBox* 
WireframeBox::clone(void) const {
	return (new WireframeBox(*this));
}

//------------------------------------------------------------------ hit
//This function has been modified since Listing 8.22

bool WireframeBox::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
	if (bbox.hit(ray))
		return Compound::hit(ray, tmin, sr);
	else
		return false;
}

// ------------------------------------------------- shadow hit
//This function has been modified since Listing 8.22

bool WireframeBox::shadow_hit(const Ray& ray, double & tmin) const {
	if (bbox.hit(ray))
		return Compound::shadow_hit(ray, tmin);
	else
		return false;
}
