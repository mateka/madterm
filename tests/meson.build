gtest_dep = dependency('gtest', main : true, fallback : ['gtest', 'gtest_dep'])

madterm_tests = executable(
    'tests',
    'cursor/move.cpp',
    'cursor/mode.cpp',
    'screen_buffer/screen_buffer.cpp',
    'text/charset.cpp',
    'text/effects.cpp',
    'text/modification.cpp',
    'window/window.cpp',
    'types.cpp',
    'terminal_sequence.cpp',
    dependencies: [gtest_dep, madterm]
)

test('tests', madterm_tests)