cmake_minimum_required(VERSION 3.0.0)
set (CMAKE_CXX_STANDARD 11)
project(objectdetection VERSION 0.1.0)

# cmake for OpenCV 3 – Advanced topics in CVAP - Section01
# your opencv/build directory should be in your system PATH

# set minimum required version for cmake
cmake_minimum_required(VERSION 2.8)


####FOR MAC#####
set( PKG_CONFIG_PATH "/usr/lib/pkgconfig/" )
find_package(OpenCV REQUIRED PATHS /usr/local/opt/opencv@3 NO_DEFAULT_PATH) # manual specification of the OpenCVConfig.cmake path is necessary since otherwise, cmake assigns /opt/local a higher priority and ocv2.4 will be used
find_library(${OpenCV_LIBS})

message(STATUS "OpenCV library status:")
message(STATUS "    config: ${OpenCV_DIR}")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

###For ubuntu###
# find_package(OpenCV REQUIRED )
# find_library(${OpenCV_LIBS})
# include_directories(${CMAKE_SOURCE_DIR}/include )


# add executable
add_executable( detectObjects detectObjects.cpp )

# link libraries
target_link_libraries( detectObjects ${OpenCV_LIBS})

# copy required images to every directory with executable
# SET (IMAGES ${CMAKE_SOURCE_DIR}/images/bike.avi)
# FILE(COPY ${IMAGES} DESTINATION .)
# FILE(COPY ${IMAGES} DESTINATION "Debug")
# FILE(COPY ${IMAGES} DESTINATION "Release")

