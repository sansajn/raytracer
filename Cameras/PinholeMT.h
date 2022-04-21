#pragma once
#include "Pinhole.h"

//! Multithread pinhole camera implementation.
class PinholeMT : public Pinhole {
public:
	void render_scene(const World& w) override;
};
