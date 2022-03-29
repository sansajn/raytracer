//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.

//  Copyright notice for changes since the originally published version:
//  Copyright (C) Eduárd Mándy 2019-2021
//  Though this C++ code was change in a large measure it still has the original copyright notice.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.

#pragma once
#include "../Utilities/ShadeRec.h"
#include "../Utilities/RGBColor.h"

class Texture {
public:
	Texture() = default;

	virtual RGBColor get_color(const ShadeRec& sr) const = 0;

	// Copy API.
	Texture(const Texture& texture);
	Texture & operator=(const Texture& rhs);
	virtual Texture* clone(void) const = 0;

	virtual ~Texture() = default;
};
