#pragma once
#include <memory>
#include "Material.h"
#include "Lambertian.h"

//----------------------------------------------------------------------------- class Matte

/*! Material without specular reflection.
\note Supports area lighting. */
class Matte: public Material {	
public:
	Matte();
	Matte(float ka, float kd, RGBColor const & cd);
	void set_ka(float k);  //!< ambient light coefficient
	void set_kd(float k);  //!< diffuse light coefficient
	void set_cd(RGBColor c);  //!< ambient and diffuse light color
	RGBColor shade(ShadeRec& sr) const override;
	RGBColor area_light_shade(ShadeRec & sr) const override;

	// Copy API.
	Matte(Matte const & m);
	Matte & operator= (const Matte& rhs);
	Material * clone() const override;

private:
	std::unique_ptr<Lambertian> ambient_brdf,
		diffuse_brdf;
};


// ---------------------------------------------------------------- set_ka
// this sets Lambertian::kd
// there is no Lambertian::ka data member because ambient reflection 
// is diffuse reflection

inline void								
Matte::set_ka(float ka) {
	ambient_brdf->set_kd(ka);
}


// ---------------------------------------------------------------- set_kd
// this also sets Lambertian::kd, but for a different Lambertian object

inline void								
Matte::set_kd (float kd) {
	diffuse_brdf->set_kd(kd);
}


// ---------------------------------------------------------------- set_cd

inline void												
Matte::set_cd(RGBColor c) {
	ambient_brdf->set_cd(c);
	diffuse_brdf->set_cd(c);
}
