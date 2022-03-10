#ifndef __SAMPLER__
#define __SAMPLER__


// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

//  Copyright notice for changes since the originally published version:
//  Copyright (C) Eduárd Mándy 2019-2021
//  Though this C++ code was change in a large measure it still has the original copyright notice.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.

#include <vector>
#include <math.h>

#include "../Utilities/Point2D.h"
#include "../Utilities/Point3D.h"
#include "../Utilities/Maths.h"

class Sampler {	
	public:	
		Sampler();
		Sampler(const int num);						
		Sampler(const int num, const int num_sets);		
		Sampler(const Sampler& s);						

		Sampler& operator= (const Sampler& rhs);

		virtual Sampler* clone() const = 0;

		virtual ~Sampler();
		
		void set_num_sets(const int np);
		
		virtual void generate_samples() = 0;  //!< generate sample patterns in a unit square [0,0]x[1,1]

		int get_num_samples();

		void shuffle_x_coordinates();
		void shuffle_y_coordinates();
		void setup_shuffled_indices();

		void map_samples_to_unit_disk();
		void map_samples_to_hemisphere(const float p);
		void map_samples_to_sphere();
		
		
		// the following functions are not const because they change count and jump
		
		Point2D sample_unit_square();  //!< get next sample on unit square
		Point2D sample_unit_disk();  //!< get next sample on unit disk
		Point3D sample_hemisphere();  //!< get next sample on unit hemisphere
		Point3D sample_sphere();  //!< get next sample on unit sphere
		
		/*! only used to set up a vector noise table
		this is not discussed in the book, but see the file LatticeNoise.cpp in Chapter 31 */
		Point2D sample_one_set();
		
	protected:
	
		int 					num_samples;     		// the number of sample points in a set
		int 					num_sets;				// the number of sample sets
		std::vector<Point2D>			samples;				// sample points on a unit square
		std::vector<int>				shuffled_indices;		// shuffled samples array indices
		std::vector<Point2D>			disk_samples;			// sample points on a unit disk
		std::vector<Point3D> 		hemisphere_samples;		// sample points on a unit hemisphere
		std::vector<Point3D> 		sphere_samples;			// sample points on a unit sphere
		unsigned long 			count;					// the current number of sample points used
		int 					jump;					// random index jump
};

#endif
