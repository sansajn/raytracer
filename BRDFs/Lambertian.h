#pragma once
#include "BRDF.h"

class Lambertian: public BRDF {
	public:
	
		Lambertian(void);
		
		Lambertian(const Lambertian& lamb);
		
		virtual Lambertian*
		clone(void) const;
		
		~Lambertian(void);
		
		Lambertian& 
		operator= (const Lambertian& rhs);
		
		virtual RGBColor
		f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const;
		
		virtual RGBColor
		rho(const ShadeRec& sr, const Vector3D& wo) const;
			
		void
		set_ka(const float ka);	
				
		void
		set_kd(const float kd);
		
		void
		set_cd(const RGBColor& c);

	private:
		float		kd;
		RGBColor 	cd;
};


// -------------------------------------------------------------- set_ka

inline void
Lambertian::set_ka(const float k) {
	kd = k;
}



// -------------------------------------------------------------- set_kd

inline void
Lambertian::set_kd(const float k) {
	kd = k;
}


// -------------------------------------------------------------- set_cd

inline void
Lambertian::set_cd(const RGBColor& c) {
	cd = c;
}
