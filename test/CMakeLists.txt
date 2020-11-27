set(TEST_FILES
)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(delaunay-test ${TEST_FILES})
target_link_libraries(delaunay-test ${GTEST_LIBRARIES} pthread numerical-mesh-lib)
GTEST_ADD_TESTS(delaunay-test "" ${TEST_FILES})
message(STATUS "CXX flags : ${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG}")
