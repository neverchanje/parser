
set(PARSER_SRC
        LR0.cc
        Symbol.cc
        Associativity.cc
        Closure.cc
        State.cc
        Rule.cc
        Grammar.cc)

add_executable(parser ${PARSER_SRC})
target_link_libraries(parser ${Boost_LIBRARIES})