#ifndef __PINHOLE__
#define __PINHOLE__

// This file contains the declaration of the class Pinhole

#include "Point2D.h"
#include "World.h"    // we can #include "World.h" here

//--------------------------------------------------------------------- class Pinhole

class Pinhole: public Camera {
	public:
	
		Pinhole();   							

		Pinhole(const Pinhole& ph);	
		
		virtual Camera*						
		clone(void) const;			

		Pinhole& 							
		operator= (const Pinhole& rhs);	
		
		virtual
		~Pinhole();   						
			
		void
		set_view_distance(const float vpd);
		
		void
		set_zoom(const float zoom_factor);
		
		Vector3D								
		get_direction(const Point2D& p) const;
		
		void render_scene(World const & w, float x = 0, int offset = 0) override;
		
	private:
			
		float	d;		// view plane distance
		float	zoom;	// zoom factor
		
};




//-------------------------------------------------------------------------- set_vpd

inline void
Pinhole::set_view_distance(float _d) {
	d = _d;
}	
	


//-------------------------------------------------------------------------- set_zoom

inline void
Pinhole::set_zoom(float zoom_factor) {
	zoom = zoom_factor;
}	

#endif
