//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.

#include <cmath>
#include "Checker3D.h"
#include "Utilities/Constants.h"
#include "Utilities/RGBColor.h"

Checker3D::Checker3D(void)
    : Texture(),
		color1(white),
		color2(0.5),
		size(1.0)
{}

Checker3D::Checker3D(const Checker3D& sc)
    : Texture(sc),
      color1(sc.color1),
		color2(sc.color2),
		size(sc.size)
{}

Checker3D&
Checker3D::operator= (const Checker3D& rhs) {
    if (this == &rhs){
        return (*this);
    }

    Texture::operator=(rhs);

    size        = rhs.size;
    color1      = rhs.color1;
    color2      = rhs.color2;

    return (*this);
}

Checker3D*
Checker3D::clone(void) const {
    return (new Checker3D(*this));
}

Checker3D::~Checker3D(void) {}

RGBColor
Checker3D::get_color(const ShadeRec& sr) const {
    double eps = -0.000187453738;	// small random number
    double x = sr.local_hit_point.x + eps;
    double y = sr.local_hit_point.y + eps;
    double z = sr.local_hit_point.z + eps;

    if (((int)floor(x / size) + (int)floor(y / size) + (int)floor(z / size)) % 2 == 0) {
        return (color1);
    }
    else {
        return (color2);
    }
}
