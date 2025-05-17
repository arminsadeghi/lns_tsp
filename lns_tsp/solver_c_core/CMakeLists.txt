cmake_minimum_required(VERSION 3.12)
project(solver)

find_package(Python3 COMPONENTS Development)

if (NOT Python3_FOUND)
    message(FATAL_ERROR "Python3 not found. Please install Python3 development files.")
endif()

if (NOT Python3_INCLUDE_DIRS)
    message(FATAL_ERROR "Python3 include directories not found. Please install Python3 development files.")
endif()

# Get all the source files in the src directory
file(GLOB_RECURSE SOURCE_FILES
    src/*.c
)
# Exclude some of the source files
list(FILTER SOURCE_FILES EXCLUDE REGEX "src/insertions/regret_insertion.c")
add_library(solver_core SHARED ${SOURCE_FILES})
target_include_directories(solver_core PRIVATE
    ${Python3_INCLUDE_DIRS} 
    include
)
target_link_libraries(solver_core PRIVATE
    ${Python3_LIBRARIES}
)
target_compile_options(solver_core PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -Werror
    -Wshadow
)
target_compile_definitions(solver_core PRIVATE
    -DVERSION_INFO="${PROJECT_VERSION}"
)
set_target_properties(solver_core PROPERTIES PREFIX "")
set_target_properties(solver_core PROPERTIES 
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
)