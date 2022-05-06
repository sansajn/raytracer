// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include <memory>
#include "BeveledWedge.h"
#include "Constants.h"
#include "Annulus.h"
#include "ConcavePartCylinder.h"
#include "ConvexPartCylinder.h"
#include "ConvexPartTorus.h"
#include "Instance.h"
#include "OpenCylinder.h"
#include "OpenPartCylinder.h"
#include "PartAnnulus.h"
#include "Rectangle.h"
#include "Sphere.h"

using std::make_shared;

// ------------------------------------------------------------------------------ copy constructor

BeveledWedge::BeveledWedge (const BeveledWedge& bw)  			
			: 	Compound(bw),
				y0(bw.y0),
				y1(bw.y1),
				r0(bw.r0),
				r1(bw.r1),
				rb(bw.rb),
				phi0(bw.phi0),
				phi1(bw.phi1),
				bbox(bw.bbox)
{}

// ------------------------------------------------------------------------------ clone

BeveledWedge* 
BeveledWedge::clone (void) const {
	return(new BeveledWedge(*this));
}


// ------------------------------------------------------------------------------ get_bounding_box

BBox 
BeveledWedge::get_bounding_box(void) {
	return (bbox);
}



// ------------------------------------------------------------------------------ hit

bool 															 
BeveledWedge::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {	
	if (bbox.hit(ray))
		return (Compound::hit(ray, tmin, sr));
	else
		return (false);
}

/*
#include "BeveledWedge.h"

#include "OpenPartCylinder.h"
#include "Annulus.h"
#include "Instance.h"
#include "ConvexPartTorus.h"
#include "Rectangle.h"
#include "ConcavePartCylinder.h"
#include "ConvexPartCylinder.h"
#include "PartAnnulus.h"
#include "Sphere.h"
*/


