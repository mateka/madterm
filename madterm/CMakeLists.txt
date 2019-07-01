cmake_minimum_required (VERSION 3.10)

project(
    "madterm"
    VERSION 0.0.0.1
    DESCRIPTION "Library with iostream manipulators for formatting console output"
    HOMEPAGE_URL "???"
    LANGUAGES CXX
)

# Project dependencies

# Project definition
add_library(
    madterm
    include/madterm/enable_formatting.hpp
    include/madterm/types.hpp
    src/enable_formatting.cpp
    include/madterm/terminal_sequence.hpp
    src/terminal_sequence.cpp
    include/madterm/text/text_effects.hpp
    src/text/text_effects.cpp
    include/madterm/cursor/move.hpp
    src/cursor/move.cpp
    include/madterm/cursor/mode.hpp
    src/cursor/mode.cpp
    include/madterm/window/window.hpp
    src/window/window.cpp
    include/madterm/screen_buffer/screen_buffer.hpp
    src/screen_buffer/screen_buffer.cpp
)
target_compile_features(
    madterm
    PUBLIC cxx_std_20
)
target_include_directories(
    madterm
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# Install part
include(CMakePackageConfigHelpers)

add_library(madterm::madterm ALIAS madterm)

configure_package_config_file(
    "madtermConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/madtermConfig.cmake"
    INSTALL_DESTINATION lib/cmake/madterm
)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/madtermConfigVersion.cmake"
    VERSION ${madterm_VERSION}
    COMPATIBILITY SameMajorVersion
)
install(
    TARGETS madterm EXPORT madtermTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)
install(
    EXPORT madtermTargets
    FILE madtermTargets.cmake
    NAMESPACE madterm::
    DESTINATION lib/cmake/madterm
)
install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/madtermConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/madtermConfigVersion.cmake"
    DESTINATION lib/cmake/madterm
)

# Testing
add_subdirectory(tests)
