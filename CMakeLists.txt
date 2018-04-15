cmake_minimum_required(VERSION 3.5.0 FATAL_ERROR)

set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_library(lp_cc_lib INTERFACE)
add_library(lp::cc_lib ALIAS lp_cc_lib)

target_include_directories(lp_cc_lib INTERFACE ${LIB_DIR}/include)

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()
