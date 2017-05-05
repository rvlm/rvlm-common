cmake_minimum_required(VERSION 2.8)

option(RVLM_CORE_BUILD_TESTS "Build unit tests for rvlm-core library")

add_library(rvlm-common
    include/rvlm/core/Constants.hh
    include/rvlm/core/Cuboid.hh
    include/rvlm/core/Flags.hh
    include/rvlm/core/Math.hh
    include/rvlm/core/NonAssignable.hh
    include/rvlm/core/SolidArray3d.hh
    include/rvlm/core/Traversable3D.hh
    include/rvlm/core/Vector3d.hh
    include/rvlm/core/memory/AlignedAllocator.hh
    include/rvlm/core/memory/Allocator.hh
    include/rvlm/core/memory/OperatorNewAllocator.hh
    include/rvlm/core/memory/StlAllocator.hh
    src/dummy.cc)

target_include_directories(rvlm-common
    PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

set_target_properties(rvlm-common PROPERTIES
    CXX_STANDARD_REQUIRED FALSE
    CXX_STANDARD          11)

if(RVLM_CORE_BUILD_TESTS)
    add_executable(rvlm-common-test
        #test/Flags_test.cc
        test/main.cc)
    target_include_directories(rvlm-common-test
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/submodules/Catch/include")
    target_link_libraries(rvlm-common-test rvlm-common)
    set_target_properties(rvlm-common-test PROPERTIES
        CXX_STANDARD_REQUIRED FALSE
        CXX_STANDARD          11)
    add_test(rvlm-common-test rvlm-common-test)
endif()
