#pragma once
#include "Camera.h"

class Orthographic : public Camera {
public:
	Camera * clone() const override;
	void render_scene(World const & w) override;
};
