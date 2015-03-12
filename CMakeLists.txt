cmake_minimum_required(VERSION 2.8)

option(RVLM_CORE_BUILD_TESTS "Build unit tests for rvlm-core library")

add_library(RvlmCore
    include/rvlm/object_ptr.hh
    include/rvlm/core/memory/IAllocator.hh
    include/rvlm/core/memory/IAlignedAllocator.hh
    include/rvlm/core/memory/StlAllocator.hh
    include/rvlm/core/memory/OperatorNewAllocator.hh
    include/rvlm/core/NonAssignable.hh
    include/rvlm/core/SolidArray3d.hh
    include/rvlm/core/Flags.hh
    include/rvlm/core/Math.hh
    include/rvlm/core/Constants.hh
    src/dummy.cc)
target_include_directories(RvlmCore PUBLIC include)
set_target_properties(RvlmCore PROPERTIES
    CXX_STANDARD_REQUIRED TRUE
    CXX_STANDARD          11)

if(RVLM_CORE_BUILD_TESTS)
    add_executable(RvlmCoreTest
        test/Flags_test.cc
        test/main.cc)
    target_include_directories(RvlmCoreTest PUBLIC ${RVLM_CATCH_INCLUDE_PATH})
    target_link_libraries(RvlmCoreTest RvlmCore)
    set_target_properties(RvlmCoreTest PROPERTIES
        CXX_STANDARD_REQUIRED TRUE
        CXX_STANDARD          11)
    add_test(RvlmCoreTest1 RvlmCoreTest)
endif()
