cmake_minimum_required(VERSION 2.8)
project( DetetecEdges )
find_package( OpenCV REQUIRED )

add_executable( detect_edges_sobel detect_edges_sobel.cpp )
add_executable( detect_edges_laplace detect_edges_laplace.cpp )
add_executable( detect_edges_canny detect_edges_canny.cpp )
add_executable( line_detector line_detector.cpp )
add_executable( circle_detector circle_detector.cpp )


target_link_libraries( detect_edges_sobel ${OpenCV_LIBS} )
target_link_libraries( detect_edges_laplace ${OpenCV_LIBS} )
target_link_libraries( detect_edges_canny ${OpenCV_LIBS} )
target_link_libraries( line_detector ${OpenCV_LIBS} )
target_link_libraries( circle_detector ${OpenCV_LIBS} )
