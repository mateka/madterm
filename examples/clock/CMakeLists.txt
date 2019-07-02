cmake_minimum_required (VERSION 3.10)

project(
    "clock"
    VERSION 0.0.0.1
    DESCRIPTION "clock"
     HOMEPAGE_URL "???"
    LANGUAGES CXX
)

# Project dependencies

# Project definition
add_executable(
    clock
    src/main.cpp
)
target_link_libraries(clock PRIVATE madterm::madterm)
target_compile_features(
    clock
    PUBLIC cxx_std_20
)
target_include_directories(
    clock
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# Install part
include(CMakePackageConfigHelpers)

add_executable(clock::clock ALIAS clock)

configure_package_config_file(
    "clockConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/clockConfig.cmake"
    INSTALL_DESTINATION lib/cmake/clock
)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/clockConfigVersion.cmake"
    VERSION ${clock_VERSION}
    COMPATIBILITY SameMajorVersion
)
install(
    TARGETS clock EXPORT clockTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)
install(
    EXPORT clockTargets
    FILE clockTargets.cmake
    NAMESPACE clock::
    DESTINATION lib/cmake/clock
)
install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/clockConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/clockConfigVersion.cmake"
    DESTINATION lib/cmake/clock
)
