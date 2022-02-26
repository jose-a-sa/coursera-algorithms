# Specify the minimum CMAKE version required
CMAKE_MINIMUM_REQUIRED(VERSION 3.21.0)

PROJECT(divide-conquer)

# Set output directories
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib")
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib")
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/include" ${ROOT_INCLUDE_DIRS} ${OS_INCLUDE_DIRS})
LINK_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/lib" ${ROOT_LIB_DIRS} ${OS_LIB_DIRS})

ADD_EXECUTABLE(merge-sort src/merge_sort.c)
TARGET_LINK_LIBRARIES(merge-sort utils msort)

ADD_EXECUTABLE(karatsuba src/karatsuba.c)
TARGET_LINK_LIBRARIES(karatsuba utils m)

ADD_EXECUTABLE(merge-sort-inv src/merge_sort_inv.c)
TARGET_LINK_LIBRARIES(merge-sort-inv utils)
SET_PROPERTY(TARGET merge-sort-inv PROPERTY C_STANDARD 11)
SET_PROPERTY(TARGET merge-sort-inv PROPERTY CXX_STANDARD_REQUIRED ON)

ADD_EXECUTABLE(quick-sort-inv src/quick_sort_inv.c)
TARGET_LINK_LIBRARIES(quick-sort-inv utils)

ADD_EXECUTABLE(rand-select src/rand_select.c src/pivot_utils.c)
TARGET_LINK_LIBRARIES(rand-select utils)

ADD_EXECUTABLE(deter-select src/deter_select.c src/pivot_utils.c)
TARGET_LINK_LIBRARIES(deter-select msort utils)

ADD_EXECUTABLE(rand-min-cut src/rand_min_cut.c src/graph_utils.c)
TARGET_LINK_LIBRARIES(rand-min-cut utils)

