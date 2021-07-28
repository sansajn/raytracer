# Ray Tracer

Ray tracer implementation from the [Ray Tracing from the Ground Up](http://www.raytracegroundup.com/index.html) book. The code was taken from [`wxraytracer_eclipse_v.1.1.2.zip`](http://www.raytracegroundup.com/downloads/wxraytracer_eclipse_v.1.1.2.zip) package.

## Build & run instructions

Under *Ubuntu 20.04 LTS*

- install dependencies with

```bash
sudo apt install scons g++ libwxgtk3.0-gtk3-dev
```

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

