#ifndef __GRID__
#define __GRID__

// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This contains the declaration of the class Grid.
// The copy constructor, assignment operator, and destructor, are dummy functions.
// The reason is that a grid can contain an arbitrary number of objects, can therefore be of arbitrary size.


// There is no set_bounding_box function because the bounding box is constructed in the setup_cells
// function.

// This Grid class is also way too large. All the triangle and PLY file code should be placed in
// a separate class called TriangleMesh that inherits from Grid.

#include <vector>
#include "Compound.h"
#include "ShadeRec.h"
#include "Utilities/Mesh.h"
#include "Utilities/BBox.h"

//---------------------------------------------------------------------- class Grid

class Grid: public Compound {										  	
	public:
		Grid();
		Grid(Mesh* _mesh_ptr);    										
		Grid * clone() const override;
		Grid(Grid const & rg);

		Grid& 								
		operator= (const Grid& rhs);	

		virtual ~Grid();

		BBox get_bounding_box() override;

		void												
		read_flat_triangles(char const * file_name);

		void												
		read_smooth_triangles(char const * file_name);

		void												
		tessellate_flat_sphere(const int horizontal_steps, const int vertical_steps);

		void												
		tessellate_smooth_sphere(const int horizontal_steps, const int vertical_steps);

		bool hit(Ray const & ray, double& tmin, ShadeRec& sr) const override;
		bool shadow_hit(Ray const & ray, double & tmin) const override;

		void setup_cells();
		void reverse_mesh_normals();
		void store_material(std::shared_ptr<Material> material, const int index);

	private: 

		std::vector<GeometricObject*>	cells;			// grid of cells
		int							nx, ny, nz;    	// number of cells in the x, y, and z directions
		BBox						bbox;			// bounding box
		Mesh*						mesh_ptr;		// holds triangle data
		bool						reverse_normal;	// some PLY files have normals that point inwards

		Point3D
		find_min_bounds(void);

		Point3D
		find_max_bounds(void);

		void
		read_ply_file(char const * file_name, const int triangle_type);

		void
		compute_mesh_normals(void);	
};


// ------------------------------------------------------------------------------ store_material

inline void
Grid::reverse_mesh_normals(void) {   
	reverse_normal = true;
}


// ------------------------------------------------------------------------------ store_material
// stores the material in the specified object
// this is called from the Rosette and Archway classes, which inherit from Grid

inline void
Grid::store_material(std::shared_ptr<Material> material_ptr, const int index) {
	objects[index]->set_material(material_ptr); 
}

#endif








