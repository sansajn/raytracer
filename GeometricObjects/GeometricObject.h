#pragma once
#include <memory>
#include "Point3D.h"
#include "Ray.h"
#include "ShadeRec.h"
#include "Samplers/Sampler.h"
#include "Materials/Material.h"
#include "Utilities/BBox.h"

class GeometricObject {
public:
	GeometricObject();

	virtual bool hit(Ray const & ray, double & t, ShadeRec & sr) const = 0;
	virtual bool shadow_hit(Ray const & ray, double & tmin) const = 0;

	Material * get_material() const;
	virtual void set_material(Material * mPtr);
	RGBColor const & get_color() const;
	void set_color(RGBColor const & c);
	void set_color(float r, float g, float b);

	// Area Lights API
	virtual void set_sampler(std::shared_ptr<Sampler> sampler);
	virtual Point3D sample();
	virtual Normal get_normal(Point3D const & p);
	virtual float pdf(ShadeRec const & sr) const;

	// Acceleration API
	virtual BBox get_bounding_box();

	// Compound API
	virtual void add_object(GeometricObject * object);

	virtual GeometricObject * clone() const = 0;

	GeometricObject(GeometricObject const & object);

	virtual ~GeometricObject();

protected:
	GeometricObject & operator=(GeometricObject const & rhs);

	mutable Material * material_ptr;   	// mutable allows Compound::hit, Instance::hit and Grid::hit to assign to material_ptr. hit functions are const

private:
	RGBColor color;
};

inline Material* 
GeometricObject::get_material(void) const {
	return (material_ptr);
}
