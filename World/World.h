#ifndef __WORLD__
#define __WORLD__


// This file contains the declaration of the class World
// The World class does not have a copy constructor or an assignment operator, for the followign reasons:

// 1 	There's no need to copy construct or assign the World
// 2 	We wouldn't want to do this anyway, because the world can contain an arbitray amount of data
// 3 	These operations wouldn't work because the world is self-referencing:
//	 	the Tracer base class contains a pointer to the world. If we wrote a correct copy constructor for the 
// 	  	Tracer class, the World copy construtor would call itself recursively until we ran out of memory. 


#include <memory>
#include <vector>
#include <cstdint>
#include "ViewPlane.h"
#include "RGBColor.h"
#include "Tracers/MultipleObjects.h"
#include "GeometricObject.h"
#include "Sphere.h"
#include "Ray.h"
#include "SingleSphere.h"
#include "Camera.h"
#include "Light.h"
#include "Ambient.h"

class World {	
	public:
	
		ViewPlane					vp;
		RGBColor					background_color;
		Tracer*						tracer_ptr;
		Light*   					ambient_ptr;
		Sphere 						sphere;		// for Chapter 3 only
		std::vector<GeometricObject*>	objects;
		std::vector<Light*> 				lights;
		
		mutable std::vector<uint8_t> pixels;
			

	public:
	
		World();
		
		~World();
								
		void 
		add_object(GeometricObject* object_ptr);
		
		void 
		add_light(Light* light_ptr); 
		
		void
		set_ambient_light(Light* light_ptr);			
		
		Camera * camera() const;  // TODO: should I return unique_ptr& rather then *?
		void set_camera(std::unique_ptr<Camera> c);

		void 					
		build(void);

		void 												
		render_scene(void) const;  //!< \note it looks like this is only used in case scene doesn't contains camera
						
		RGBColor
		max_to_one(const RGBColor& c) const;
		
		RGBColor
		clamp_to_color(const RGBColor& c) const;
		
		void
		display_pixel(const int row, const int column, const RGBColor& pixel_color) const;

		ShadeRec
		hit_objects(const Ray& ray);

		ShadeRec
		hit_bare_bones_objects(const Ray &ray);  //!< \note the function is only used in chapter 3

		void
		save_to_ppm(void) const;

		void save_to_png() const;
						
	private:
		
		void 
		delete_objects(void);
		
		void 
		delete_lights(void);

		std::unique_ptr<Camera> _camera;  // TODO: use unique_ptr to make ownership clear
};


// ------------------------------------------------------------------ add_object

inline void 
World::add_object(GeometricObject* object_ptr) {  
	objects.push_back(object_ptr);	
}


// ------------------------------------------------------------------ add_light

inline void 
World::add_light(Light* light_ptr) {  
	lights.push_back(light_ptr);
}


// ------------------------------------------------------------------ set_ambient_light

inline void
World::set_ambient_light(Light* light_ptr) {
	ambient_ptr = light_ptr;
}


// ------------------------------------------------------------------ set_camera


#endif
