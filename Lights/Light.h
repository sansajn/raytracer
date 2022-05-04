#pragma once
#include "Vector3D.h"
#include "RGBColor.h"
#include "Ray.h"
#include "ShadeRec.h"

class Light {	
public:
	Light();

	bool casts_shadows() const;  // TODO: rename to cast_shadows?
	void set_shadows(bool shadows);
	virtual RGBColor L(ShadeRec & sr);
	virtual bool in_shadow(Ray const & ray, ShadeRec const & sr) const;
	virtual Vector3D get_direction(ShadeRec& sr) = 0;
	virtual float pdf(ShadeRec const & sr) const;  //!< Area shading support. \sa AreaLight
	virtual float G(ShadeRec const & sr) const;  //!< Area shading support. \sa AreaLight

	// Copy API.
	virtual Light * clone() const = 0;
	Light & operator=(Light const & rhs);

	virtual ~Light() = default;

protected:
	bool _shadows;
};
