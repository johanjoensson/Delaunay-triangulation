cmake_minimum_required(VERSION 3.14)

project(
	Delaunay-triangulation
	VERSION 0.1
	DESCRIPTION "C++ library for Delaunay triangulation in, hopefully and/or at least, 2D and 3D"
	LANGUAGES CXX
)

# Only do these if this is the main project, and not if it is included through add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
	set(CMAKE_CXX_EXTENSIONS OFF)
	set_property(GLOBAL PROPERTY USE_FOLDERS ON)

	find_package(Doxygen)
	if(Doxygen_FOUND)
		add_subdirectory(doc)
	else()
		message(STATUS "Doxygen not found, not building docs")
	endif()

	set(WFLAGS -Werror -Wall -Wextra -pedantic -Wshadow -Wnon-virtual-dtor
		-Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -Wpedantic
		-Wconversion -Wsign-conversion -Wmisleading-indentation
		-Wnull-dereference -Wdouble-promotion -Wformat=2 -Weffc++)
	if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
		set(WFLAGS ${WFLAGS} -Wduplicated-cond -Wduplicated-branches
			-Wlogical-op -Wuseless-cast)
	endif()
endif() # Main project only part ends here

# IDEs should put the headers in a nice place
source_group(
	TREE "${PROJECT_SOURCE_DIR}/include"
	PREFIX "Header Files"
	FILES ${HEADER_LIST}
)

add_subdirectory(src)

if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR MODERN_CMAKE_BUILD_TESTING)
AND BUILD_TESTING)
	add_subdirectory(test)
endif()
