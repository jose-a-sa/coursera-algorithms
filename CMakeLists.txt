# Specify the minimum CMAKE version required
CMAKE_MINIMUM_REQUIRED(VERSION 3.0.0)

PROJECT(coursera-algorithms VERSION 0.0.2)

# Set output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../bin")


# OS specific variables
if(APPLE)
    SET(CMAKE_CXX_FLAGS "-Wimplicit-function-declaration")
    SET(OS_INCLUDE_DIRS "/usr/include" "/usr/local/include" "/opt/homebrew/include")
    SET(OS_LIB_DIRS "/usr/lib" "/usr/local/lib" "/opt/homebrew/lib")
elseif(UNIX)
    SET(CMAKE_CXX_FLAGS "-Wimplicit-function-declaration")
    SET(OS_INCLUDE_DIRS "/usr/include" "/usr/local/include")
    SET(OS_LIB_DIRS "/usr/lib" "/usr/local/lib")
elseif(WIN32)
    SET(CMAKE_CXX_FLAGS "-Wimplicit-function-declaration")
    SET(OS_INCLUDE_DIRS "c:/msys2/mingw64/include")
    SET(OS_INCLUDE_DIRS "c:/msys2/mingw64/lib")      
endif()

INCLUDE_DIRECTORIES("${CMAKE_BINARY_DIR}/../include" ${OS_INCLUDE_DIRS})
LINK_DIRECTORIES("${CMAKE_BINARY_DIR}/../lib" ${OS_LIB_DIRS})


ADD_LIBRARY(utils STATIC src/utils.c)
ADD_LIBRARY(matrix STATIC src/matrix_int.c)
ADD_LIBRARY(msort STATIC src/msort.c)

ADD_EXECUTABLE(merge-sort src/merge_sort.c)
TARGET_LINK_LIBRARIES(merge-sort utils)

ADD_EXECUTABLE(karatsuba src/karatsuba.c)
TARGET_LINK_LIBRARIES(karatsuba utils m)

ADD_EXECUTABLE(array-inv src/array_inv.c)
TARGET_LINK_LIBRARIES(array-inv utils)

ADD_EXECUTABLE(strassen-mul src/strassen_mul.c)
TARGET_LINK_LIBRARIES(strassen-mul utils matrix msort)