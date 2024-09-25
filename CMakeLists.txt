cmake_minimum_required(VERSION 3.20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(SUDUKO
        VERSION 2024.1
        DESCRIPTION "soduku solution in cpp version"
        LANGUAGES C CXX
)

if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to `Debug` as none was specified.")
    set(CMAKE_BUILD_TYPE "Debug")
endif ()

if (EMSCRIPTEN)
    add_compile_definitions(-fexceptions)
    add_link_options(-fexceptions)
endif ()

# Compiler flags.
# Debug flags.
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -Werror")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wno-unused-parameter -Wno-attributes") # TODO: remove
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -ggdb -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls -fopenmp")

# People keep running CMake in the wrong folder, completely nuking their project or creating weird bugs.
# This checks if you're running CMake from a folder that already has CMakeLists.txt.
# Importantly, this catches the common case of running it from the root directory.
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" PATH_TO_CMAKELISTS_TXT)

if(EXISTS "${PATH_TO_CMAKELISTS_TXT}")
    message(FATAL_ERROR "Run CMake from a build subdirectory! \"mkdir build ; cd build ; cmake ..\" \
    Some junk files were created in this folder (CMakeCache.txt, CMakeFiles); you should delete those.")
endif()

# #############################################
# DEPENDENCIES
# #############################################

# CTest
enable_testing()

# Output directory.
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Includes.
set(SUDUKO_SRC_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/src/include)
set(SUDUKO_THIRD_PARTY_DIR
        ${PROJECT_SOURCE_DIR}/third-party/googletest/googletest/include
        ${PROJECT_SOURCE_DIR}/third-party/fmt/include
)

include_directories(${SUDUKO_SRC_INCLUDE_DIR} ${SUDUKO_THIRD_PARTY_DIR})
include_directories(BEFORE src)

set(SUDUKO_THIRD_PARTY_LIBS
        fmt
)

add_library(suduko_libs
        ${PROJECT_SOURCE_DIR}/src/suduko.cpp
        ${PROJECT_SOURCE_DIR}/src/grid.cpp
)

target_link_libraries(suduko_libs PUBLIC ${SUDUKO_THIRD_PARTY_LIBS})

add_executable(suduko_main ${PROJECT_SOURCE_DIR}/src/main.cpp)
target_link_libraries(suduko_main PUBLIC suduko_libs)

add_subdirectory(test)
add_subdirectory(third-party)