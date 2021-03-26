# dependencies: libwxgtk3.0-gtk3-dev libmagick++-dev

env = Environment(
	CCFLAGS=['-Wall', '-O0', '-g'],
	CPPPATH=['BRDFs', 'BTDFs', 'build', 'Cameras', 'GeometricObjects', 'Lights', 'Mappings', 
		'Materials', 'Noises', 'Samplers', 'Textures', 'Tracers', 'UserInterface', 
		'Utilities', 'World'],
	CPPDEFINES=['USE_TERMINAL']
)

env.ParseConfig('wx-config --cflags --libs')
env.ParseConfig('pkg-config --cflags --libs Magick++')

env.Program('raytracer', ['main.cpp',
	Glob('BRDFs/*.cpp'),
	Glob('BTDFs/*.cpp'),
	Glob('build/*.cpp'),
	Glob('Cameras/*.cpp'),
	Glob('GeometricObjects/*.cpp'),
	Glob('Lights/*.cpp'),
	Glob('Mappings/*.cpp'),
	Glob('Materials/*.cpp'),
	Glob('Noises/*.cpp'),
	Glob('Samplers/*.cpp'),
	Glob('Textures/*.cpp'),
	Glob('Tracers/*.cpp'),
	#Glob('UserInterface/*.cpp'),
	'UserInterface/terminal.cpp',
	Glob('Utilities/*.cpp'),
	Glob('World/*.cpp'),
])
