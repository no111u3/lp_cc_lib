file(GLOB_RECURSE SOURCES "src/*.cc")

add_executable(lp_cc_lib_tests ${SOURCES})

target_link_libraries(lp_cc_lib_tests
    lp::cc_lib
)

target_compile_features(lp_cc_lib_tests PUBLIC cxx_std_14)
