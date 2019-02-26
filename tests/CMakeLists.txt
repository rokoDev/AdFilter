cmake_minimum_required(VERSION ${cmake_version})

set(ProjectName ${AppName}_tests)
project(${ProjectName})

add_subdirectory(googletest)

macro(package_add_test TESTNAME)
    add_executable(${TESTNAME} ${ARGN})
    target_link_libraries(${TESTNAME} gtest gmock gtest_main)
    add_test(NAME ${TESTNAME} COMMAND ${TESTNAME})
    set_target_properties(${TESTNAME} PROPERTIES FOLDER tests)
endmacro()

package_add_test(${ProjectName} AdFilter_tests.cpp ${SOURCE_DIR}/AdFilter.cpp)
