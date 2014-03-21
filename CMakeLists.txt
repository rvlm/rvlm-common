project(RvlmFdtdLibrary)
cmake_minimum_required(VERSION 2.8)

include_directories(rvlm-core)

install(TARGETS RvlmCore
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib/static)
