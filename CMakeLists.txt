cmake_minimum_required(VERSION 2.8)

option(RVLM_CORE_BUILD_TESTS "Build unit tests for rvlm-core library")

add_library(rvlm-common
    include/rvlm/core/memory/IAllocator.hh
    include/rvlm/core/memory/IAlignedAllocator.hh
    include/rvlm/core/memory/StlAllocator.hh
    include/rvlm/core/memory/OperatorNewAllocator.hh
    include/rvlm/core/ITraversable3d.hh
    include/rvlm/core/NonAssignable.hh
    include/rvlm/core/SolidArray3d.hh
    include/rvlm/core/Flags.hh
    include/rvlm/core/Math.hh
    include/rvlm/core/Constants.hh
    src/dummy.cc)
target_include_directories(rvlm-common PUBLIC include)
set_target_properties(rvlm-common PROPERTIES
    CXX_STANDARD_REQUIRED TRUE
    CXX_STANDARD          11)

if(RVLM_CORE_BUILD_TESTS)
    add_executable(rvlm-common-test
        test/Flags_test.cc
        test/main.cc)
    target_link_libraries(rvlm-common-test rvlm-common Thirdparty::Catch)
    set_target_properties(rvlm-common-test PROPERTIES
        CXX_STANDARD_REQUIRED TRUE
        CXX_STANDARD          11)
    add_test(rvlm-common-test rvlm-common-test)
endif()
