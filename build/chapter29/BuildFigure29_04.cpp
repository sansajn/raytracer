// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This builds the scene for Figure 29.4

#include "World/World.h"
#include "Tracers/RayCast.h"
#include "Cameras/Pinhole.h"
#include "Lights/Directional.h"
#include "Utilities/Image.h"
#include "Mappings/RectangularMap.h"
#include "Textures/ImageTexture.h"
#include "Materials/Matte.h"
#include "Materials/SV_Matte.h"
#include "GeometricObjects/Rectangle.h"
#include "GeometricObjects/Instance.h"
#include "GeometricObjects/Plane.h"

using std::make_unique, std::move, std::make_shared;

void World::build() {
	constexpr int num_samples = 16;
	
	vp.set_hres(400);
	vp.set_vres(400); 
	vp.set_samples(num_samples);
	vp.set_max_depth(0);
		
	background_color = RGBColor(0.0);
	
	tracer_ptr = new RayCast(this);
	
	auto pinhole_ptr = make_unique<Pinhole>();
	pinhole_ptr->set_eye({5, 1.5, 8});
	pinhole_ptr->set_lookat({0.25, 0.0, 0.0});
	pinhole_ptr->set_view_distance(1000.0);
	pinhole_ptr->compute_uvw();
	set_camera(move(pinhole_ptr));
	
	Directional* light_ptr = new Directional;
	light_ptr->set_direction(-15, 20, 25);  
	light_ptr->scale_radiance(2.5);  
	light_ptr->set_shadows(true);
	add_light(light_ptr);
	
	// image:

	Image* image_ptr = new Image;					
	image_ptr->read_ppm_file("assets/Lightlace.ppm");
	
	// mapping:
	
	RectangularMap* map_ptr = new RectangularMap;
	
	// image texture:
	
	ImageTexture* texture_ptr = new ImageTexture(image_ptr); 
	texture_ptr->set_mapping(map_ptr);
	
	// spatially varying material:
		
	auto sv_matte_ptr = make_shared<SV_Matte>();
	sv_matte_ptr->set_ka(0.40);
	sv_matte_ptr->set_kd(0.95);
	sv_matte_ptr->set_cd(texture_ptr);
	
	// generic rectangle:
	
	auto rectangle_ptr = make_shared<Rectangle>();
	rectangle_ptr->set_material(sv_matte_ptr);
	
	// transformed rectangle:
	
	Instance* lightlace_ptr = new Instance(rectangle_ptr);  
	lightlace_ptr->scale({1.0, 1.0, 1.5});
	lightlace_ptr->rotate_z(90);
	lightlace_ptr->rotate_y(90);
	add_object(lightlace_ptr);
	
	// ground plane
	Plane* plane_ptr = new Plane(Point3D(0.0, -1.0, 0.0), Normal(0.0, 1.0, 0.0));
	plane_ptr->set_material(make_shared<Matte>(.25, .5, white));
	add_object(plane_ptr);
}
