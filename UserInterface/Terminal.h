#pragma once
#include <vector>
#include <Magick++.h>
#include "World.h"

#ifdef RENDER_PARALLEL
class RenderThread
{
public:
	RenderThread(World & w, std::vector<RGBColor> & image)
		: _image{image}
	{
		w.paintArea = this;
	}

	RGBColor * begin() {return &_image[0];}
	void setPixel(int x, int y, int red, int green, int blue) {}

private:
	std::vector<RGBColor> & _image;
};
#else
class RenderThread
{
public:
	RenderThread(World & w, Magick::Image & im);
	void setPixel(int x, int y, int red, int green, int blue);

private:
	World & _w;
	Magick::Image & _im;
};
#endif
