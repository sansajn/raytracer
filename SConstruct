# dependencies: libwxgtk3.0-gtk3-dev libmagick++-dev libtbb-dev libboost-all-dev

ccflags = ['-Wall', '-O0', '-ggdb3']

cpp = Environment(
	CCFLAGS=ccflags,
	CXXFLAGS=['--std=c++20'],
	CPPPATH=['BRDFs', 'BTDFs', 'build', 'Cameras', 'GeometricObjects', 'Lights', 'Mappings', 
		'Materials', 'Noises', 'Samplers', 'Textures', 'Tracers', 'UserInterface', 
		'Utilities', 'World', '.'],
	CPPDEFINES=['BOOST_STACKTRACE_USE_BACKTRACE'],
	LIBS=['boost_stacktrace_backtrace', 'dl'],
	LINKFLAGS=['-rdynamic']
)

cpp.ParseConfig('wx-config --cflags --libs')
cpp.ParseConfig('pkg-config --cflags --libs Magick++ tbb')

import os
if 'TERM' in os.environ:
	cpp['ENV']['TERM'] = os.environ['TERM']


engine = cpp.Object([
	Glob('BRDFs/*.cpp'),
	Glob('BTDFs/*.cpp'),
	Glob('Cameras/*.cpp'),
	Glob('GeometricObjects/*.cpp'),
	Glob('Lights/*.cpp'),
	Glob('Mappings/*.cpp'),
	Glob('Materials/*.cpp'),
	Glob('Noise/*.cpp'),
	Glob('Samplers/*.cpp'),
	Glob('Textures/*.cpp'),
	Glob('Tracers/*.cpp'),
	Glob('Utilities/*.cpp'),
	Glob('Utilities/*.c'),
	Glob('World/*.cpp')
])

#shaded_objects = cpp.Object('build/BuildShadedObjects.cpp')


# chapter 3
ch3path = 'build/chapter03/'

ch3 = [
	cpp.Program('fig3_18', ['main.cpp', engine, ch3path + 'BuildFigure3_18.cpp']),
	cpp.Program('fig3_20a', ['main.cpp', engine, ch3path + 'BuildFigure3_20a.cpp']),
	cpp.Program('ch3_title', ['main.cpp', engine, ch3path + 'BuildCh3Title.cpp']),
]

cpp.Alias('ch3', ch3)


# chapter 4
ch4path = 'build/chapter04/'

ch4 = [
	cpp.Program('fig4_4a', ['main.cpp', engine, ch4path + 'BuildFigure4_4a.cpp']),
	cpp.Program('fig4_4b', ['main.cpp', engine, ch4path + 'BuildFigure4_4b.cpp']),
	cpp.Program('fig4_8a', ['main.cpp', engine, ch4path + 'BuildFigure4_8a.cpp']),
	cpp.Program('fig4_8b', ['main.cpp', engine, ch4path + 'BuildFigure4_8b.cpp']),
]

cpp.Alias('ch4', ch4)


# chapter 5
ch5path = 'build/chapter05/'

ch5 = [
	cpp.Program('fig5_13', ['main.cpp', engine, ch5path + 'BuildFigure5_13.cpp']),
]

cpp.Alias('ch5', ch5)


# chapter 6
ch6path = 'build/chapter06/'

ch6 = [
	cpp.Program('ch06_title', ['main.cpp', engine, ch6path + 'BuildCh06Title.cpp'])
]

cpp.Alias('ch6', ch6)


# chapter 8
ch8path = 'build/chapter08/'

ch8 = [
	cpp.Program('fig8_16a', ['main.cpp', engine, ch8path + 'BuildFigure8_16a.cpp']),
	cpp.Program('fig8_16b', ['main.cpp', engine, ch8path + 'BuildFigure8_16b.cpp']),
	cpp.Program('fig8_16c', ['main.cpp', engine, ch8path + 'BuildFigure8_16c.cpp']),
	cpp.Program('fig8_19a', ['main.cpp', engine, ch8path + 'BuildFigure8_19a.cpp']),
	cpp.Program('fig8_19b', ['main.cpp', engine, ch8path + 'BuildFigure8_19b.cpp']),
	cpp.Program('fig8_19c', ['main.cpp', engine, ch8path + 'BuildFigure8_19c.cpp']),
	cpp.Program('fig8_21a', ['main.cpp', engine, ch8path + 'BuildFigure8_21a.cpp']),
	cpp.Program('fig8_21b', ['main.cpp', engine, ch8path + 'BuildFigure8_21b.cpp']),
	cpp.Program('fig8_21c', ['main.cpp', engine, ch8path + 'BuildFigure8_21c.cpp']),
	cpp.Program('fig8_22a', ['main.cpp', engine, ch8path + 'BuildFigure8_22a.cpp']),
	cpp.Program('fig8_22b', ['main.cpp', engine, ch8path + 'BuildFigure8_22b.cpp']),
	cpp.Program('fig8_22c', ['main.cpp', engine, ch8path + 'BuildFigure8_22c.cpp']),
	cpp.Program('ch08_title', ['main.cpp', engine, ch8path + 'BuildCh08Title.cpp']),
]

