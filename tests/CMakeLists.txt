project(parser_tests)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
add_subdirectory(lib/gtest-1.7.0)

add_executable(Symbol_unittest Symbol_unittest.cc ${PARSER_SOURCE_DIR}/Symbol.cc)
target_link_libraries(Symbol_unittest gtest gtest_main)

add_executable(Rule_unittest
        Rule_unittest.cc
        ${PARSER_SOURCE_DIR}/Rule.cc
        ${PARSER_SOURCE_DIR}/Symbol.cc
        )
target_link_libraries(Rule_unittest gtest gtest_main)