#ifndef __CONSTANTS__
#define __CONSTANTS__

#include <cmath>
#include <stdlib.h>
#include "RGBColor.h"

template <typename T>
constexpr T PI = T{M_PIl};

template <typename T>
constexpr T TWO_PI = T{2.0L*M_PIl};

template <typename T>
constexpr T PI_ON_180 = T{M_PIl/180.0L};

template <typename T>
constexpr T invPI = T{1.0L/M_PIl};

template <typename T>
constexpr T invTWO_PI = T{1.0L/(2.0L * M_PIl)};

const double 	kEpsilon 	= 0.0001; 
const double	kHugeValue	= 1.0E10;

RGBColor	const black(0.0);
RGBColor	const white(1.0);
RGBColor	const red(1.0, 0.0, 0.0);
RGBColor const yellow(1, 1, 0);
RGBColor const brown(0.71, 0.40, 0.16);
RGBColor const dark_green(0.0, 0.41, 0.41);
RGBColor const orange(1.0, 0.75, 0.0);
RGBColor const green(0.0, 0.6, 0.3);
RGBColor const light_green(0.65, 1.0, 0.30);
RGBColor const dark_yellow(0.61, 0.61, 0.0);
RGBColor const light_purple(0.65, 0.3, 1.0);
RGBColor const dark_purple(0.5, 0.0, 1.0);

const float 	invRAND_MAX = 1.0 / (float)RAND_MAX;

#endif
