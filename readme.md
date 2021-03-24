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

command from the project directory and

- run with

```bash
./raytracer
```

command.
