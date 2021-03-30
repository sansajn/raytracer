# dependencies: libwxgtk3.0-gtk3-dev libmagick++-dev

AddOption('--render-parallel', action='store_true', default=False, dest='render_parallel', help='parallel rendering')

env = Environment(
	CXXFLAGS=['-std=c++17'],
	CCFLAGS=['-Wall', '-O0', '-g'],
	CPPPATH=['BRDFs', 'BTDFs', 'build', 'Cameras', 'GeometricObjects', 'Lights', 'Mappings', 
		'Materials', 'Noises', 'Samplers', 'Textures', 'Tracers', 'UserInterface', 
		'Utilities', 'World'],
	CPPDEFINES=['USE_TERMINAL']
)

if GetOption('render_parallel'):
	env.Append(CPPDEFINES=['RENDER_PARALLEL'])

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
	'UserInterface/Terminal.cpp',
	Glob('Utilities/*.cpp'),
	Glob('World/*.cpp'),
])
