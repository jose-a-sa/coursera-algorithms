# Specify the minimum CMAKE version required
CMAKE_MINIMUM_REQUIRED(VERSION 3.21.0)

PROJECT(coursera-algorithms VERSION 0.0.2)

# Set output directories
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../lib")
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../lib")
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../bin")

# OS specific variables
IF(APPLE)
    SET(OS_INCLUDE_DIRS "/usr/include" "/usr/local/include" "/opt/homebrew/include")
    SET(OS_LIB_DIRS "/usr/lib" "/usr/local/lib" "/opt/homebrew/lib")
ELSEIF(UNIX)
    SET(OS_INCLUDE_DIRS "/usr/include" "/usr/local/include")
    SET(OS_LIB_DIRS "/usr/lib" "/usr/local/lib")
ELSEIF(WIN32)
    SET(OS_INCLUDE_DIRS "c:/msys2/mingw64/include")
    SET(OS_INCLUDE_DIRS "c:/msys2/mingw64/lib")      
ENDIF()

INCLUDE_DIRECTORIES("${CMAKE_BINARY_DIR}/../include" ${OS_INCLUDE_DIRS})
LINK_DIRECTORIES("${CMAKE_BINARY_DIR}/../lib" ${OS_LIB_DIRS})

ADD_LIBRARY(utils STATIC src/utils.c)
ADD_LIBRARY(matrix STATIC src/matrix_int.c)
ADD_LIBRARY(msort STATIC src/msort.c)

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
SET_PROPERTY(TARGET quick-sort-inv PROPERTY C_STANDARD 11)
SET_PROPERTY(TARGET quick-sort-inv PROPERTY CXX_STANDARD_REQUIRED ON)

ADD_EXECUTABLE(strassen-mul src/strassen_mul.c)
TARGET_LINK_LIBRARIES(strassen-mul utils matrix msort)
