cmake_minimum_required(VERSION 2.8)

project( Tutorials )
cmake_minimum_required(VERSION 2.8)
project( houghcircle )
find_package( OpenCV REQUIRED )
add_executable( houghcircle houghcircle.cpp )
target_link_libraries( houghcircle  ${OpenCV_LIBS} )

