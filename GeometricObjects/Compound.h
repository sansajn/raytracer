#ifndef __COMPOUND__
#define __COMPOUND__

// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include <vector> 
#include "GeometricObject.h"

//-------------------------------------------------------------------------------- class Compound

class Compound: public GeometricObject {	
public:
	Compound();

	void set_material(Material* material_ptr) override;
	virtual void add_object(GeometricObject * object_ptr);
	int get_num_objects(void);

	bool hit(const Ray& ray, double& tmin, ShadeRec& s) const override;
	bool shadow_hit(Ray const & ray, double & tmin) const override;

	Compound * clone() const override;

	Compound(const Compound& c);
	Compound & operator=(const Compound& c);
	~Compound();

protected:
	std::vector<GeometricObject*> objects;

private:
	void delete_objects();
	void copy_objects(const std::vector<GeometricObject*>& rhs_objects);
};


// ------------------------------------------------------------------------------- get_num_objects

inline int
Compound::get_num_objects(void) {
	return (objects.size());
}

#endif
