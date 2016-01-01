
set(PARSER_SRC
        ${PARSER_SOURCE_DIR}/LR0.cc
        ${PARSER_SOURCE_DIR}/LR1.cc
        ${PARSER_SOURCE_DIR}/DFA.cc
        ${PARSER_SOURCE_DIR}/Symbol.cc
        ${PARSER_SOURCE_DIR}/Closure.cc
        ${PARSER_SOURCE_DIR}/Rule.cc
        ${PARSER_SOURCE_DIR}/Item.cc
        ${PARSER_SOURCE_DIR}/First.cc
        ${PARSER_SOURCE_DIR}/LAItem.cc
        ${PARSER_SOURCE_DIR}/LAClosure.cc
        )

add_executable(parser ${PARSER_SRC} main.cc)
target_link_libraries(parser ${Boost_LIBRARIES})