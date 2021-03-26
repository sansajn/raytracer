#pragma once
#include <Magick++.h>
#include "World.h"
#include <iostream>

class RenderThread
{
public:
	RenderThread(World & w, Magick::Image & im);
	void setPixel(int x, int y, int red, int green, int blue);

private:
	World & _w;
	Magick::Image & _im;
};
