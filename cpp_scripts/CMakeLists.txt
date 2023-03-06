cmake_minimum_required(VERSION 2.8...3.0)

project( tracker )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O3")
if(CMAKE_COMPILER_IS_GNUCXX)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wextra -pedantic -Wno-long-long")
endif()

find_package( OpenCV REQUIRED )
link_directories ( ${OpenCV_LIB_DIR} )
include_directories( ${OpenCV_INCLUDE_DIRS} )

set(COLOR_LIB_SRC colotracker.cpp histogram.cpp MeanShiftImp.cpp CamShiftImp.cpp )

add_library(color STATIC ${COLOR_LIB_SRC})
target_link_libraries(color ${OpenCV_LIBS})
set_target_properties(color PROPERTIES VERSION 1.0.0 SOVERSION 1)

add_executable( Main Main.cpp )
target_link_libraries( Main ${OpenCV_LIBS} color )