//
// Created by neverchanje on 12/21/15.
//

#ifndef PARSER_LR1_H
#define PARSER_LR1_H

#include "DFA.h"

namespace parser {

namespace LR1 {

class Automaton {

 public:

  static Automaton Make();

  void Dump();

 private:

  Automaton() = default;

  DFA dfa;

};

} // namespace LR1

} // namespace parser

#endif //PARSER_LR1_H
