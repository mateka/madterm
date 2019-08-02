project('madterm', 'cpp', version: '0.0.0.1', default_options: ['cpp_std=c++17'])

madterm_includes = include_directories('include')
madterm_lib = library(
    'madterm',
    'src/cursor/mode.cpp',
    'src/cursor/move.cpp',
    'src/enable_formatting.cpp',
    'src/screen_buffer/screen_buffer.cpp',
    'src/terminal_sequence.cpp',
    'src/text/effects.cpp',
    'src/text/modification.cpp',
    'src/text/charset.cpp',
    'src/window/window.cpp',
    include_directories: madterm_includes,
    install: true
)
madterm = declare_dependency(
    link_with : madterm_lib, include_directories : madterm_includes
)
install_subdir('include/madterm', install_dir: 'include')

subdir('tests')
subdir('examples')