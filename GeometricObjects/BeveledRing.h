// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#pragma once

#include "Compound.h"
#include "Disk.h"

class BeveledRing: public Compound {
public:
	BeveledRing(void);
	BeveledRing(const double bottom, const double top, const double i_radius, const double o_radius, const double b_radius);

	bool hit(const Ray& ray, double& tmin, ShadeRec& s) const override;
	bool shadow_hit(const Ray& ray, double & tmin) const override;

	virtual void set_bottom_material(std::shared_ptr<Material> material_ptr);	//19.29
	virtual void set_top_material(std::shared_ptr<Material> material_ptr);	//19.29
	virtual void set_inner_wall_material(std::shared_ptr<Material> material_ptr);	//19.29
	virtual void set_outer_wall_material(std::shared_ptr<Material> material_ptr);	//19.29

	BBox get_bounding_box() override;

	BeveledRing * clone() const override;
	BeveledRing(const BeveledRing& cc);

private:
	BBox		bbox;	// the bounding box
};
