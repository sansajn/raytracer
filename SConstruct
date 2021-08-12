# dependencies: libwxgtk3.0-gtk3-dev libmagick++-dev

# TODO: implement --with-ui to build against wxwidget as interface

cpp = Environment(
	CCFLAGS=['--std=c++17', '-Wall', '-O0', '-g'],
	CPPPATH=['BRDFs', 'BTDFs', 'build', 'Cameras', 'GeometricObjects', 'Lights', 'Mappings', 
		'Materials', 'Noises', 'Samplers', 'Textures', 'Tracers', 'UserInterface', 
		'Utilities', 'World', '.']
)

cpp.ParseConfig('wx-config --cflags --libs')
cpp.ParseConfig('pkg-config --cflags --libs Magick++')

engine = cpp.Object([
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
	Glob('World/*.cpp')
])

#shaded_objects = cpp.Object('build/BuildShadedObjects.cpp')

fig3_18 = cpp.Object('build/BuildFigure3_18.cpp')
fig3_20a = cpp.Object('build/BuildFigure3_20a.cpp')

cpp.Program('fig3_18', ['main.cpp', engine, fig3_18])
cpp.Program('fig3_20a', ['main.cpp', engine, fig3_20a])