cpp.Alias('ch8', ch8)


# chapter 9
ch9path = 'build/chapter09/'

ch9 = [
	cpp.Program('fig9_9a', ['main.cpp', engine, ch9path + 'BuildFigure9_9a.cpp']),
	cpp.Program('fig9_9b', ['main.cpp', engine, ch9path + 'BuildFigure9_9b.cpp']),
	cpp.Program('fig9_9c', ['main.cpp', engine, ch9path + 'BuildFigure9_9c.cpp']),
	cpp.Program('fig9_10a', ['main.cpp', engine, ch9path + 'BuildFigure9_10a.cpp']),
	cpp.Program('fig9_10b', ['main.cpp', engine, ch9path + 'BuildFigure9_10b.cpp']),
	cpp.Program('fig9_10c', ['main.cpp', engine, ch9path + 'BuildFigure9_10c.cpp']),
	cpp.Program('fig9_11a', ['main.cpp', engine, ch9path + 'BuildFigure9_11a.cpp']),
	cpp.Program('fig9_11b', ['main.cpp', engine, ch9path + 'BuildFigure9_11b.cpp']),
	cpp.Program('fig9_11c', ['main.cpp', engine, ch9path + 'BuildFigure9_11c.cpp']),
]

cpp.Alias('ch9', ch9)


# chapter 10
ch10path = 'build/chapter10/'

ch10 = [
	cpp.Program('fig10_9a', ['main.cpp', engine, ch10path + 'BuildFigure10_9a.cpp']),
	cpp.Program('fig10_9b', ['main.cpp', engine, ch10path + 'BuildFigure10_9b.cpp']),
	cpp.Program('fig10_10a', ['main.cpp', engine, ch10path + 'BuildFigure10_10a.cpp']),
	cpp.Program('fig10_10b', ['main.cpp', engine, ch10path + 'BuildFigure10_10b.cpp']),
	cpp.Program('fig10_10c', ['main.cpp', engine, ch10path + 'BuildFigure10_10c.cpp']),
	cpp.Program('fig10_11a', ['main.cpp', engine, ch10path + 'BuildFigure10_11a.cpp']),
	cpp.Program('fig10_11b', ['main.cpp', engine, ch10path + 'BuildFigure10_11b.cpp']),
	cpp.Program('fig10_12', ['main.cpp', engine, ch10path + 'BuildFigure10_12.cpp']),
	cpp.Program('fig10_13', ['main.cpp', engine, ch10path + 'BuildFigure10_13.cpp'])
]

cpp.Alias('ch10', ch10)


# chapter 11
ch11path = 'build/chapter11/'

ch11 = [
	cpp.Program('fig11_7a', ['main.cpp', engine, ch11path + 'BuildFigure11_7a.cpp']),
	cpp.Program('fig11_7b', ['main.cpp', engine, ch11path + 'BuildFigure11_7b.cpp']),
	cpp.Program('fig11_7c', ['main.cpp', engine, ch11path + 'BuildFigure11_7c.cpp']),
	cpp.Program('fig11_7d', ['main.cpp', engine, ch11path + 'BuildFigure11_7d.cpp']),
	cpp.Program('fig11_7e', ['main.cpp', engine, ch11path + 'BuildFigure11_7e.cpp']),
	cpp.Program('fig11_7f', ['main.cpp', engine, ch11path + 'BuildFigure11_7f.cpp']),
	cpp.Program('fig11_08a', ['main.cpp', engine, ch11path + 'BuildFigure11_08a.cpp']),
	cpp.Program('fig11_08b', ['main.cpp', engine, ch11path + 'BuildFigure11_08b.cpp']),
	cpp.Program('fig11_08c', ['main.cpp', engine, ch11path + 'BuildFigure11_08c.cpp']),
	cpp.Program('fig11_11a', ['main.cpp', engine, ch11path + 'BuildFigure11_11a.cpp']),
	cpp.Program('fig11_11b', ['main.cpp', engine, ch11path + 'BuildFigure11_11b.cpp']),
	cpp.Program('fig11_12a', ['main.cpp', engine, ch11path + 'BuildFigure11_12a.cpp']),
	cpp.Program('fig11_12b', ['main.cpp', engine, ch11path + 'BuildFigure11_12b.cpp']),
	cpp.Program('fig11_13', ['main.cpp', engine, ch11path + 'BuildFigure11_13.cpp'])
]

