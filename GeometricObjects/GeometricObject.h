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
	GeometricObject();

	virtual bool hit(Ray const & ray, double & tmin, ShadeRec & sr) const = 0;
	virtual bool shadow_hit(Ray const & ray, double & tmin) const = 0;
	virtual GeometricObject * clone() const = 0;

	bool casts_shadows() const;
	void set_shadows(bool shadows);

	// material API needs to be virtual due to Instance implementation
	virtual Material const * get_material() const;
	virtual void get_material(std::shared_ptr<Material> & m) const;
	virtual void set_material(std::shared_ptr<Material> mPtr);  //!< \note we do not want all objects look the same so maybe material shuold be unique

	RGBColor const & get_color() const;
	void set_color(RGBColor const & c);
	void set_color(float r, float g, float b);

	/*! \name Area Lights API.
	The following functions are used when the geometric-object is a light source */
	//! \{
	virtual void set_sampler(std::shared_ptr<Sampler> sampler);  //!< \bug sampler can not be shared, because implementations calls map_samples_XX function, which can make sampler unusable every time set_sampler called
	virtual Point3D sample();
	virtual Normal get_normal(Point3D const & p);  //!< \param [in] p Point on surface (\sa sample()).
	virtual float pdf(ShadeRec const & sr) const;
	//! \}

	virtual BBox get_bounding_box();  // allows acceleration schema
	virtual void add_object(GeometricObject * object);  // allows compound objects
	virtual Normal get_normal() const;  // smoothing triangles

	virtual ~GeometricObject() = default;

protected:
	GeometricObject & operator=(GeometricObject const & rhs);

	mutable std::shared_ptr<Material> material_ptr;   	// mutable allows Compound::hit, Instance::hit and Grid::hit to assign to material_ptr. hit functions are const

private:
	bool _shadows;
	RGBColor color;
};
