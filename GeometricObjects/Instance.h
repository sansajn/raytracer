#ifndef __INSTANCE__
#define __INSTANCE__

// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This includes a bounding box, instead of computing it. 
// This uses extra memory but the object to be transformed may be a grid or some other complex object
// whose bouding box is expensive to compute.

#include <memory>
#include "GeometricObject.h"
#include "Matrix.h"

class Instance: public GeometricObject {	
	public:
		
		Instance();
		Instance(std::shared_ptr<GeometricObject> obj_ptr);
		
		Instance * clone() const override;
		Instance(const Instance& instance);
		Instance & operator=(const Instance& rhs);
				
		void set_object(std::shared_ptr<GeometricObject> obj_ptr);

		Material const * get_material() const override;
		void get_material(std::shared_ptr<Material> & m) const override;
		void set_material(std::shared_ptr<Material> m) override;
		
		void transform_texture(const bool transform);
			
		virtual void compute_bounding_box();
		virtual BBox get_bounding_box();
											
		bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const override;
		bool shadow_hit(const Ray& ray, double& tmin) const override;
		
		// affine tranformation functions

		void translate(const Vector3D& trans);
		void scale(const Vector3D& s);
		virtual void rotate_x(const double r);
		virtual void rotate_y(const double r);
		virtual void rotate_z(const double r);
		void shear(const Matrix& m);
		
	private:
		std::shared_ptr<GeometricObject> object_ptr;				// object to be transformed
		Matrix				inv_matrix;		    	// inverse transformation matrix
		static 	Matrix		forward_matrix; 		// transformation matrix
		BBox				bbox;					// transformed object's bounding box
		bool				transform_the_texture;	// do we transform the texture?
};


inline void
Instance::transform_texture(const bool transform) {
	transform_the_texture = transform;
}	

#endif