# cmake for OpenCV 3 – Advanced topics in CVAP - Section01
# your opencv/build directory should be in your system PATH

# set minimum required version for cmake
cmake_minimum_required(VERSION 2.8)
set( PKG_CONFIG_PATH "/usr/lib/pkgconfig/" )

find_package(OpenCV REQUIRED PATHS /usr/local/opt/opencv@3 NO_DEFAULT_PATH) # manual specification of the OpenCVConfig.cmake path is necessary since otherwise, cmake assigns /opt/local a higher priority and ocv2.4 will be used

find_library(${OpenCV_LIBS})
#INCLUDE_DIRECTORIES(/usr/local/opt/opencv@2/include/opencv)
#INCLUDE_DIRECTORIES(/usr/local/opt/opencv@2/include/opencv2)

message(STATUS "OpenCV library status:")
message(STATUS "    config: ${OpenCV_DIR}")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")


# add executable
add_executable( video_processing video_processing.cpp)
add_executable( foreground foreground.cpp)

# link libraries
target_link_libraries( video_processing ${OpenCV_LIBS})
target_link_libraries( foreground ${OpenCV_LIBS})

# copy required images to every directory with executable
SET (IMAGES ${CMAKE_SOURCE_DIR}/images/bike.avi)
FILE(COPY ${IMAGES} DESTINATION .)
FILE(COPY ${IMAGES} DESTINATION "Debug")
FILE(COPY ${IMAGES} DESTINATION "Release")
