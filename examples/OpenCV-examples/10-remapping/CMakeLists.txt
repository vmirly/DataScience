cmake_minimum_required(VERSION 2.8)
project( RemapImg )
find_package( OpenCV REQUIRED )
add_executable( remap_img remap_img.cpp )
target_link_libraries( remap_img ${OpenCV_LIBS} )

add_executable( affine_transf affine_transf.cpp )
target_link_libraries( affine_transf ${OpenCV_LIBS} )

