# dependencies: libwxgtk3.0-gtk3-dev libmagick++-dev

# TODO: implement --with-ui to build against wxwidget as interface

cpp = Environment(
	CCFLAGS=['-Wall', '-Og', '-ggdb3'],
	CXXFLAGS=['--std=c++17'],
	CPPPATH=['BRDFs', 'BTDFs', 'build', 'Cameras', 'GeometricObjects', 'Lights', 'Mappings', 
		'Materials', 'Noises', 'Samplers', 'Textures', 'Tracers', 'UserInterface', 
		'Utilities', 'World', '.'],
	CPPDEFINES=['BOOST_STACKTRACE_USE_BACKTRACE'],
	LIBS=['boost_stacktrace_backtrace', 'dl'],
	LINKFLAGS=['-rdynamic']
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
	Glob('Utilities/*.c'),
	Glob('World/*.cpp')
])

#shaded_objects = cpp.Object('build/BuildShadedObjects.cpp')

fig3_18 = cpp.Object('build/BuildFigure3_18.cpp')
fig3_20a = cpp.Object('build/BuildFigure3_20a.cpp')
ch3_title = cpp.Object('build/BuildCh3Title.cpp')  # chapter 3 title image
fig4_4a = cpp.Object('build/BuildFigure4_4a.cpp')
fig4_4b = cpp.Object('build/BuildFigure4_4b.cpp')
fig4_8a = cpp.Object('build/BuildFigure4_8a.cpp')
fig4_8b = cpp.Object('build/BuildFigure4_8b.cpp')
fig5_13 = cpp.Object('build/BuildFigure5_13.cpp')
ch6_title = cpp.Object('build/BuildCh06Title.cpp')  # chapter 6 title image
fig8_16a = cpp.Object('build/BuildFigure8_16a.cpp')
fig8_16b = cpp.Object('build/BuildFigure8_16b.cpp')
fig8_16c = cpp.Object('build/BuildFigure8_16c.cpp')
fig8_19a = cpp.Object('build/BuildFigure8_19a.cpp')
fig8_19b = cpp.Object('build/BuildFigure8_19b.cpp')
fig8_19c = cpp.Object('build/BuildFigure8_19c.cpp')


cpp.Program('fig3_18', ['main.cpp', engine, fig3_18])
cpp.Program('fig3_20a', ['main.cpp', engine, fig3_20a])
cpp.Program('ch3_title', ['main.cpp', engine, ch3_title])
cpp.Program('fig4_4a', ['main.cpp', engine, fig4_4a])
cpp.Program('fig4_4b', ['main.cpp', engine, fig4_4b])
cpp.Program('fig4_8a', ['main.cpp', engine, fig4_8a])
cpp.Program('fig4_8b', ['main.cpp', engine, fig4_8b])
cpp.Program('fig5_13', ['main.cpp', engine, fig5_13])
cpp.Program('ch06_title', ['main.cpp', engine, ch6_title])
cpp.Program('fig8_16a', ['main.cpp', engine, fig8_16a])
cpp.Program('fig8_16b', ['main.cpp', engine, fig8_16b])
cpp.Program('fig8_16c', ['main.cpp', engine, fig8_16c])
cpp.Program('fig8_19a', ['main.cpp', engine, fig8_19a])
cpp.Program('fig8_19b', ['main.cpp', engine, fig8_19b])
cpp.Program('fig8_19c', ['main.cpp', engine, fig8_19c])
