# dependencies: libwxgtk3.0-gtk3-dev

env = Environment(
	CPPPATH=['BRDFs', 'BTDFs', 'build', 'Cameras', 'GeometricObjects', 'Lights', 'Mappings', 
		'Materials', 'Noises', 'Samplers', 'Textures', 'Tracers', 'UserInterface', 
		'Utilities', 'World']
)

env.ParseConfig('wx-config --cflags --libs')

env.Program('raytracer', [
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
	Glob('UserInterface/*.cpp'),
	Glob('Utilities/*.cpp'),
	Glob('World/*.cpp'),
])
