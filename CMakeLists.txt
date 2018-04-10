set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_library(lp_cc_lib INTERFACE)

target_include_directories(lp_cc_lib INTERFACE ${LIB_DIR}/include)
