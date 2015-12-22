
set(PARSER_SRC
        LR0.cc
        DFA.cc
        Symbol.cc
#        Associativity.cc
        Closure.cc
        Rule.cc
#        Grammar.cc
        main.cc
        Item.h GoTo.h GoTo.cc)

add_executable(parser ${PARSER_SRC})
target_link_libraries(parser ${Boost_LIBRARIES})