# dependencies: libwxgtk3.0-gtk3-dev libmagick++-dev

# TODO: implement --with-ui to build against wxwidget as interface

cpp = Environment(
	CCFLAGS=['--std=c++17', '-Wall', '-O0', '-g'],
	CPPPATH=['BRDFs', 'BTDFs', 'build', 'Cameras', 'GeometricObjects', 'Lights', 'Mappings', 
		'Materials', 'Noises', 'Samplers', 'Textures', 'Tracers', 'UserInterface', 
		'Utilities', 'World', '.'],
	CPPDEFINES=['USE_TERMINAL']
)

cpp.ParseConfig('wx-config --cflags --libs')
cpp.ParseConfig('pkg-config --cflags --libs Magick++')

# edit to change rendered scene
#scene = cpp.Object('build/BuildShadedObjects.cpp')
scene = cpp.Object('build/BuildFigure3_18.cpp')


interface = cpp.Object('UserInterface/terminal.cpp')

cpp.Program('raytracer', ['main.cpp',
	Glob('BRDFs/*.cpp'),
	Glob('BTDFs/*.cpp'),
	Glob('Cameras/*.cpp'),
	Glob('GeometricObjects/*.cpp'),
	Glob('Lights/*.cpp'),
	Glob('Mappings/*.cpp'),
	Glob('Materials/*.cpp'),
	Glob('Noises/*.cpp'),
	Glob('Samplers/*.cpp'),
	Glob('Textures/*.cpp'),
	Glob('Tracers/*.cpp'),
	Glob('Utilities/*.cpp'),
	Glob('World/*.cpp'),
	interface,
	scene
])
