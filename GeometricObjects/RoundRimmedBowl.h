// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This file contains the declaration of the class RoundRimmedBowl
// The bowl is centered on the world origin

#pragma once
#include <memory>
#include "Compound.h"

class RoundRimmedBowl: public Compound {
public:
	RoundRimmedBowl(void);
	RoundRimmedBowl(	const double inner_radius, const double outer_radius);
	RoundRimmedBowl(	const double inner_radius, const double outer_radius, const double openning_angle);

	virtual RoundRimmedBowl & operator=(const RoundRimmedBowl& rhs);

	virtual
	~RoundRimmedBowl(void);

	void
	build_components(void);

	void set_material(std::shared_ptr<Material> m_ptr) override;


	RoundRimmedBowl * clone() const override;
	RoundRimmedBowl(const RoundRimmedBowl& fb);

protected:
	double inner_radius;		// radius of the inside glass surface
	double outer_radius;
	double openning;
};