BeveledWedge::BeveledWedge(const double bottom, const double top, const double i_radius, const double o_radius, const double b_radius, const double min_azimuth, const double max_azimuth)
			: Compound() {
						
	objects.push_back(new PartAnnulus(Point3D(0.0,bottom,0.0),Normal(0,-1,0),i_radius+b_radius,o_radius-i_radius-2*b_radius,min_azimuth,max_azimuth));

	objects.push_back(new PartAnnulus(Point3D(0.0,top,0.0),Normal(0,1,0),i_radius+b_radius,o_radius-i_radius-2*b_radius,min_azimuth,max_azimuth));  

	Instance* bottom_torus_ptr = new Instance(make_shared<ConvexPartTorus>( o_radius - b_radius , b_radius, min_azimuth, max_azimuth,0,180));
	bottom_torus_ptr->translate({0, top-b_radius, 0});
	bottom_torus_ptr->transform_texture(false);
	objects.push_back(bottom_torus_ptr);

	Instance* bottom_torus_ptr1 = new Instance(make_shared<ConvexPartTorus>( i_radius + b_radius , b_radius, min_azimuth, max_azimuth,0,180));
	bottom_torus_ptr1->translate({0, top-b_radius, 0});
	bottom_torus_ptr1->transform_texture(false);
	objects.push_back(bottom_torus_ptr1);

	Instance* top_torus_ptr1 = new Instance(make_shared<ConvexPartTorus>( o_radius - b_radius , b_radius, min_azimuth, max_azimuth,0,180));
	top_torus_ptr1->translate({0, bottom+b_radius, 0});
	top_torus_ptr1->transform_texture(false);
	objects.push_back(top_torus_ptr1);

	Instance* top_torus_ptr = new Instance(make_shared<ConvexPartTorus>( i_radius + b_radius , b_radius, min_azimuth, max_azimuth,0,180));
	top_torus_ptr->translate({0, bottom+b_radius, 0});
	top_torus_ptr->transform_texture(false);
	objects.push_back(top_torus_ptr);

	objects.push_back(new OpenPartCylinder(bottom+b_radius, top-b_radius, i_radius,min_azimuth,max_azimuth));	// iwall

	objects.push_back(new OpenPartCylinder(bottom+b_radius, top-b_radius, o_radius,min_azimuth,max_azimuth));	// owall

	if( max_azimuth - min_azimuth < 360 )
	{
		double minx = sin(min_azimuth*PI_ON_180<double>)*(i_radius+b_radius);
		double miny = top-b_radius;
		double minz = cos(min_azimuth*PI_ON_180<double>)*(i_radius+b_radius);
		Vector3D a(sin(min_azimuth*PI_ON_180<double>),0,cos(min_azimuth*PI_ON_180<double>));
		a.normalize();
		a = a * ( o_radius - i_radius - 2 * b_radius);

		Vector3D b(0,- (top-bottom-2* b_radius),0);
		Vector3D n = b ^ a;
		n.normalize();
		/////////////////////////
		Instance* rectangle1 = new Instance(make_shared<Rectangle>( Point3D(minx,miny,minz)+(n*b_radius) , a, b,n));
		objects.push_back(rectangle1);

		Instance* new_cylinder1 = new Instance(make_shared<OpenPartCylinder>( bottom+b_radius , top-b_radius, b_radius,0,360));
		new_cylinder1->translate({minx, 0, minz});
		new_cylinder1->transform_texture(false);
		objects.push_back(new_cylinder1);

		Instance* new_cylinder2 = new Instance(make_shared<OpenPartCylinder>( bottom+b_radius , top-b_radius, b_radius,0,360));
		new_cylinder2->translate({minx+a.x, 0, minz+a.z});
		new_cylinder2->transform_texture(false);
		objects.push_back(new_cylinder2);

		Instance* new_cylinderh1 = new Instance(make_shared<OpenPartCylinder>( 0 , o_radius-i_radius-2*b_radius, b_radius,0,360));
		new_cylinderh1->rotate_x(90);
		new_cylinderh1->translate({0,bottom+b_radius,i_radius+b_radius});
		new_cylinderh1->rotate_y(min_azimuth);
		new_cylinderh1->transform_texture(false);
		objects.push_back(new_cylinderh1);

		Instance* new_cylinderh2 = new Instance(make_shared<OpenPartCylinder>( 0, o_radius-i_radius-2*b_radius, b_radius,0,360));
		new_cylinderh2->rotate_x(90);
		new_cylinderh2->translate({0,top-b_radius,i_radius+b_radius});
		new_cylinderh2->rotate_y(min_azimuth);
		new_cylinderh2->transform_texture(false);
		objects.push_back(new_cylinderh2);

		Sphere *sphere1 = new Sphere( Point3D(minx,miny,minz),b_radius);
		objects.push_back(sphere1);
		Sphere *sphere2 = new Sphere( Point3D(minx,miny,minz)+a,b_radius);
		objects.push_back(sphere2);
		Sphere *sphere3 = new Sphere( Point3D(minx,bottom+b_radius,minz),b_radius);
		objects.push_back(sphere3);
		Sphere *sphere4 = new Sphere( Point3D(minx,bottom+b_radius,minz)+a,b_radius);
		objects.push_back(sphere4);

		minx = sin(max_azimuth*PI_ON_180<double>)*(i_radius+b_radius);
		miny = top-b_radius;
		minz = cos(max_azimuth*PI_ON_180<double>)*(i_radius+b_radius);
		a = Vector3D(sin(max_azimuth*PI_ON_180<double>),0,cos(max_azimuth*PI_ON_180<double>));
		a.normalize();
		a = a * ( o_radius - i_radius - 2 * b_radius);

		n = a ^ b;
		n.normalize();
		/////////////////////////

		Instance* new_cylinder3 = new Instance(make_shared<OpenPartCylinder>( bottom+b_radius , top-b_radius, b_radius,0,360));
		new_cylinder3->translate({minx, 0, minz});
		new_cylinder3->transform_texture(false);
		objects.push_back(new_cylinder3);

		Instance* new_cylinder4 = new Instance(make_shared<OpenPartCylinder>( bottom+b_radius , top-b_radius, b_radius,0,360));
		new_cylinder4->translate({minx+a.x, 0, minz+a.z});
		new_cylinder4->transform_texture(false);
		objects.push_back(new_cylinder4);
				
		Instance* rectangle2 = new Instance(make_shared<Rectangle>( Point3D(minx,miny,minz)+(n*b_radius) , a, b,n));
		objects.push_back(rectangle2);

		Instance* new_cylinderh3 = new Instance(make_shared<OpenPartCylinder>( 0 , o_radius-i_radius-2*b_radius, b_radius,0,360));
		new_cylinderh3->rotate_x(90);
		new_cylinderh3->translate({0,bottom+b_radius,i_radius+b_radius});
		new_cylinderh3->rotate_y(max_azimuth);
		new_cylinderh3->transform_texture(false);
		objects.push_back(new_cylinderh3);

		Instance* new_cylinderh4 = new Instance(make_shared<OpenPartCylinder>( 0, o_radius-i_radius-2*b_radius, b_radius,0,360));
		new_cylinderh4->rotate_x(90);
		new_cylinderh4->translate({0,top-b_radius,i_radius+b_radius});
		new_cylinderh4->rotate_y(max_azimuth);
		new_cylinderh4->transform_texture(false);
		objects.push_back(new_cylinderh4);

		Sphere *sphere5 = new Sphere( Point3D(minx,miny,minz),b_radius);
		objects.push_back(sphere5);
		Sphere *sphere6 = new Sphere( Point3D(minx,miny,minz)+a,b_radius);
		objects.push_back(sphere6);
		Sphere *sphere7 = new Sphere( Point3D(minx,bottom+b_radius,minz),b_radius);
		objects.push_back(sphere7);
		Sphere *sphere8 = new Sphere( Point3D(minx,bottom+b_radius,minz)+a,b_radius);
		objects.push_back(sphere8);
	}

	bbox.x0 = -o_radius;
	bbox.y0 = bottom;
	bbox.z0 = -o_radius;
	bbox.x1 = o_radius;
	bbox.y1 = top;
	bbox.z1 = o_radius;
}


