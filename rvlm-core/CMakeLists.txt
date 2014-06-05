cmake_minimum_required(VERSION 2.8)

set(RVLM_CORE_UNIT_TESTING TRUE CACHE BOOL
    "Enable unit testing in library")

add_custom_target(RvlmCore SOURCES
    include/rvlm/core/NonAssignable.hh
    include/rvlm/core/SolidArray3d.hh
    include/rvlm/core/Flags.hh
    include/rvlm/core/Math.hh
    include/rvlm/core/Constants.hh)

install(
    DIRECTORY include
    DESTINATION .
    PATTERN *.hh)
if(RVLM_CORE_UNIT_TESTING)
find_package(Threads REQUIRED)
find_package(GTest REQUIRED)
add_executable(RvlmCoreTest
    tests/Flags.test.cc
target_include_directories(RvlmCoreTest
    PRIVATE include
    PRIVATE ${GTEST_INCLUDE_DIRS})
target_link_libraries(RvlmCoreTest
    ${CMAKE_THREAD_LIBS_INIT}
    ${GTEST_LIBRARIES}
    ${GTEST_MAIN_LIBRARIES})
endif()