cpp.Alias('ch11', ch11)


# chapter 14
ch14path = 'build/chapter14/'

ch14 = [
	cpp.Program('fig14_05', ['main.cpp', engine, ch14path + 'BuildFigure14_05.cpp']),
	cpp.Program('fig14_07', ['main.cpp', engine, ch14path + 'BuildFigure14_07.cpp']),
	cpp.Program('fig14_10', ['main.cpp', engine, ch14path + 'BuildFigure14_10.cpp']),
	cpp.Program('fig14_11a', ['main.cpp', engine, ch14path + 'BuildFigure14_11a.cpp']),
	cpp.Program('fig14_11b', ['main.cpp', engine, ch14path + 'BuildFigure14_11b.cpp']),
	cpp.Program('fig14_11c', ['main.cpp', engine, ch14path + 'BuildFigure14_11c.cpp']),
	cpp.Program('fig14_15', ['main.cpp', engine, ch14path + 'BuildFigure14_15.cpp']),
	cpp.Program('fig14_21', ['main.cpp', engine, ch14path + 'BuildFigure14_21.cpp']),
	cpp.Program('fig14_22a', ['main.cpp', engine, ch14path + 'BuildFigure14_22a.cpp']),
	cpp.Program('fig14_22b', ['main.cpp', engine, ch14path + 'BuildFigure14_22b.cpp'])
]

cpp.Alias('ch14', ch14)


# chapter15
ch15path = 'build/chapter15/'

ch15 = [
	cpp.Program('fig15_07', ['main.cpp', engine, ch15path + 'BuildFigure15_07.cpp']),
	cpp.Program('fig15_08a', ['main.cpp', engine, ch15path + 'BuildFigure15_08a.cpp']),
	cpp.Program('fig15_08b', ['main.cpp', engine, ch15path + 'BuildFigure15_08b.cpp']),
	cpp.Program('fig15_title', ['main.cpp', engine, ch15path + 'BuildFigure15_title.cpp'])
]

cpp.Alias('ch15', ch15)


# chapter16
ch16path = 'build/chapter16/'

ch16 = [
	cpp.Program('fig16_01a', ['main.cpp', engine, ch16path + 'BuildFigure16_01a.cpp']),
	cpp.Program('fig16_01b', ['main.cpp', engine, ch16path + 'BuildFigure16_01b.cpp']),
	cpp.Program('fig16_05a', ['main.cpp', engine, ch16path + 'BuildFigure16_05a.cpp']),
	cpp.Program('fig16_05b', ['main.cpp', engine, ch16path + 'BuildFigure16_05b.cpp']),
	cpp.Program('fig16_09a', ['main.cpp', engine, ch16path + 'BuildFigure16_09a.cpp']),
	cpp.Program('fig16_10a', ['main.cpp', engine, ch16path + 'BuildFigure16_10a.cpp']),
	cpp.Program('fig16_10b', ['main.cpp', engine, ch16path + 'BuildFigure16_10b.cpp']),
	cpp.Program('fig16_11b', ['main.cpp', engine, ch16path + 'BuildFigure16_11b.cpp']),
	cpp.Program('fig16_title', ['main.cpp', engine, ch16path + 'BuildFigure16_title.cpp'])
]

cpp.Alias('ch16', ch16)


# chapter 17
ch17path = 'build/chapter17/'

