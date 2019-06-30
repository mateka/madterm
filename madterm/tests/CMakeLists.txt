enable_testing()

find_package(GTest REQUIRED)

include(GoogleTest)

add_executable(
    madterm_tests
    terminal_sequence.cpp
    text/text_effects.cpp
)
target_link_libraries(
    madterm_tests
    PUBLIC
        madterm
        GTest::GTest
        GTest::Main
)

gtest_discover_tests(madterm_tests)
