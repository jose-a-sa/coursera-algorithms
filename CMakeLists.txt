CMAKE_MINIMUM_REQUIRED(VERSION 3.21.0)
PROJECT(coursera-algoritms)


# Set output directories
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib")
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib")
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

SET(ROOT_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include")
SET(ROOT_LIB_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/lib")


# OS specific variables
IF(APPLE)
    SET(OS_INCLUDE_DIRS "/usr/include" "/usr/local/include" "/opt/homebrew/include")
    SET(OS_LIB_DIRS "/usr/lib" "/usr/local/lib" "/opt/homebrew/lib")
ELSEIF(UNIX)
    SET(OS_INCLUDE_DIRS "/usr/include" "/usr/local/include")
    SET(OS_LIB_DIRS "/usr/lib" "/usr/local/lib")
ELSEIF(WIN32)
    SET(OS_INCLUDE_DIRS "c:/msys2/mingw64/include")
    SET(OS_LIB_DIRS "c:/msys2/mingw64/lib")      
ENDIF()


INCLUDE_DIRECTORIES(${ROOT_INCLUDE_DIRS} ${OS_INCLUDE_DIRS})
LINK_DIRECTORIES(${ROOT_LIB_DIRS} ${OS_LIB_DIRS})


ADD_LIBRARY(utils STATIC src/utils.c)
ADD_LIBRARY(matrix STATIC src/matrix_int.c)
ADD_LIBRARY(msort STATIC src/msort.c)


ADD_SUBDIRECTORY(divide-conquer)
ADD_SUBDIRECTORY(graph-search-data-structures)

