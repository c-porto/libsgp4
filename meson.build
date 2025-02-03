project(
  'libsgp4',
  'c',
  version: '0.1.0',
  default_options: [
    'warning_level=3',
    'c_std=c99',
    'optimization=s',
    'buildtype=release',
    'default_library=both',
  ],
)

cc = meson.get_compiler('c')

sgp4_srcs = files(
  'src/sgp4.c',
  'src/tle.c',
)

sgp4_inc = include_directories('include', 'src')

sgp4_deps = []

libmath = cc.find_library('m')

if libmath.found()
  sgp4_deps += libmath
endif

c_args = [
  '-Wno-unused-parameter',
  '-Wno-unused-value',
  '-Wno-missing-field-initializers',
  '-Wno-narrowing',
  '-Wno-pointer-arith',
  '-Wshadow',
  '-Wcast-align',
  '-Wwrite-strings',
]

libsgp4 = library(
  'sgp4',
  sources: sgp4_srcs,
  include_directories: sgp4_inc,
  dependencies: sgp4_deps,
  c_args: c_args,
  install: false,
  version: meson.project_version(),
  soversion: meson.project_version().split('.')[0],
  pic: true,
)