/*
// ----------------------------------------------------------------  default constructor

BeveledWedge::BeveledWedge (void)
	: 	Compound()
{
	double bottom = -1.0;		// minimum y value
	float top = 2;			// maximum y value
	float i_radius = 1.5;			// inner radius
	float o_radius = 3;			// outer radius
	float b_radius = 0.25;		// bevel radius
	float min_azimuth = 140;		// minimum azimuth angle in degrees
	float max_azimuth = 350;		// maximum azimuth angle in degrees

	objects.push_back(new PartAnnulus(Point3D(0.0,bottom,0.0),Normal(0,-1,0),i_radius+b_radius,o_radius-i_radius-2*b_radius,min_azimuth,max_azimuth));

	objects.push_back(new PartAnnulus(Point3D(0.0,top,0.0),Normal(0,1,0),i_radius+b_radius,o_radius-i_radius-2*b_radius,min_azimuth,max_azimuth));  
	
	Instance* bottom_torus_ptr = new Instance(new ConvexPartTorus( o_radius - b_radius , b_radius, min_azimuth, max_azimuth,0,180));
	bottom_torus_ptr->translate(0, top-b_radius, 0);
	bottom_torus_ptr->transform_texture(false);
	objects.push_back(bottom_torus_ptr);

	Instance* bottom_torus_ptr1 = new Instance(new ConvexPartTorus( i_radius + b_radius , b_radius, min_azimuth, max_azimuth,0,180));
	bottom_torus_ptr1->translate(0, top-b_radius, 0);
	bottom_torus_ptr1->transform_texture(false);
	objects.push_back(bottom_torus_ptr1);

	Instance* top_torus_ptr1 = new Instance(new ConvexPartTorus( o_radius - b_radius , b_radius, min_azimuth, max_azimuth,0,180));
	top_torus_ptr1->translate(0, bottom+b_radius, 0);
	top_torus_ptr1->transform_texture(false);
	objects.push_back(top_torus_ptr1);

	Instance* top_torus_ptr = new Instance(new ConvexPartTorus( i_radius + b_radius , b_radius, min_azimuth, max_azimuth,0,180));
	top_torus_ptr->translate(0, bottom+b_radius, 0);
	top_torus_ptr->transform_texture(false);
	objects.push_back(top_torus_ptr);

	objects.push_back(new OpenPartCylinder(bottom+b_radius, top-b_radius, i_radius,min_azimuth,max_azimuth));	// iwall

	objects.push_back(new OpenPartCylinder(bottom+b_radius, top-b_radius, o_radius,min_azimuth,max_azimuth));	// owall

	if( max_azimuth - min_azimuth < 360 )
	{
		Instance* rectangle1 = new Instance(new TRectangle( Point3D(b_radius,top-b_radius,o_radius-b_radius) , Vector3D(0,0,-(o_radius-i_radius-2*b_radius)),Vector3D(0,-(top-bottom-2*b_radius),0),Normal(-1,0,0)));
		rectangle1->rotate_y(min_azimuth);
		rectangle1->transform_texture(false);
		objects.push_back(rectangle1);

		Instance* rectangle2 = new Instance(new TRectangle( Point3D(b_radius,top-b_radius,o_radius-b_radius) , Vector3D(0,0,-(o_radius-i_radius-2*b_radius)),Vector3D(0,-(top-bottom-2*b_radius),0),Normal(1,0,0)));
		rectangle2->rotate_y(max_azimuth);
		rectangle2->transform_texture(false);
		objects.push_back(rectangle2);
	}

	bbox.x0 = -o_radius;
	bbox.y0 = bottom;
	bbox.z0 = -o_radius;
	bbox.x1 = o_radius;
	bbox.y1 = top;
	bbox.z1 = o_radius;
}


// ---------------------------------------------------------------- clone

BeveledWedge* 
BeveledWedge::clone(void) const {
	return (new BeveledWedge(*this));
}


// ---------------------------------------------------------------- copy constructor

BeveledWedge::BeveledWedge (const BeveledWedge& c)
	: Compound(c) {
	
	copy_objects(c.objects);					
}



// ---------------------------------------------------------------- assignment operator

BeveledWedge& 
BeveledWedge::operator= (const BeveledWedge& rhs) {
	if (this == &rhs)
		return (*this);

	GeometricObject::operator= (rhs);						
	
	copy_objects(rhs.objects);				

	return (*this);
}


// ---------------------------------------------------------------- destructor

BeveledWedge::~BeveledWedge(void) {	
	delete_objects();				
}


//------------------------------------------------------------------ set_material
// sets the same material on all objects

void 
BeveledWedge::set_material(Material* material_ptr) {
	int num_objects = objects.size();

	for (int j = 0; j < num_objects; j++)
		objects[j]->set_material(material_ptr);
}


//------------------------------------------------------------------ delete_objects
// Deletes the objects in the objects array, and erases the array.
// The array still exists, because it'ss an automatic variable, but it's empty 

void
BeveledWedge::delete_objects(void) {
	int num_objects = objects.size();
	
	for (int j = 0; j < num_objects; j++) {
		delete objects[j];
		objects[j] = NULL;
	}	
	
	objects.erase(objects.begin(), objects.end());
}


//------------------------------------------------------------------ copy_objects

void
BeveledWedge::copy_objects(const vector<GeometricObject*>& rhs_ojects) {
	delete_objects();    	
	int num_objects = rhs_ojects.size();
	
	for (int j = 0; j < num_objects; j++)
		objects.push_back(rhs_ojects[j]->clone());
}


//------------------------------------------------------------------ hit

bool 															 
BeveledWedge::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
	if (bbox.hit(ray))
		return (Compound::hit(ray, tmin, sr));
	else
		return (false);
}

// ------------------------------------------------- shadow hit

bool 																						 
BeveledWedge::shadow_hit(const Ray& ray, float& tmin) const
{
	if (bbox.hit(ray))
		return (Compound::shadow_hit(ray, tmin));
	else
		return (false);
}

void 
BeveledWedge::set_bottom_material(Material* material_ptr)
{
	objects[0]->set_material(material_ptr);
}	//19.29

void 
BeveledWedge::set_top_material(Material* material_ptr)
{
	objects[1]->set_material(material_ptr);
}	//19.29

void 
BeveledWedge::set_inner_wall_material(Material* material_ptr)
{
	objects[2]->set_material(material_ptr);
}//19.29

void 
BeveledWedge::set_outer_wall_material(Material* material_ptr)
{
	objects[3]->set_material(material_ptr);
}//19.29

BBox 
BeveledWedge::get_bounding_box(void)
{
	return bbox;
}
*/