ch17 = [
	cpp.Program('fig17_03a', ['main.cpp', engine, ch17path + 'BuildFigure17_03a.cpp']),
	cpp.Program('fig17_03b', ['main.cpp', engine, ch17path + 'BuildFigure17_03b.cpp']),
	cpp.Program('fig17_04a', ['main.cpp', engine, ch17path + 'BuildFigure17_04a.cpp']),
	cpp.Program('fig17_04b', ['main.cpp', engine, ch17path + 'BuildFigure17_04b.cpp']),
	cpp.Program('fig17_04c', ['main.cpp', engine, ch17path + 'BuildFigure17_04c.cpp']),
	cpp.Program('fig17_04d', ['main.cpp', engine, ch17path + 'BuildFigure17_04d.cpp']),
	cpp.Program('fig17_06a', ['main.cpp', engine, ch17path + 'BuildFigure17_06a.cpp']),
	cpp.Program('fig17_06b', ['main.cpp', engine, ch17path + 'BuildFigure17_06b.cpp']),
	cpp.Program('fig17_06c', ['main.cpp', engine, ch17path + 'BuildFigure17_06c.cpp']),
	cpp.Program('fig17_06d', ['main.cpp', engine, ch17path + 'BuildFigure17_06d.cpp']),
	cpp.Program('fig17_07a', ['main.cpp', engine, ch17path + 'BuildFigure17_07a.cpp']),
	cpp.Program('fig17_07b', ['main.cpp', engine, ch17path + 'BuildFigure17_07b.cpp']),
	cpp.Program('fig17_07c', ['main.cpp', engine, ch17path + 'BuildFigure17_07c.cpp']),
	cpp.Program('fig17_07d', ['main.cpp', engine, ch17path + 'BuildFigure17_07d.cpp']),
	cpp.Program('fig17_08a', ['main.cpp', engine, ch17path + 'BuildFigure17_08a.cpp']),
	cpp.Program('fig17_08b', ['main.cpp', engine, ch17path + 'BuildFigure17_08b.cpp']),
	cpp.Program('fig17_11a', ['main.cpp', engine, ch17path + 'BuildFigure17_11a.cpp']),
	cpp.Program('fig17_11b', ['main.cpp', engine, ch17path + 'BuildFigure17_11b.cpp']),
	cpp.Program('fig17_12a', ['main.cpp', engine, ch17path + 'BuildFigure17_12a.cpp']),
	cpp.Program('fig17_12b', ['main.cpp', engine, ch17path + 'BuildFigure17_12b.cpp']),
	cpp.Program('fig17_12c', ['main.cpp', engine, ch17path + 'BuildFigure17_12c.cpp']),
	cpp.Program('fig17_13a', ['main.cpp', engine, ch17path + 'BuildFigure17_13a.cpp']),
	cpp.Program('fig17_13b', ['main.cpp', engine, ch17path + 'BuildFigure17_13b.cpp']),
	cpp.Program('fig17_14', ['main.cpp', engine, ch17path + 'BuildFigure17_14.cpp'])
]

cpp.Alias('ch17', ch17)


# chapter 18
ch18path = 'build/chapter18/'

ch18 = [
	cpp.Program('fig18_04a', ['main.cpp', engine, ch18path + 'BuildFigure18_04a.cpp']),
	cpp.Program('fig18_04b', ['main.cpp', engine, ch18path + 'BuildFigure18_04b.cpp']),
	cpp.Program('fig18_04c', ['main.cpp', engine, ch18path + 'BuildFigure18_04c.cpp']),
	cpp.Program('fig18_05a', ['main.cpp', engine, ch18path + 'BuildFigure18_05a.cpp']),
	cpp.Program('fig18_05b', ['main.cpp', engine, ch18path + 'BuildFigure18_05b.cpp']),
	cpp.Program('fig18_06a', ['main.cpp', engine, ch18path + 'BuildFigure18_06a.cpp']),
	cpp.Program('fig18_06b', ['main.cpp', engine, ch18path + 'BuildFigure18_06b.cpp']),
	cpp.Program('fig18_07a', ['main.cpp', engine, ch18path + 'BuildFigure18_07a.cpp']),
	cpp.Program('fig18_07b', ['main.cpp', engine, ch18path + 'BuildFigure18_07b.cpp']),
	cpp.Program('fig18_07c', ['main.cpp', engine, ch18path + 'BuildFigure18_07c.cpp']),
	cpp.Program('fig18_08a', ['main.cpp', engine, ch18path + 'BuildFigure18_08a.cpp']),
	cpp.Program('fig18_08b', ['main.cpp', engine, ch18path + 'BuildFigure18_08b.cpp']),
	cpp.Program('fig18_09', ['main.cpp', engine, ch18path + 'BuildFigure18_09.cpp']),
	cpp.Program('fig18_10a', ['main.cpp', engine, ch18path + 'BuildFigure18_10a.cpp']),
	cpp.Program('fig18_10b', ['main.cpp', engine, ch18path + 'BuildFigure18_10b.cpp']),
	cpp.Program('fig18_10c', ['main.cpp', engine, ch18path + 'BuildFigure18_10c.cpp']),
	cpp.Program('fig18_10d', ['main.cpp', engine, ch18path + 'BuildFigure18_10d.cpp']),
	cpp.Program('fig18_11a', ['main.cpp', engine, ch18path + 'BuildFigure18_11a.cpp']),
	cpp.Program('fig18_11b', ['main.cpp', engine, ch18path + 'BuildFigure18_11b.cpp']),
	cpp.Program('fig18_11c', ['main.cpp', engine, ch18path + 'BuildFigure18_11c.cpp']),
	cpp.Program('fig18_title', ['main.cpp', engine, ch18path + 'BuildFigure18_title.cpp']),
]

