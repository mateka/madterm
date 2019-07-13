enable_testing()

find_package(GTest REQUIRED)

include(GoogleTest)

add_executable(
    madterm_tests
    types.cpp
    terminal_sequence.cpp
    text/effects.cpp
    text/modification.cpp
    text/charset.cpp
    cursor/move.cpp
    cursor/mode.cpp
    window/window.cpp
    screen_buffer/screen_buffer.cpp
)
target_link_libraries(
    madterm_tests
    PUBLIC
        madterm
        GTest::GTest
        GTest::Main
)

gtest_discover_tests(madterm_tests)
