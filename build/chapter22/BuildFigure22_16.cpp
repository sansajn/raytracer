// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figure 22.16
// This will render a uniform brown image as in Figure 22.16(a)
// To render Figure 22.16(b) you will have to alter the Grid code
// as described in Question 22.6
// The LightProbe mapping is discussed in Chapter 29
// The map type panoramic is declared in LightProbe.h, which is #included in World.h

#include "World/World.h"
#include "Tracers/RayCast.h"
#include "Cameras/Pinhole.h"
#include "Lights/PointLight.h"
#include "Materials/SV_Matte.h"
#include "Materials/Matte.h"
#include "Textures/LightProbe.h"
#include "Textures/ImageTexture.h"
#include "GeometricObjects/Box.h"
#include "GeometricObjects/Grid.h"
#include "GeometricObjects/Instance.h"
#include "Utilities/Image.h"
#include "Utilities/Random.h"

using std::make_unique, std::make_shared, std::move;

void World::build() {
	constexpr int num_samples = 1;
	
	vp.set_hres(600);			
	vp.set_vres(600); 
	vp.set_samples(num_samples);
	
	tracer_ptr = new RayCast(this);	
	
	auto pinhole_ptr = make_unique<Pinhole>();
	pinhole_ptr->set_eye({0.05, 0.06, 0.07});
	pinhole_ptr->set_lookat({0.1, 0.1, -10.0});
	pinhole_ptr->set_view_distance(80);
	pinhole_ptr->compute_uvw(); 
	set_camera(move(pinhole_ptr));
	
	
	PointLight* light_ptr = new PointLight;
	light_ptr->set_location(Point3D{0});
	light_ptr->scale_radiance(3.0);
	light_ptr->set_shadows(false);
	add_light(light_ptr);

	
	// the box
			
	auto matte_ptr = make_shared<Matte>();
	matte_ptr->set_ka(0.2); 
	matte_ptr->set_kd(0.5);
	matte_ptr->set_cd(RGBColor{1.0, 0.75, 0.25});  // brown
	
	Point3D p0(-10);
	Point3D p1(10);
	
	Box* box_ptr = new Box(p0, p1);	
	box_ptr->set_material(matte_ptr);

	Grid* grid_ptr = new Grid();
	grid_ptr->add_object(box_ptr);
	grid_ptr->setup_cells();
	add_object(grid_ptr);
		
	Image* image_ptr = new Image;
//	image_ptr->read_ppm_file("uffizi_probe_small.ppm");  // for testing 
	image_ptr->read_ppm_file("assets/uffizi_probe.ppm");  // for production

	LightProbe* light_probe_ptr = new LightProbe;
	light_probe_ptr->set_map_type(panoramic);     		
	
	ImageTexture* image_texture_ptr = new ImageTexture(image_ptr); 
	image_texture_ptr->set_mapping(light_probe_ptr);
	
	auto sv_matte_ptr = make_shared<SV_Matte>();
	sv_matte_ptr->set_ka(1);
	sv_matte_ptr->set_kd(0.85);  
	sv_matte_ptr->set_cd(image_texture_ptr);
	
	auto unit_sphere_ptr = make_shared<Sphere>();
	unit_sphere_ptr->set_shadows(false);	
	
	Instance* large_sphere_ptr = new Instance(unit_sphere_ptr); 
	large_sphere_ptr->scale(Vector3D{1000000.0});
	large_sphere_ptr->set_material(sv_matte_ptr);
	add_object(large_sphere_ptr);
}
