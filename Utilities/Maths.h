#pragma once

// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This is a header file for the mathematics utility functions
// The prototypes of any inlined functions must be placed here

#include <stdlib.h>
#include <cmath>
#include "Constants.h"
#include "RGBColor.h"


// prototypes

double
min(double x0, double x1);

double
max(double x0, double x1);

double
clamp(const double x, const double min, const double max);

int
SolveQuadric(double c[3], double s[2]);

int 
SolveCubic(double c[4], double s[3]);

int 
SolveQuartic(double c[5], double s[4]);



// inlined functions

// ----------------------------------------------------------------- min

inline double
min(double x0, double x1) {
	return ((x0 < x1) ? x0 : x1);
}


// ----------------------------------------------------------------- max

inline double
max(double x0, double x1) {
	return ((x0 > x1) ? x0 : x1);
}

// ---------------------------------------------------- clamp

inline double
clamp(const double x, const double min, const double max) {
	return (x < min ? min : (x > max ? max : x));
}

//! Convert degrees to radians.
template <typename T>
T radians(T const & val) {
	return val * PI_ON_180<T>;
}

//! Convert radians to degrees.
template <typename T>
T degrees(T const & val) {
	return val * (180.0 * invPI<double>);
}


// The following functions are required for the noise classes and the Wood class.

// clamp, mod, mix_color, and smooth_step are RenderMan Shading Language functions
// They are discussed in Peachey in Ebert et al. (2003), where the RenderMan name for mix_color is mix.

// smooth_pulse and smooth_pulse_train are discussed in Apodaca and Gritz (2000).

double
mod(double a, const double b);

double
smooth_pulse(double e0, double e1, double e2, double e3, double x);

double
smooth_pulse_train(double e0, double e1, double e2, double e3, double period, double x);

double
smooth_step(double a, double b, double x);

RGBColor
mix_color(const RGBColor& c0, const RGBColor& c1, const double f);

double
mix_double(const double a, const double b, const double f);
