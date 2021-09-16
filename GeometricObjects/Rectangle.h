#ifndef __RECTANGLE__
#define __RECTANGLE__

// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "Sampler.h"
#include "GeometricObject.h"
#include "Utilities/BBox.h"

class Rectangle: public GeometricObject {	
public:
	Rectangle(void);
	Rectangle(const Point3D& _p0, const Vector3D& _a, const Vector3D& _b);
	Rectangle(const Point3D& _p0, const Vector3D& _a, const Vector3D& _b, const Normal& n);
	Rectangle *	clone() const override;
	Rectangle(const Rectangle& r);

	~Rectangle() = default;

	Rectangle&
	operator= (const Rectangle& rhs);

	BBox
	get_bounding_box(void);
	
	bool hit(Ray const & ray, double & t, ShadeRec & s) const override;
	bool shadow_hit(Ray const & ray, double & tmin) const override;

	// the following functions are used when the rectangle is a light source

	void set_sampler(std::shared_ptr<Sampler> sampler) override;
	Point3D sample() override;
	Normal get_normal(const Point3D& p) override;
	float	pdf(ShadeRec const & sr) const override;

private:
	Point3D 		p0;   			// corner vertex
	Vector3D		a;				// side
	Vector3D		b;				// side
	double			a_len_squared;	// square of the length of side a
	double			b_len_squared;	// square of the length of side b
	Normal			normal;

	float			area;			// for rectangular lights
	float			inv_area;		// for rectangular lights
	std::shared_ptr<Sampler> sampler_ptr;  // for rectangular lights

	static const double kEpsilon;
};

#endif
