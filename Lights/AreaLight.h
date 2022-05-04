#pragma once

#include "RGBColor.h"
#include "Vector3D.h"
#include "Point3D.h"
#include "Normal.h"
#include "Light.h"
#include "Material.h"
#include "GeometricObject.h"

class AreaLight: public Light {	
public:
	AreaLight();

	void set_object(std::unique_ptr<GeometricObject> o);

	Vector3D get_direction(ShadeRec& s) override;
	RGBColor L(ShadeRec& sr) override;
	bool in_shadow(const Ray& ray, const ShadeRec& sr) const override;
	float G(const ShadeRec& sr) const override;
	float pdf(const ShadeRec& sr) const override;

	// Copy API.
	AreaLight * clone() const override;
	AreaLight(const AreaLight& al);
	AreaLight &	operator=(const AreaLight& rhs);

	~AreaLight() = default;

private:
	std::unique_ptr<GeometricObject>	object_ptr;
	Material const * material_ptr;  // will be an emissive material, owned by object_ptr
	Point3D sample_point;
	Normal light_normal;  // assigned in get_direction - which therefore can't be const for any light
	Vector3D	wi;  // unit direction from hit point being shaded to sample point on light surface
};
