cmake_minimum_required(VERSION 2.8)

project( 3d_eye_tracker )

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)
set(CMAKE_INSTALL_PREFIX "./install") 
set(CMAKE_CXX_STANDARD 14)

# Some libraries
find_package (OpenCV REQUIRED)
find_package (Boost 1.62 COMPONENTS filesystem system timer thread date_time chrono regex serialization REQUIRED )
find_package (Eigen 3.0.0 REQUIRED)
find_package (Ceres REQUIRED)

### Get spii
add_subdirectory (external/spii)
set (spii_ROOT_DIR "${CMAKE_BINARY_DIR}/external/spii")
set (spii_INCLUDE_DIRS ${spii_ROOT_DIR}/include)
find_library (spii_LIBRARY_RELEASE
              spii
              PATHS ${spii_ROOT_DIR}/lib/ ${spii_ROOT_DIR}/lib/Release)
find_library (meschach_LIBRARY_RELEASE
              meschach
              PATHS ${spii_ROOT_DIR}/lib/ ${spii_ROOT_DIR}/lib/Release)
if (spii_LIBRARY_RELEASE AND meschach_LIBRARY_RELEASE)
    set(spii_LIBRARIES ${spii_LIBRARY_RELEASE} ${meschach_LIBRARY_RELEASE})
else()
    set(spii_LIBRARIES "")
endif()
message(STATUS "spii_LIBRARIES:\"${spii_LIBRARIES}\"")


message(STATUS "")
message(STATUS "--- Include directories ---" )
message(STATUS " OpenCV_INCLUDE_DIRS: ${OpenCV_INCLUDE_DIRS}" )
message(STATUS " Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}" )
message(STATUS "---------------------------" )
message(STATUS "")

add_subdirectory (main)
add_subdirectory (singleeyefitter)
