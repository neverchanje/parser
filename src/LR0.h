//
// Created by neverchanje on 12/7/15.
//

#ifndef PARSER_LR0_H
#define PARSER_LR0_H

#include "DFA.h"
#include "Item.h"

namespace parser {

typedef int RuleID;

namespace LR0 {

struct ItemSetHasher {
  size_t operator()(const ItemSet &val) const;
};

typedef std::unordered_map<ItemSet, DFA::State, ItemSetHasher> StateTable;

// typedef std::pair<ItemSet, DFA::State> State;

class Automaton {

 public:

  // Construct a LR(0) parsing table by a given initial rule init.
  static Automaton Make(RuleID init);

  void Dump() const;

 private:

  Automaton() = default;

  DFA dfa_;

};

} // namespace LR0

} // namespace parser

#endif //PARSER_LR0_H