cpp.Alias('ch18', ch18)


# chapter 19
ch19path = 'build/chapter19/'

ch19 = [
	cpp.Program('fig19_07', ['main.cpp', engine, ch19path + 'BuildFigure19_07.cpp']),
	cpp.Program('fig19_16a', ['main.cpp', engine, ch19path + 'BuildFigure19_16a.cpp']),
	cpp.Program('fig19_16b', ['main.cpp', engine, ch19path + 'BuildFigure19_16b.cpp']),
	cpp.Program('fig19_16c', ['main.cpp', engine, ch19path + 'BuildFigure19_16c.cpp']),
	cpp.Program('fig19_23a', ['main.cpp', engine, ch19path + 'BuildFigure19_23a.cpp']),
	cpp.Program('fig19_25b', ['main.cpp', engine, ch19path + 'BuildFigure19_25b.cpp']),
	cpp.Program('fig19_27a', ['main.cpp', engine, ch19path + 'BuildFigure19_27a.cpp']),
	cpp.Program('fig19_27b', ['main.cpp', engine, ch19path + 'BuildFigure19_27b.cpp']),
	cpp.Program('fig19_29a', ['main.cpp', engine, ch19path + 'BuildFigure19_29a.cpp']),
	#cpp.Program('fig19_29b', ['main.cpp', engine, ch19path + 'BuildFigure19_29b.cpp']),
]

cpp.Alias('ch19', ch19)

# chapter 20
ch20path = 'build/chapter20/'

ch20 = [
	cpp.Program('fig20_06a', ['main.cpp', engine, ch20path + 'BuildFigure20_06a.cpp']),
	cpp.Program('fig20_06b', ['main.cpp', engine, ch20path + 'BuildFigure20_06b.cpp']),
	cpp.Program('fig20_06c', ['main.cpp', engine, ch20path + 'BuildFigure20_06c.cpp']),
	cpp.Program('fig20_06d', ['main.cpp', engine, ch20path + 'BuildFigure20_06d.cpp']),
]

cpp.Alias('ch20', ch20)

# chapter 21
ch21path = 'build/chapter21/'

ch21 = [
	cpp.Program('fig21_04', ['main.cpp', engine, ch21path + 'BuildFigure21_04.cpp']),
	cpp.Program('fig21_05a', ['main.cpp', engine, ch21path + 'BuildFigure21_05a.cpp']),
	cpp.Program('fig21_05b', ['main.cpp', engine, ch21path + 'BuildFigure21_05b.cpp']),
	cpp.Program('fig21_06', ['main.cpp', engine, ch21path + 'BuildFigure21_06.cpp']),
	cpp.Program('fig21_07', ['main.cpp', engine, ch21path + 'BuildFigure21_07.cpp']),
	cpp.Program('fig21_09a', ['main.cpp', engine, ch21path + 'BuildFigure21_09a.cpp']),
	cpp.Program('fig21_12', ['main.cpp', engine, ch21path + 'BuildFigure21_12.cpp']),
	cpp.Program('fig21_13', ['main.cpp', engine, ch21path + 'BuildFigure21_13.cpp']),
	cpp.Program('fig21_15', ['main.cpp', engine, ch21path + 'BuildFigure21_15.cpp']),
]

cpp.Alias('ch21', ch21)


# chapter 22
ch22path = 'build/chapter22/'

ch22 = [
	cpp.Program('fig22_09a', ['main.cpp', engine, ch22path + 'BuildFigure22_09a.cpp']),
	cpp.Program('fig22_10a', ['main.cpp', engine, ch22path + 'BuildFigure22_10a.cpp']),
	cpp.Program('fig22_10b', ['main.cpp', engine, ch22path + 'BuildFigure22_10b.cpp']),
	cpp.Program('fig22_11a', ['main.cpp', engine, ch22path + 'BuildFigure22_11a.cpp']),
	cpp.Program('fig22_11b', ['main.cpp', engine, ch22path + 'BuildFigure22_11b.cpp']),
	cpp.Program('fig22_11c', ['main.cpp', engine, ch22path + 'BuildFigure22_11c.cpp']),
	cpp.Program('fig22_11d', ['main.cpp', engine, ch22path + 'BuildFigure22_11d.cpp']),
	cpp.Program('fig22_11e', ['main.cpp', engine, ch22path + 'BuildFigure22_11e.cpp']),
	cpp.Program('fig22_14', ['main.cpp', engine, ch22path + 'BuildFigure22_14.cpp']),
	cpp.Program('fig22_16', ['main.cpp', engine, ch22path + 'BuildFigure22_16.cpp']),
	cpp.Program('fig22_title', ['main.cpp', engine, ch22path + 'BuildFigure22_title.cpp']),
]

