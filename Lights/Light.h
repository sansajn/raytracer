#pragma once
#include "Vector3D.h"
#include "RGBColor.h"
#include "Ray.h"
#include "ShadeRec.h"

class Light {	
public:
	Light();

	bool casts_shadows() const;
	void set_shadows(bool shadows);
	virtual RGBColor L(ShadeRec & sr);
	virtual float G(ShadeRec const & sr) const;
	virtual bool in_shadow(Ray const & ray, ShadeRec const & sr) const;
	virtual Vector3D get_direction(ShadeRec& sr) = 0;
	virtual float pdf(ShadeRec const & sr) const;

	virtual Light * clone() const = 0;

	Light(const Light& ls);
	Light & operator=(const Light& rhs);
	virtual ~Light() = default;

protected:
	bool _shadows;
};
