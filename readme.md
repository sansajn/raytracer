# Ray Tracer

Ray tracer implementation from the [Ray Tracing from the Ground Up](http://www.raytracegroundup.com/index.html) book. The code was taken from [`wxraytracer_eclipse_v.1.1.2.zip`](http://www.raytracegroundup.com/downloads/wxraytracer_eclipse_v.1.1.2.zip) package. Ray tracer implementation is in *Bare-Bones* state as described in chapter 3 *Bare-Bones Ray Tracing*. 

Stanford models like bunny and dragon were downloaded from [The Stanford 3D Scanning Repository]http://graphics.stanford.edu/data/3Dscanrep/).

## Build & run instructions

Under *Ubuntu 20.04 LTS*

- install dependencies with

```bash
sudo apt install scons g++ pkg-conifg libwxgtk3.0-gtk3-dev libmagick++-dev libtbb-dev libboost-dev libboost-stacktrace-dev
```

> for whole boost library just install `libboost-all-dev` package

command, then

- build with

```bash
scons -j8
```

command from the project directory. This creates terminal based renderer rendering scene defined by `World::build()` member function implementation in `build/BuildShadedObjects.cpp` file. 

Terminal interface (`UserInterface/terminal.cpp`) was not part of raytracer source and together with `main.cpp` it was implemented as part of this repository.

- run with

```bash
./raytracer
```

command.

## Custom scenes

Read section *3.6.5 The Build Function* for detailed description, but in short rendered scene is defined by `World::build()` member function implementation (see `build/BuildShadedObjects.cpp`). To change renedered scene open build script `SConstruct` and edit line

```
scene = cpp.Object('build/BuildShadedObjects.cpp')
```

> TODO: describe building samples from the book ...

### Other implementations

[Hadryan Salles](https://github.com/hadryansalles/ray-tracing-from-the-ground-up)
[Jörn Dinkla](https://github.com/jdinkla/from-the-ground-up-ray-tracer)
[Dr. Brad Hollister](https://github.com/behollister/raytracingfromgroundup.git)
