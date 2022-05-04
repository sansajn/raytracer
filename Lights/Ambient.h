#pragma once
#include "Light.h"

class Ambient: public Light {
public:
	Ambient(void);

	void scale_radiance(const float b);
	void set_color(const float c);
	void set_color(const RGBColor& c);
	void set_color(const float r, const float g, const float b);

	Vector3D	get_direction(ShadeRec& s) override;
	RGBColor L(ShadeRec& s) override;

	// Copy API.
	Light * clone(void) const override;
	Ambient(const Ambient& a);
	Ambient & operator=(const Ambient& rhs);

	~Ambient() = default;
	
private:
	float		ls;
	RGBColor	color;
};


// ------------------------------------------------------------------------------- scale_radiance

inline void
Ambient::scale_radiance(const float b) { 
	ls = b;
}

// ------------------------------------------------------------------------------- set_color

inline void
Ambient::set_color(const float c) {
	color.r = c; color.g = c; color.b = c;
}


// ------------------------------------------------------------------------------- set_color

inline void
Ambient::set_color(const RGBColor& c) {
	color = c;
}


// ------------------------------------------------------------------------------- set_color

inline void
Ambient::set_color(const float r, const float g, const float b) {
	color.r = r; color.g = g; color.b = b;
}