cpp.Alias('ch22', ch22)


# chapter 23
ch23path = 'build/chapter23/'

ch23 = [
	cpp.Program('fig23_01a', ['main.cpp', engine, ch23path + 'BuildFigure23_01a.cpp']),
	cpp.Program('fig23_01b', ['main.cpp', engine, ch23path + 'BuildFigure23_01b.cpp']),
	cpp.Program('fig23_01c', ['main.cpp', engine, ch23path + 'BuildFigure23_01c.cpp']),
	cpp.Program('fig23_01d', ['main.cpp', engine, ch23path + 'BuildFigure23_01d.cpp']),
	cpp.Program('fig23_03a', ['main.cpp', engine, ch23path + 'BuildFigure23_03a.cpp']),
	cpp.Program('fig23_03b', ['main.cpp', engine, ch23path + 'BuildFigure23_03b.cpp']),
	cpp.Program('fig23_03c', ['main.cpp', engine, ch23path + 'BuildFigure23_03c.cpp']),
	cpp.Program('fig23_03d', ['main.cpp', engine, ch23path + 'BuildFigure23_03d.cpp']),
	cpp.Program('fig23_07a', ['main.cpp', engine, ch23path + 'BuildFigure23_07a.cpp']),
	cpp.Program('fig23_07b', ['main.cpp', engine, ch23path + 'BuildFigure23_07b.cpp']),
	cpp.Program('fig23_09b', ['main.cpp', engine, ch23path + 'BuildFigure23_09b.cpp']),
	cpp.Program('fig23_12a', ['main.cpp', engine, ch23path + 'BuildFigure23_12a.cpp']),
	cpp.Program('fig23_13', ['main.cpp', engine, ch23path + 'BuildFigure23_13.cpp']),
]

cpp.Alias('ch23', ch23)


# chapter 24
ch24path = 'build/chapter24/'

ch24 = [
	cpp.Program('fig24_06a', ['main.cpp', engine, ch24path + 'BuildFigure24_06a.cpp']),
	cpp.Program('fig24_06b', ['main.cpp', engine, ch24path + 'BuildFigure24_06b.cpp']),
	cpp.Program('fig24_07a', ['main.cpp', engine, ch24path + 'BuildFigure24_07a.cpp']),
	cpp.Program('fig24_07b', ['main.cpp', engine, ch24path + 'BuildFigure24_07b.cpp']),
	cpp.Program('fig24_11', ['main.cpp', engine, ch24path + 'BuildFigure24_11.cpp']),
]

cpp.Alias('ch24', ch24)


# chapter 25
ch25path = 'build/chapter25/'

ch25 = [
	cpp.Program('fig25_07', ['main.cpp', engine, ch25path + 'BuildFigure25_07.cpp']),
	cpp.Program('fig25_09', ['main.cpp', engine, ch25path + 'BuildFigure25_09.cpp']),
]

cpp.Alias('ch25', ch25)


# chapter 26
ch26path = 'build/chapter26/'

ch26 = [
	cpp.Program('fig26_06a', ['main.cpp', engine, ch26path + 'BuildFigure26_06a.cpp']),
	cpp.Program('fig26_06b', ['main.cpp', engine, ch26path + 'BuildFigure26_06b.cpp']),
	cpp.Program('fig26_06c', ['main.cpp', engine, ch26path + 'BuildFigure26_06c.cpp']),
]

cpp.Alias('ch26', ch26)


# chapter 28
ch28path = 'build/chapter28/'

ch28 = [
	cpp.Program('fig28_05a', ['main.cpp', engine, ch28path + 'BuildFigure28_05a.cpp']),
	cpp.Program('fig28_05b', ['main.cpp', engine, ch28path + 'BuildFigure28_05b.cpp']),
]

cpp.Alias('ch28', ch28)


# chapter 29
ch29path = 'build/chapter29/'

