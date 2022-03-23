// 	Copyright (C) Mp77 2012
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

//BeveledBox class only used in Listing 8.22, Here I have implemented a simple demo, and It seems to be OK according to source pictures.

#pragma once
#include "Compound.h"
#include "Instance.h"

class BeveledBox: public Compound {
public:
	BeveledBox();

	BeveledBox(const Point3D	bottom_,
				  const Point3D 	top_,
				  const float	bevel_radius);

	bool hit(const Ray& ray, double& tmin, ShadeRec& s) const override;
	bool shadow_hit(const Ray& ray, double & tmin) const override;
	void set_material(std::shared_ptr<Material> material_ptr) override;

	BBox get_bounding_box() override;

	// Copy API.
	BeveledBox * clone(void) const override;
	BeveledBox & operator=(const BeveledBox& c);
	BeveledBox(const BeveledBox& cc);

	~BeveledBox (void);
	
private:
	
	void
	delete_objects(void);

	void
	copy_objects(const std::vector<Instance*>& rhs_objects);

	BBox		bbox;	// the bounding box

	Point3D p0;
	Point3D p1;
	float br;

	std::vector<Instance*> parts;	//we build each arris of the whole wireframebox
};
