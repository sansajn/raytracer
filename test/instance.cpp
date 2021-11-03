#include <memory>
#include <catch.hpp>
#include "World/World.h"
#include "GeometricObjects/Box.h"
#include "GeometricObjects/Instance.h"
#include "Utilities/Ray.h"
#include "Tracers/RayCast.h"
#include "Materials/Matte.h"

using std::make_shared;

namespace {

class instance_world : public World {
	void build() {}
};

}  //namespace

TEST_CASE("geometric objects can be instanced", "[w][Instance]") {
	instance_world world;
	Ray r{Point3D{3,0,5}, Vector3D{0,0,-1}};
	auto material = make_shared<Matte>(0.2, 0.8, RGBColor{1,1,0});
	Point3D min_corner = {-0.5, -0.5, -0.5},
		max_corner = {0.5, 0.5, 0.5};

	SECTION("without an instance") {
		// SETUP
		Box * box = new Box{min_corner, max_corner};
		box->set_material(material);
		world.add_object(box);

		// ACT
		ShadeRec sr = world.hit_objects(r);

		// CHECK
		REQUIRE_FALSE(sr.hit_an_object);
	}

	SECTION("with an instance") {
		// SETUP
		auto box = make_shared<Box>(min_corner, max_corner);
		box->set_material(material);

		// instance box with translate transformation
		Instance * inst = new Instance{box};
		inst->translate(r.o);
		world.add_object(inst);

		// ACT
		ShadeRec sr = world.hit_objects(r);

		// CHECK
		REQUIRE(sr.hit_an_object);
	}
}

TEST_CASE("instanced object can be transformed with", "[x][w][Instance]") {
	// SETUP
	instance_world world;
	auto material = make_shared<Matte>(0.2, 0.8, RGBColor{1,1,0});

	Point3D min_corner = {-0.5, -1, -0.5},
		max_corner = {0.5, 1, 0.5};

	auto box = make_shared<Box>(min_corner, max_corner);
	box->set_material(material);

	Instance * inst = new Instance{box};
	world.add_object(inst);

	SECTION("translate transformation") {
		// SETUP
		Ray r{Point3D{.75,0,5}, Vector3D{0,0,-1}};

		// ACT
		inst->translate({.5, 0, 0});
		ShadeRec sr = world.hit_objects(r);

		// CHECK
		REQUIRE(sr.hit_an_object);
	}

	SECTION("rotate transformation") {
		// SETUP
		Ray r{Point3D{.75,0,5}, Vector3D{0,0,-1}};

		// check without transformation
		ShadeRec miss = world.hit_objects(r);
		REQUIRE_FALSE(miss.hit_an_object);

		// ACT
		inst->rotate_z(90.0);
		ShadeRec hit = world.hit_objects(r);

		// CHECK
		REQUIRE(hit.hit_an_object);
	}

	SECTION("tranlate and rotate transformations") {
		// SETUP
		Ray r{Point3D{-1.75, .25, 5}, Vector3D{0,0,-1}};

		// check without transformation
		ShadeRec miss = world.hit_objects(r);
		REQUIRE_FALSE(miss.hit_an_object);

		// ACT

		// translate > rotate
		inst->translate({0,1,0});
		inst->rotate_z(90.0);
		ShadeRec hit = world.hit_objects(r);

		// CHECK
		REQUIRE(hit.hit_an_object);
	}
}