ch29 = [
	cpp.Program('fig29_01', ['main.cpp', engine, ch29path + 'BuildFigure29_01.cpp']),
	cpp.Program('fig29_02', ['main.cpp', engine, ch29path + 'BuildFigure29_02.cpp']),
	cpp.Program('fig29_04', ['main.cpp', engine, ch29path + 'BuildFigure29_04.cpp']),
	cpp.Program('fig29_06', ['main.cpp', engine, ch29path + 'BuildFigure29_06.cpp']),
	cpp.Program('fig29_09a', ['main.cpp', engine, ch29path + 'BuildFigure29_09a.cpp']),
	cpp.Program('fig29_09b', ['main.cpp', engine, ch29path + 'BuildFigure29_09b.cpp']),
	cpp.Program('fig29_10b', ['main.cpp', engine, ch29path + 'BuildFigure29_10b.cpp']),
	cpp.Program('fig29_11b', ['main.cpp', engine, ch29path + 'BuildFigure29_11b.cpp']),
	cpp.Program('fig29_12b', ['main.cpp', engine, ch29path + 'BuildFigure29_12b.cpp']),
	cpp.Program('fig29_13', ['main.cpp', engine, ch29path + 'BuildFigure29_13.cpp']),
	cpp.Program('fig29_16', ['main.cpp', engine, ch29path + 'BuildFigure29_16.cpp']),
	cpp.Program('fig29_19a', ['main.cpp', engine, ch29path + 'BuildFigure29_19a.cpp']),
	cpp.Program('fig29_19b', ['main.cpp', engine, ch29path + 'BuildFigure29_19b.cpp']),
	cpp.Program('fig29_19c', ['main.cpp', engine, ch29path + 'BuildFigure29_19c.cpp']),
	cpp.Program('fig29_22a', ['main.cpp', engine, ch29path + 'BuildFigure29_22a.cpp']),
	cpp.Program('fig29_22b', ['main.cpp', engine, ch29path + 'BuildFigure29_22b.cpp']),
]

cpp.Alias('ch29', ch29)

# chapter 30
ch30path = 'build/chapter30/'

ch30 = [
	cpp.Program('fig30_01a', ['main.cpp', engine, ch30path + 'BuildFigure30_01a.cpp']),
	cpp.Program('fig30_01b', ['main.cpp', engine, ch30path + 'BuildFigure30_01b.cpp']),
	cpp.Program('fig30_01c', ['main.cpp', engine, ch30path + 'BuildFigure30_01c.cpp']),
	cpp.Program('fig30_02', ['main.cpp', engine, ch30path + 'BuildFigure30_02.cpp']),
	cpp.Program('fig30_04', ['main.cpp', engine, ch30path + 'BuildFigure30_04.cpp']),
	cpp.Program('fig30_06a', ['main.cpp', engine, ch30path + 'BuildFigure30_06a.cpp']),
	cpp.Program('fig30_06b', ['main.cpp', engine, ch30path + 'BuildFigure30_06b.cpp']),
	cpp.Program('fig30_06c', ['main.cpp', engine, ch30path + 'BuildFigure30_06c.cpp']),
	cpp.Program('fig30_06d', ['main.cpp', engine, ch30path + 'BuildFigure30_06d.cpp']),
	cpp.Program('fig30_07', ['main.cpp', engine, ch30path + 'BuildFigure30_07.cpp']),
	cpp.Program('fig30_08', ['main.cpp', engine, ch30path + 'BuildFigure30_08.cpp']),
	cpp.Program('fig30_11a', ['main.cpp', engine, ch30path + 'BuildFigure30_11a.cpp']),
	cpp.Program('fig30_11b', ['main.cpp', engine, ch30path + 'BuildFigure30_11b.cpp']),
	cpp.Program('fig30_11c', ['main.cpp', engine, ch30path + 'BuildFigure30_11c.cpp']),
	cpp.Program('fig30_11d', ['main.cpp', engine, ch30path + 'BuildFigure30_11d.cpp']),
	cpp.Program('fig30_12', ['main.cpp', engine, ch30path + 'BuildFigure30_12.cpp']),
	cpp.Program('fig30_13b', ['main.cpp', engine, ch30path + 'BuildFigure30_13b.cpp']),
]

cpp.Alias('ch30', ch30)


# chapter 31
ch31path = 'build/chapter31/'

