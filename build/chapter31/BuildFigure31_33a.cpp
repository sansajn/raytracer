// 	Copyright (C) Kevin Suffern 2000-2008.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This builds the scene for Figure 31.33

// The perturbation amounts (values of a) are different from those used in 
// Figure 31.33 in the book. The original images used a fractal sum function whose
// output was not normalised to the range [0, 1]. In the original function,
// adding more octaves produced a larger range. Because the noise used here 
// has 6 octaves, larger perturbation amounts are needed to produce similar
// results.

#include "World/World.h"
#include "Tracers/RayCast.h"
#include "Cameras/Pinhole.h"
#include "Lights/PointLight.h"
#include "Noise/CubicNoise.h"
#include "Textures/RampFBmTexture.h"
#include "Materials/SV_Matte.h"
#include "Utilities/Image.h"
#include "GeometricObjects/Instance.h"

using std::make_unique, std::move, std::make_shared;

void World::build() {
	constexpr int num_samples = 16;
	
	vp.set_hres(600);     
	vp.set_vres(600);
	vp.set_samples(num_samples);
	
	background_color = black;
	tracer_ptr = new RayCast(this);
	
	auto pinhole_ptr = make_unique<Pinhole>();
	pinhole_ptr->set_eye({0, 0, 100});
	pinhole_ptr->set_lookat(Point3D{0});
	pinhole_ptr->set_view_distance(5800.0);
	pinhole_ptr->compute_uvw();     
	set_camera(move(pinhole_ptr));
	
	
	PointLight* light_ptr = new PointLight;
	light_ptr->set_location({20, 20, 40});
	light_ptr->scale_radiance(2.5);
	add_light(light_ptr);

	
	// noise:
	
	CubicNoise* noise_ptr = new CubicNoise;	
	noise_ptr->set_num_octaves(6);
	noise_ptr->set_gain(0.5);	
	noise_ptr->set_lacunarity(2.0);		

	// ramp image:
	
	Image* image_ptr = new Image;						
	image_ptr->read_ppm_file("assets/BlueMarbleRamp.ppm");
	
	// marble texture:	
		
	RampFBmTexture* marble_ptr = new RampFBmTexture(image_ptr);
	marble_ptr->set_noise(noise_ptr);
	marble_ptr->set_perturbation(4.0);		// for Figure 31.33(a)
//	marble_ptr->set_perturbation(8.0);		// for Figure 31.33(b)
//	marble_ptr->set_perturbation(30.0);		// for Figure 31.33(c)

	// material:
		
	auto sv_matte_ptr = make_shared<SV_Matte>();
	sv_matte_ptr->set_ka(0.25);
	sv_matte_ptr->set_kd(0.9);
	sv_matte_ptr->set_cd(marble_ptr);

	
	Instance* sphere_ptr1 = new Instance(make_shared<Sphere>(Point3D(0.0), 5.0));
	sphere_ptr1->set_material(sv_matte_ptr);
	sphere_ptr1->rotate_y(180);
	add_object(sphere_ptr1);
}
