#ifndef __LIGHT__
#define __LIGHT__

#include "Vector3D.h"
#include "RGBColor.h"
#include "Ray.h"

class ShadeRec;


//-------------------------------------------------------------------- class Light

class Light {	
	public:
	
		Light(void);
								
		Light(const Light& ls);			

		Light& 								
		operator= (const Light& rhs); 

		virtual Light* 						
		clone(void) const = 0;
		
		virtual 							
		~Light(void);
						
		virtual Vector3D								
		get_direction(ShadeRec& sr) = 0;

		bool casts_shadows() const;
		void set_shadows(bool shadows);
		virtual bool in_shadow(Ray const & ray, ShadeRec const & sr) const;
																
		virtual RGBColor														
		L(ShadeRec& sr);

		virtual float G(ShadeRec & sr) const;

	protected:
		bool _shadows;
};

#endif
