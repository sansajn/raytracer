// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figure 11.12
// The light probe mapping is described in Chapter 29
// There are no light sources in this scene

#include "World/World.h"
#include "Tracers/RayCast.h"
#include "Cameras/Spherical.h"
#include "Lights/PointLight.h"
#include "Materials/Matte.h"
#include "Materials/SV_Matte.h"
#include "GeometricObjects/Box.h"
#include "GeometricObjects/Grid.h"
#include "GeometricObjects/Plane.h"
#include "GeometricObjects/Instance.h"
#include "Textures/Checker3D.h"
#include "Textures/ImageTexture.h"
#include "Textures/SphericalMap.h"
#include "Utilities/Image.h"
#include "Utilities/Random.h"

using std::make_unique, std::make_shared, std::move;

void World::build() {
	constexpr int num_samples = 16;
	
	vp.set_hres(600);			
	vp.set_vres(600); 
	vp.set_samples(num_samples);
	vp.set_pixel_size(1.0);
	
	tracer_ptr = new RayCast(this);	
	
	auto spherical_ptr = make_unique<Spherical>();
	spherical_ptr->set_eye(10, 15, 13);      
	spherical_ptr->set_lookat(34, 15, 0);
		
	// for Figure 11.12(a)
	
	vp.set_hres(600);			
	vp.set_vres(400);
	
	spherical_ptr->set_horizontal_fov(180);  
	spherical_ptr->set_vertical_fov(120);    
	
/*	
	// for Figure 11.12(b)
	
	vp.set_hres(800);			
	vp.set_vres(400);
	
	spherical_ptr->set_horizontal_fov(360);  
	spherical_ptr->set_vertical_fov(180);  
*/  
		
	spherical_ptr->compute_uvw(); 
	set_camera(move(spherical_ptr));
	   	
	
	PointLight* light_ptr2 = new PointLight;
	light_ptr2->set_location(150, 500, 300);  
	light_ptr2->scale_radiance(3.75);  
	light_ptr2->set_shadows(true);
	add_light(light_ptr2);
	
	
	// city parameters
	
	float 	a					= 10;   // city block width:  xw extent
	float 	b   				= 12;	// city block length:  yw extent
	int 	num_rows			= 10;  	// number of blocks in the xw direction
	int 	num_columns			= 12; 	// number of blocks in the zw direction
	float	width				= 7;	// building width: xw extent in range [min, a - offset]
	float 	length				= 7;	// building length: zw extent in range [min, b - offset]
	float 	min_size			= 6;	// mininum building extent in xw and yw directions
	float 	offset				= 1.0;	// half the minimum distance between buildings
	float 	min_height			= 0.0; 	// minimum building height
	float 	max_height			= 30; 	// maximum bulding height
	float 	height;						// the building height in range [min_height, max_height]
	int		num_park_rows		= 4;  	// number of blocks of park in xw direction
	int		num_park_columns	= 6;  	// number of blocks of park in xw direction
	int 	row_test;					// there are no buildings in the park
	int 	column_test;				// there are no buildings in the park
	float 	min_color			= 0.1;  // prevents black buildings
	float 	max_color			= 0.9;	// prevents white buildings
		
	set_rand_seed(15);  				// as the buildings' dimensions and colors are random, it's necessary to 
										// seed rand to keep these quantities the same at each run
										// if you leave this out, and change the number of samples per pixel,
										// these will change
	
	// the buildings are stored in a grid
	
	Grid* grid_ptr = new Grid;
	
	for (int r = 0; r < num_rows; r++)  			// xw direction
		for (int c = 0; c < num_columns; c++) {		// zw direction
			// determine if the block is in the park
		
			if ((r - num_rows / 2) >= 0)
				row_test = r -  num_rows / 2;
			else
				row_test = r -  num_rows / 2 + 1;
				
			if ((c - num_columns / 2) >= 0)
				column_test = c - num_columns / 2;
			else
				column_test = c - num_columns / 2 + 1;
			
			if (abs(row_test) >= (num_park_rows / 2) || abs(column_test) >= (num_park_columns / 2)) {
		
				auto matte_ptr = make_shared<Matte>();
				matte_ptr->set_ka(0.4); 
				matte_ptr->set_kd(0.6); 			
				matte_ptr->set_cd(	min_color + rand_float() * (max_color - min_color), 
									min_color + rand_float() * (max_color - min_color), 
									min_color + rand_float() * (max_color - min_color));    
				
				// block center coordinates
				
				float xc = a * (r - num_rows / 2.0 + 0.5);
				float zc = b * (c - num_columns / 2.0 + 0.5);
				
				width = min_size + rand_float() * (a - 2 * offset - min_size);
				length = min_size + rand_float() * (b - 2 * offset - min_size);	
				
				// minimum building coordinates
				
				float xmin = xc - width / 2.0;
				float ymin = 0.0;
				float zmin = zc - length / 2.0;
				
				// maximum building coordinates
				
				height = min_height + rand_float() * (max_height - min_height);
				
				// The following is a hack to make the middle row and column of buildings higher
				// on average than the other buildings. 
				// This only works properly when there are three rows and columns of buildings
				
				if (r == 1 || r == num_rows - 2 || c == 1 || c == num_columns - 2)
					height *= 1.5;
				
				float xmax = xc + width / 2.0;
				float ymax = height;
				float zmax = zc + length / 2.0;
				
				Box* building_ptr = new  Box(Point3D(xmin, ymin, zmin), Point3D(xmax, ymax, zmax));
				building_ptr->set_material(matte_ptr);
				grid_ptr->add_object(building_ptr);
			}
		}
		
	grid_ptr->setup_cells();
	add_object(grid_ptr);
	
	
	// render the park with small green checkers
	
	Checker3D* checker3D_ptr1 = new Checker3D;
	checker3D_ptr1->set_size(5); 
	checker3D_ptr1->set_color1(0.35, 0.75, 0.35);  
	checker3D_ptr1->set_color2(0.3, 0.5, 0.3);
	
	Box* park_ptr = new Box( 	Point3D(-a * num_park_rows / 2, 0.0, -b * num_park_columns / 2), 
								Point3D(a * num_park_rows / 2, 0.1, b * num_park_columns / 2)  );										
	park_ptr->set_material(make_shared<SV_Matte>(0.3, 0.5, checker3D_ptr1));
	add_object(park_ptr);
											
	
	// ground plane with checker:
	
	Checker3D* checker3D_ptr2 = new Checker3D;
	checker3D_ptr2->set_size(50); 
	checker3D_ptr2->set_color1(RGBColor(0.7));  
	checker3D_ptr2->set_color2(RGBColor(1));
	
	Plane* plane_ptr = new Plane(Point3D(0, 0.01, 0), Normal(0, 1, 0));
	plane_ptr->set_material(make_shared<SV_Matte>(0.3, 0.4, checker3D_ptr2));
	add_object(plane_ptr);

	
	Image* image_ptr = new Image;
	image_ptr->read_ppm_file("assets/CloudsSmall.ppm");
	
	SphericalMap* spherical_map_ptr = new SphericalMap; 
	
	ImageTexture* image_texture_ptr = new ImageTexture(image_ptr); 
	image_texture_ptr->set_mapping(spherical_map_ptr); 
	
	Sphere* unit_sphere_ptr = new Sphere;
	unit_sphere_ptr->set_shadows(false);	
	
	Instance* sphere_ptr = new Instance(unit_sphere_ptr); 
	sphere_ptr->scale(1000000);
	sphere_ptr->set_material(make_shared<SV_Matte>(1.0, 0.85, image_texture_ptr));
	add_object(sphere_ptr);
}
