cmake_minimum_required(VERSION 3.28)
project(CMakeSFMLProject LANGUAGES CXX)

option(BUILD_TESTS "Build tests" ON)
option(ENABLE_WARNINGS_AS_ERRORS "Treat warnings as errors" OFF)
option(BUILD_SHARED_LIBS "Build shared libraries" ON)

# compile options for all targets depending on the compiler and the system
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    set(MY_COMPILE_OPTIONS "-Wall;-Wextra;-pedantic;-Wno-comment;-Wshadow;-Wnon-virtual-dtor;-Wpedantic;-Wconversion;-Wmisleading-indentation;-Wsign-conversion;-Wfloat-equal")
    if(ENABLE_WARNINGS_AS_ERRORS)
        list(APPEND MY_COMPILE_OPTIONS "-Werror")
    endif()
elseif(MSVC)
    set(MY_COMPILE_OPTIONS "/W4;/permissive-")
    if(ENABLE_WARNINGS_AS_ERRORS)
        list(APPEND MY_COMPILE_OPTIONS "/WX")
    endif()
endif()
if(APPLE)
    list(APPEND MY_COMPILE_OPTIONS "-Wno-deprecated-declarations")
endif()

# compile definitions for all targets depending on the compiler and the system
set(MY_COMPILE_DEFINITIONS "")
if(MSVC)
    set(MY_COMPILE_DEFINITIONS "-DNOMINMAX;-D_USE_MATH_DEFINES")
endif()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(AddSFML)

add_subdirectory(src)

add_executable(physics_engine main.cpp)
target_link_libraries(physics_engine PRIVATE application SFML::Graphics)
target_compile_options(physics_engine PRIVATE ${MY_COMPILE_OPTIONS})

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()
