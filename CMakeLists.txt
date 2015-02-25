cmake_minimum_required(VERSION 2.8.11)
project(RvlmFramework)

enable_testing()

add_subdirectory(catch)
add_subdirectory(rvlm-core)

add_custom_target(RvlmFrameworkMiscFiles SOURCES
    README.txt)
