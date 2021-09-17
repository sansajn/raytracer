#ifndef __GEOMETRIC_OBJECT__
#define __GEOMETRIC_OBJECT__

class Material;

#include <memory>
#include "Point3D.h"
#include "Ray.h"
#include "ShadeRec.h"
#include "Samplers/Sampler.h"


//----------------------------------------------------------------------------------------------------- Class GeometricObject

class GeometricObject {	
	
	public:	
		GeometricObject();
			
		virtual bool hit(const Ray& ray, double& t, ShadeRec& s) const = 0;
				
		Material * get_material() const;

		virtual void 							// needs to virtual so that it can be overriden in Compound
		set_material(Material* mPtr); 			

		RGBColor const & get_color() const;
		void set_color(RGBColor const & c);
		void set_color(float r, float g, float b);

		virtual bool shadow_hit(Ray const & ray, double & tmin) const = 0;

		// Area Lights API
		virtual void set_sampler(std::shared_ptr<Sampler> sampler);
		virtual Point3D sample();
		virtual Normal get_normal(Point3D const & p);
		virtual float pdf(ShadeRec const & sr) const;

		virtual GeometricObject * clone() const = 0;
		GeometricObject(GeometricObject const & object);

		virtual ~GeometricObject();

	protected:
		GeometricObject&						// assignment operator
		operator= (const GeometricObject& rhs);

	private:
		mutable Material*   material_ptr;   	// mutable allows Compound::hit, Instance::hit and Grid::hit to assign to material_ptr. hit functions are const
		RGBColor color;
};


// ------------------------------------------------------------------------- get_material

inline Material* 
GeometricObject::get_material(void) const {
	return (material_ptr);
}

#endif
