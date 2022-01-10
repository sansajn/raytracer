#pragma once
#include "Camera.h"

class Orthographic : public Camera {
public:
	void render_scene(World const & w) override;
	Camera * clone() const override;
};
