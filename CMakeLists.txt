cmake_minimum_required(VERSION 2.8.11)
project(RvlmFramework)

option(RVLM_UNIT_TESTING "Enable unit testing in rvlm-core library")

if(RVLM_UNIT_TESTING)
include(GTest.cmake)
enable_testing()
endif()

add_subdirectory(rvlm-core)
