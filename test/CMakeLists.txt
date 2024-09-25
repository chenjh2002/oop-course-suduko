cmake_minimum_required(VERSION 3.10)

include(GoogleTest)
file(GLOB_RECURSE SUDUKO_TEST_SOURCES "${PROJECT_SOURCE_DIR}/test/*test.cpp")

# ##########################################
# "make check-test"
# ##########################################
add_custom_target(build-tests COMMAND ${CMAKE_CTEST_COMMAND} --show-only)
add_custom_target(check-tests COMMAND ${CMAKE_CTEST_COMMAND} --verbose)


# ##########################################
# "make XYZ_test"
# ##########################################
foreach (suduko_test_source ${SUDUKO_TEST_SOURCES})
    # Create a human readable name
    get_filename_component(suduko_test_filename ${suduko_test_source} NAME)
    string(REPLACE ".cpp" "" suduko_test_name ${suduko_test_filename})

    # Add the test target separately and as part of "make check-test"
    add_executable(${suduko_test_name}  EXCLUDE_FROM_ALL ${suduko_test_source})
    add_dependencies(build-tests ${suduko_test_name})
    add_dependencies(check-tests ${suduko_test_name})

    gtest_discover_tests(${suduko_test_name}
            EXTRA_ARGS
            --gtest_color=auto
            --gtest_output=xml:${CMAKE_BINARY_DIR}/test/${suduko_test_name}.xml
            --gtest_catch_exceptions=0
            DISCOVERY_TIMEOUT 120
            PROPERTIES
            TIMEOUT 120
    )

    target_link_libraries(${suduko_test_name} suduko_libs gtest gmock_main)

    # Set test target properties and dependencies.
    set_target_properties(${suduko_test_name}
            PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/test"
            COMMAND ${suduko_test_name}
    )
endforeach ()