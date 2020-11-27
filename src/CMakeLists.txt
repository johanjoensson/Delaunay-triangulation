set(HEADER_LIST "${Delaunay-triangulation_SOURCE_DIR}/include/delaunay-triangulation.h")

add_executable(delaunay delaunay-lib.cpp ${HEADER_LIST})
target_compile_features(delaunay PUBLIC cxx_std_20)

target_include_directories(delaunay PUBLIC ../include/)

# IDEs should put the headers in a nice place
source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST})
