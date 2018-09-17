cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

PROJECT(tide)

INCLUDE_DIRECTORIES(include)

AUX_SOURCE_DIRECTORY(src DIR_SRCS)

set(tide ${DIR_SRCS})

INCLUDE_DIRECTORIES("/usr/include/eigen3/Eigen")

ADD_LIBRARY(dataio_lib SHARED ./src/dataio.cpp)

ADD_LIBRARY(para_lib SHARED ./src/parameterCal.cpp)

ADD_LIBRARY(linerSolve_lib SHARED ./src/linerSolver.cpp)

ADD_EXECUTABLE(${PROJECT_NAME} ${tide})

TARGET_LINK_LIBRARIES(${PROJECT_NAME} dataio_lib para_lib linerSolve_lib)
