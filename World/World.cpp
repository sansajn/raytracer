// this file contains the definition of the World class

#include <fstream>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <memory>
#include <cassert>

#include <Magick++.h>

#include "World.h"
#include "Constants.h"

// geometric objects

#include "Plane.h"
#include "Sphere.h"

// tracers

#include "SingleSphere.h"
#include "MultipleObjects.h"
#include "RayCast.h"

// cameras

#include "Pinhole.h"

// lights

#include "Directional.h"

// materials

#include "Matte.h"

// utilities

#include "Vector3D.h"
#include "Point3D.h"
#include "Normal.h"
#include "ShadeRec.h"
#include "Maths.h"

// build functions

//#include "BuildShadedObjects.cpp"

using std::unique_ptr;
using namespace Magick;


// -------------------------------------------------------------------- default constructor

// tracer_ptr is set to NULL because the build functions will always construct the appropriate tracer
// ambient_ptr is set to a default ambient light because this will do for most scenes
// camera_ptr is set to NULL because the build functions will always have to construct a camera
// and set its parameters

World::World()
	: background_color{black}
	, tracer_ptr{nullptr}
	, ambient_ptr{new Ambient}
{}



//------------------------------------------------------------------ destructor

World::~World(void) {

	if(tracer_ptr) {
		delete tracer_ptr;
		tracer_ptr = NULL;
	}


	if (ambient_ptr) {
		delete ambient_ptr;
		ambient_ptr = NULL;
	}

	delete_objects();
	delete_lights();
}


//------------------------------------------------------------------ render_scene

// This uses orthographic viewing along the zw axis

void World::render_scene() const {
	RGBColor	pixel_color;
	Ray			ray;
	int 		hres 	= vp.hres;
	int 		vres 	= vp.vres;
	float		s		= vp.s;
	float		zw		= 100.0;				// hardwired in

	ray.d = Vector3D(0, 0, -1);

	for (int r = 0; r < vres; r++)			// up
		for (int c = 0; c < hres; c++) {	// across
			ray.o = Point3D(s * (c - hres / 2.0 + 0.5), s * (r - vres / 2.0 + 0.5), zw);
			pixel_color = tracer_ptr->trace_ray(ray);
			display_pixel(r, c, pixel_color);
		}
}


// ------------------------------------------------------------------ clamp

RGBColor
World::max_to_one(const RGBColor& c) const  {
	float max_value = max(c.r, max(c.g, c.b));

	if (max_value > 1.0)
		return (c / max_value);
	else
		return (c);
}


// ------------------------------------------------------------------ clamp_to_color
// Set color to red if any component is greater than one

RGBColor World::clamp_to_color(const RGBColor& raw_color) const {
	if (raw_color.r > 1.0 || raw_color.g > 1.0 || raw_color.b > 1.0)
		return red;
	else
		return raw_color;
}


// ---------------------------------------------------------------------------display_pixel
// raw_color is the pixel color computed by the ray tracer
// its RGB floating point components can be arbitrarily large
// mapped_color has all components in the range [0, 1], but still floating point
// display color has integer components for computer display
// the Mac's components are in the range [0, 65535]
// a PC's components will probably be in the range [0, 255]
// the system-dependent code is in the function convert_to_display_color
// the function SetCPixel is a Mac OS function


void World::display_pixel(const int row, const int column, const RGBColor& raw_color) const {
	RGBColor mapped_color;

	if (vp.show_out_of_gamut)
		mapped_color = clamp_to_color(raw_color);
	else
		mapped_color = max_to_one(raw_color);

	if (vp.gamma != 1.0)
		mapped_color = mapped_color.powc(vp.inv_gamma);

/*
	//have to start from max y coordinate to convert to screen coordinates
	int x = column;
	int y = vp.vres - row - 1;

	paintArea->setPixel(x, y, (int)(mapped_color.r * 255),
									  (int)(mapped_color.g * 255),
									  (int)(mapped_color.b * 255));
*/
	pixels.push_back((int)(mapped_color.r * 255));
	pixels.push_back((int)(mapped_color.g * 255));
	pixels.push_back((int)(mapped_color.b * 255));
}

// ----------------------------------------------------------------------------- hit_objects

ShadeRec
World::hit_objects(const Ray& ray) {
	ShadeRec	sr{*this};
	Normal normal;
	Point3D local_hit_point;
	float	tmin = kHugeValue;

	for (auto const * object : objects) {
		if (double t; object->hit(ray, t, sr) && (t < tmin)) {
			sr.hit_an_object	= true;
			tmin = t;
			sr.material_ptr = object->get_material();
			assert(sr.material_ptr);
			sr.hit_point = ray.o + t * ray.d;
			normal = sr.normal;
			local_hit_point = sr.local_hit_point;
		}
	}

	if(sr.hit_an_object) {
		sr.t = tmin;
		sr.normal = normal;
		sr.local_hit_point = local_hit_point;
	}

	return sr;
}

ShadeRec
World::hit_bare_bones_objects(const Ray &ray) {
	ShadeRec	sr(*this);
	double		t;
	double		tmin = kHugeValue;
	size_t 		num_objects = objects.size();

	for ( size_t j = 0; j < num_objects; j++ ) {
		if ( objects[j]->hit(ray, t, sr) && (t < tmin) ) {
			sr.hit_an_object = true;
			tmin = t;
			sr.color = objects[j]->get_color();
		}
	}

	return(sr);
}


//------------------------------------------------------------------ save_to_ppm

void
World::save_to_ppm(void) const {
	std::time_t t = std::time(nullptr);
	std::tm tm = *std::localtime(&t);
	std::stringstream imageFile;
	imageFile << "./image_" << std::put_time(&tm, "%Y%m%e%H%M%S") << ".ppm";

	std::ofstream ofs;
	ofs.open(imageFile.str().c_str(), std::ios::out | std::ios::binary);
	ofs << "P6\n" << vp.hres << " " << vp.vres << "\n255\n";

	// images are stored from top to bottom so flip pixels
	for (int r = vp.vres-1; r >= 0; --r) {
		int idx = r*vp.vres*3;
		uint8_t * p = pixels.data() + idx;
		for (int c = 0; c < vp.hres; ++c) {
			ofs << *(p++);
			ofs << *(p++);
			ofs << *(p++);
		}
	}

	ofs.close();
}

void World::save_to_png() const {
	std::time_t t = std::time(nullptr);
	std::tm tm = *std::localtime(&t);
	std::stringstream fname;
	fname << "./image_" << std::put_time(&tm, "%Y%m%e%H%M%S") << ".png";

	Image im;
	im.read(vp.hres, vp.vres, "RGB", StorageType::CharPixel, pixels.data());
	im.flip();  // images are stored from top to bottom
	im.write(fname.str().c_str());
}


//------------------------------------------------------------------ delete_objects

// Deletes the objects in the objects array, and erases the array.
// The objects array still exists, because it's an automatic variable, but it's empty

void
World::delete_objects(void) {
	int num_objects = objects.size();

	for (int j = 0; j < num_objects; j++) {
		delete objects[j];
		objects[j] = NULL;
	}

	objects.erase (objects.begin(), objects.end());
}


//------------------------------------------------------------------ delete_lights

void
World::delete_lights(void) {
	int num_lights = lights.size();

	for (int j = 0; j < num_lights; j++) {
		delete lights[j];
		lights[j] = NULL;
	}

	lights.erase (lights.begin(), lights.end());
}

Camera * World::camera() const {
	return _camera.get();
}

void World::set_camera(unique_ptr<Camera> c) {
	_camera = move(c);
}
