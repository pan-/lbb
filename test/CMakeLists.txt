enable_testing()

# gtest definition
include(ExternalProject)

ExternalProject_Add(
    gtest
    SVN_REPOSITORY http://googletest.googlecode.com/svn/tags/release-1.7.0
    TIMEOUT 10
    INSTALL_COMMAND ""
    LOG_DOWNLOAD ON
    LOG_CONFIGURE ON
    LOG_BUILD ON
    PREFIX "gtest"
)

# exports workaround
ExternalProject_Get_Property(gtest source_dir)
ExternalProject_Get_Property(gtest binary_dir)

# tests definition
set(TEST_TARGET test_${LIB_NAME})
file(GLOB_RECURSE TEST_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)


add_executable(${TEST_TARGET} ${TEST_FILES})
include_directories(
  ${source_dir}/include              # gtest includes 
  ${PROJECT_SOURCE_DIR}/include
)
add_dependencies(${TEST_TARGET} gtest)
target_link_libraries(
  ${TEST_TARGET}
  ${LIB_NAME}
#  gtest gtest_main
  ${binary_dir}/${CMAKE_STATIC_LIBRARY_PREFIX}gtest${CMAKE_STATIC_LIBRARY_SUFFIX}
  ${binary_dir}/${CMAKE_STATIC_LIBRARY_PREFIX}gtest_main${CMAKE_STATIC_LIBRARY_SUFFIX}
)

if(CMAKE_COMPILER_IS_GNUC OR CMAKE_COMPILER_IS_GNUCXX)
  target_link_libraries(${TEST_TARGET} pthread)
endif()

