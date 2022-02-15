// This file contains the definition the ViewPlane class

#include "ViewPlane.h"
#include "Samplers/Regular.h"
#include "Samplers/MultiJittered.h"

using std::unique_ptr, std::make_unique;
	
// ---------------------------------------------------------------- default constructor	
						
ViewPlane::ViewPlane(void)							
	: ViewPlane{400, 400, 1}
{}

ViewPlane::ViewPlane(int hres, int vres, int samples)
	: hres{hres}
	, vres{vres}
	, s{1.0}
	, num_samples{samples}
	, gamma{1.0}
	, show_out_of_gamut{false}
	, max_depth{0}
{}


// ---------------------------------------------------------------- copy constructor

ViewPlane::ViewPlane(const ViewPlane& vp)   
	:  	hres(vp.hres),  
		vres(vp.vres), 
		s(vp.s),
		num_samples(vp.num_samples),
		gamma(vp.gamma),
		inv_gamma(vp.inv_gamma),
		show_out_of_gamut(vp.show_out_of_gamut),
		sampler_ptr{vp.sampler_ptr->clone()},
		max_depth{vp.max_depth}
{}


// ---------------------------------------------------------------- assignment operator

ViewPlane& 
ViewPlane::operator= (const ViewPlane& rhs) {
	if (this == &rhs)
		return (*this);
		
	hres 				= rhs.hres;
	vres 				= rhs.vres;
	s					= rhs.s;
	num_samples			= rhs.num_samples;
	gamma				= rhs.gamma;
	inv_gamma			= rhs.inv_gamma;
	show_out_of_gamut	= rhs.show_out_of_gamut;
	sampler_ptr.reset(rhs.sampler_ptr->clone());
	max_depth = rhs.max_depth;
	
	return (*this);
}


// -------------------------------------------------------------- destructor

void ViewPlane::set_samples(const int n) {
	num_samples = n;

	if (num_samples > 1)
		sampler_ptr = make_unique<MultiJittered>(num_samples);
	else
		sampler_ptr = make_unique<Regular>(1);
}

void ViewPlane::set_sampler(unique_ptr<Sampler> sp) {
	sampler_ptr = move(sp);
	num_samples = sampler_ptr->get_num_samples();
}

void ViewPlane::set_max_depth(int depth) {
	max_depth = depth;
}
