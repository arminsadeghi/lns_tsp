cmake_minimum_required(VERSION 3.12)
project(solver)

find_package(Python3 COMPONENTS Development)

add_library(solver_core SHARED
    src/heuristic_util/insertion_util.c
    src/heuristic_util/removal_util.c
    src/removals/random_removal.c
    src/removals/worst_removal.c
    src/removals/cluster_removal.c
    src/util/tour_util.c
    src/insertions/cheapest_insertion.c
    src/insertions/nearest_insertion.c
    src/util/objective.c
    src/util/node_dlist.c
    src/twist_move.c
    src/wrapper.c
    src/tsp_instance.c
    src/data_loader/load_instance.c
    src/data_loader/distance_matrix.c
)
target_include_directories(solver_core PRIVATE
    ${Python3_INCLUDE_DIRS}
    include
)
target_link_libraries(solver_core PRIVATE
    ${Python3_LIBRARIES}
)

set_target_properties(solver_core PROPERTIES PREFIX "")
set_target_properties(solver_core PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
)
add_executable(solver_test
    tests/read_file_tests.c
)
target_link_libraries(solver_test PRIVATE
    solver_core
    m
    ${Python3_LIBRARIES}
)
target_include_directories(solver_test PRIVATE
    ${Python3_INCLUDE_DIRS}
    include
)