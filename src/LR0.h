//
// Created by neverchanje on 12/7/15.
//

#ifndef PARSER_LR0_H
#define PARSER_LR0_H

#include "DFA.h"

namespace parser {

typedef int RuleID;

namespace LR0 {

class Automaton {

 public:

  // Construct a LR(0) parsing table by a given initial rule init.
  static Automaton Make(RuleID init);

  void Dump();

 private:

  Automaton() = default;

  DFA dfa_;

};

} // namespace LR0

} // namespace parser

#endif //PARSER_LR0_H
