// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include "Rosette.h"
#include "BeveledWedge.h"

Rosette* 
Rosette::clone(void) const {
	return(new Rosette(*this));
}

// ------------------------------------------------------------------------------ construct_rosette
// this function constructs the wedges in a rosette pattern and stores them in a grid
// this is the regular version, for Figure 21.11

/*
void
Rosette::construct_rosette(void) {	
	
	for (int k = 0; k < num_rings; k++) {
		for (int j = 0; j < num_wedges[k]; j++) {
			double angle_width = 360 / num_wedges[k];  // the azimuth angle extent of each wedge
			double r0 = hole_radius + k * ring_width;
			double r1 = hole_radius + (k + 1) * ring_width;
			double phi0 = j * angle_width;
			double phi1 = (j + 1) * angle_width;
			
			BeveledWedge* wedge_ptr = new BeveledWedge(y0, y1, r0, r1, rb, phi0 , phi1);
			add_object(wedge_ptr);										
		}
	}
}
*/


/*

// ------------------------------------------------------------------------------ construct_rosette
// use this version to render Figure 21.17
 
void
Rosette::construct_rosette(void) {

	for (int k = 0; k < num_rings; k++) {
		for (int j = 0; j < num_wedges[k]; j++) {
			double angle_width = 360 / num_wedges[k];  // the azimuth angle extent of each wedge
			double r0 = hole_radius + k * ring_width;
			double r1 = hole_radius + (k + 1) * ring_width;
			double angle_offset = 63 * k;
			double phi0 = j * angle_width + angle_offset;
			double phi1 = (j + 1) * angle_width + angle_offset;

			BeveledWedge* wedge_ptr = new BeveledWedge(y0, y1, r0, r1, rb, phi0 , phi1);
			add_object(wedge_ptr);
		}
	}
}

*/


Rosette::Rosette(int num_rings, const double hole_r, const double ring_w, const double rb, const double y0, const double y1)
			: Grid() {

	int max = 9;
	double min_azimuth, max_azimuth;
	double step;
	double min_r = hole_r,max_r;
	double flaw = 0;
	for(int i = 0; i < num_rings; ++i)
	{
		max += i + 1;
		step = 360.0 / max;
		min_r = hole_r+i*ring_w;
		max_r = min_r + ring_w;
		flaw = rb / (hole_r+(i+1)*ring_w) * 180 * invPI<double>;
		for(int j =0 ; j< max ; ++j)
		{
			min_azimuth = j*step;
			max_azimuth = (j+1)*step;
			BeveledWedge *bw = new BeveledWedge( y0, y1, min_r,max_r,rb,min_azimuth+flaw,max_azimuth-flaw);
			this->add_object(bw);
		}	
	}
}

// ----------------------------------------------------------------  default constructor
/*
Rosette::Rosette (void)
	: 	Grid()
{
}

void
Rosette::store_material(Material* material_ptr,int no)
{
	objects[no]->set_material(material_ptr);
}
*/
