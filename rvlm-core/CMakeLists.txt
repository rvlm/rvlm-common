cmake_minimum_required(VERSION 2.8.11)

option(RVLM_CORE_BUILD_TESTS "Build unit tests for rvlm-core library")

add_library(RvlmCore
    include/rvlm/core/memory/IAllocator.hh
    include/rvlm/core/memory/IAlignedAllocator.hh
    include/rvlm/core/memory/StlAllocator.hh
    include/rvlm/core/memory/StupidAlignedAllocator.hh
    include/rvlm/core/memory/OperatorNewAllocator.hh
    include/rvlm/core/NonAssignable.hh
    include/rvlm/core/SolidArray3d.hh
    include/rvlm/core/Flags.hh
    include/rvlm/core/Math.hh
    include/rvlm/core/Constants.hh
    dummy.cc)
target_include_directories(RvlmCore PUBLIC include)

if(RVLM_UNIT_TESTING AND RVLM_CORE_BUILD_TESTS)
add_executable(RvlmCoreTest
    tests/memory/OperatorNewAllocator.test.cc
    tests/memory/StlAllocator.test.cc
    tests/memory/StupidAlignedAllocator.test.cc)
    tests/Flags.test.cc)
target_link_libraries(RvlmCoreTest RvlmCore GTestMain)
add_test(RvlmCoreTest RvlmCoreTest)
endif()
