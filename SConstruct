import os, os.path

env = Environment()

env['CPPPATH'] = ['include']
env['LIBPATH'] = ['lib']
env['CC'] = 'clang'
env['CXX'] = 'clang++'
env['ENV']['TERM'] = os.environ['TERM']
env['CCFLAGS'] = '-g -W -Wall'
env['CXXFLAGS'] = '--std=c++11 --stdlib=libc++'

def subdirs(path):
    lst = []
    for root, dirs, files in os.walk(path):
        lst += [os.path.join(root, d) for d in dirs]
    lst.sort()
    return lst

srcdirs = subdirs('src')
srcdirs.append('src')

sources = []
for d in srcdirs:
    sources.append(Glob(os.path.join(d, '*.c')))
    sources.append(Glob(os.path.join(d, '*.cc')))

env.Library('lib/macho', sources)

for sample in Glob('samples/*.c') + Glob('samples/*.cc'):
    env.Program(sample, LIBS=['macho', 'c++'])

for sample in subdirs('samples'):
    sources = Glob(os.path.join(sample, '*.c')) \
              + Glob(os.path.join(sample, '*.cc'))
    env.Program(sources, LIBS=['macho', 'c++'])
