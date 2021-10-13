#pragma once
#include <memory>
#include "Point3D.h"
#include "Ray.h"
#include "ShadeRec.h"
#include "Samplers/Sampler.h"
#include "Materials/Material.h"
#include "Utilities/BBox.h"
#include "Utilities/Normal.h"

class GeometricObject {
public:
	GeometricObject() = default;

	virtual bool hit(Ray const & ray, double & t, ShadeRec & sr) const = 0;
	virtual bool shadow_hit(Ray const & ray, double & tmin) const = 0;

	Material const * get_material() const;
	void get_material(std::shared_ptr<Material> & m) const;
	virtual void set_material(std::shared_ptr<Material> mPtr);
	RGBColor const & get_color() const;
	void set_color(RGBColor const & c);
	void set_color(float r, float g, float b);

	// Area Lights API
	virtual void set_sampler(std::shared_ptr<Sampler> sampler);
	virtual Point3D sample();
	virtual Normal get_normal(Point3D const & p);
	virtual float pdf(ShadeRec const & sr) const;

	virtual BBox get_bounding_box();  // allows acceleration schema
	virtual void add_object(GeometricObject * object);  // allows compound objects
	virtual Normal get_normal() const;  // smoothing triangles

	virtual GeometricObject * clone() const = 0;

	GeometricObject(GeometricObject const & object);

	virtual ~GeometricObject() = default;

protected:
	GeometricObject & operator=(GeometricObject const & rhs);

	mutable std::shared_ptr<Material> material_ptr;   	// mutable allows Compound::hit, Instance::hit and Grid::hit to assign to material_ptr. hit functions are const

private:
	RGBColor color;
};