ch31 = [
	cpp.Program('fig31_18', ['main.cpp', engine, ch31path + 'BuildFigure31_18.cpp']),
	cpp.Program('fig31_21a', ['main.cpp', engine, ch31path + 'BuildFigure31_21a.cpp']),
	cpp.Program('fig31_21b', ['main.cpp', engine, ch31path + 'BuildFigure31_21b.cpp']),
	cpp.Program('fig31_21c', ['main.cpp', engine, ch31path + 'BuildFigure31_21c.cpp']),
	cpp.Program('fig31_21d', ['main.cpp', engine, ch31path + 'BuildFigure31_21d.cpp']),
	cpp.Program('fig31_23a', ['main.cpp', engine, ch31path + 'BuildFigure31_23a.cpp']),
	cpp.Program('fig31_23b', ['main.cpp', engine, ch31path + 'BuildFigure31_23b.cpp']),
	cpp.Program('fig31_23c', ['main.cpp', engine, ch31path + 'BuildFigure31_23c.cpp']),
	cpp.Program('fig31_23d', ['main.cpp', engine, ch31path + 'BuildFigure31_23d.cpp']),
	cpp.Program('fig31_25a', ['main.cpp', engine, ch31path + 'BuildFigure31_25a.cpp']),
	cpp.Program('fig31_25b', ['main.cpp', engine, ch31path + 'BuildFigure31_25b.cpp']),
	cpp.Program('fig31_25c', ['main.cpp', engine, ch31path + 'BuildFigure31_25c.cpp']),
	cpp.Program('fig31_25d', ['main.cpp', engine, ch31path + 'BuildFigure31_25d.cpp']),
	cpp.Program('fig31_25e', ['main.cpp', engine, ch31path + 'BuildFigure31_25e.cpp']),
	cpp.Program('fig31_25f', ['main.cpp', engine, ch31path + 'BuildFigure31_25f.cpp']),
	cpp.Program('fig31_26a', ['main.cpp', engine, ch31path + 'BuildFigure31_26a.cpp']),
	cpp.Program('fig31_26b', ['main.cpp', engine, ch31path + 'BuildFigure31_26b.cpp']),
	cpp.Program('fig31_26c', ['main.cpp', engine, ch31path + 'BuildFigure31_26c.cpp']),
	cpp.Program('fig31_26d', ['main.cpp', engine, ch31path + 'BuildFigure31_26d.cpp']),
	cpp.Program('fig31_26e', ['main.cpp', engine, ch31path + 'BuildFigure31_26e.cpp']),
	cpp.Program('fig31_27a', ['main.cpp', engine, ch31path + 'BuildFigure31_27a.cpp']),
	cpp.Program('fig31_27b', ['main.cpp', engine, ch31path + 'BuildFigure31_27b.cpp']),
	cpp.Program('fig31_27c', ['main.cpp', engine, ch31path + 'BuildFigure31_27c.cpp']),
	cpp.Program('fig31_28a', ['main.cpp', engine, ch31path + 'BuildFigure31_28a.cpp']),
	cpp.Program('fig31_28b', ['main.cpp', engine, ch31path + 'BuildFigure31_28b.cpp']),
	cpp.Program('fig31_29a', ['main.cpp', engine, ch31path + 'BuildFigure31_29a.cpp']),
	cpp.Program('fig31_29b', ['main.cpp', engine, ch31path + 'BuildFigure31_29b.cpp']),
	cpp.Program('fig31_29c', ['main.cpp', engine, ch31path + 'BuildFigure31_29c.cpp']),
	cpp.Program('fig31_32a', ['main.cpp', engine, ch31path + 'BuildFigure31_32a.cpp']),
	cpp.Program('fig31_32b', ['main.cpp', engine, ch31path + 'BuildFigure31_32b.cpp']),
	cpp.Program('fig31_33a', ['main.cpp', engine, ch31path + 'BuildFigure31_33a.cpp']),
	cpp.Program('fig31_33b', ['main.cpp', engine, ch31path + 'BuildFigure31_33b.cpp']),
	cpp.Program('fig31_33c', ['main.cpp', engine, ch31path + 'BuildFigure31_33c.cpp']),
	cpp.Program('fig31_38', ['main.cpp', engine, ch31path + 'BuildFigure31_38.cpp']),
]

cpp.Alias('ch31', ch31)



# other samples
cpp.Program('instance', ['main.cpp', engine, 'build/instance.cpp'])
cpp.Program('open_part_cylinder', ['main.cpp', engine, 'build/open_part_cylinder.cpp'])
cpp.Program('smooth_triangle', ['main.cpp', engine, 'build/smooth_triangle.cpp'])
cpp.Program('pinhole_mt', ['main.cpp', engine, 'build/pinhole_mt.cpp'])

# tests
cpp.Program('test/test', [
	Glob('test/*.cpp'),
	engine])
