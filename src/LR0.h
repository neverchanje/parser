//
// Created by neverchanje on 12/7/15.
//

#ifndef PARSER_LR0_H
#define PARSER_LR0_H

#include "DFA.h"
#include "Item.h"

namespace parser {

typedef int RuleID;

struct ItemSetHasher {
  size_t operator()(const ItemSet &val) const;
};

namespace LR0 {

typedef std::pair<ItemSet, DFA::State> State;

typedef std::unordered_map<ItemSet, DFA::State, ItemSetHasher> StateTable;

inline State MakeState(ItemSet &&iset, DFA::State &&state) {
  return std::make_pair(std::move(iset), state);
}

class Automaton {

 public:

  // Construct a LR(0) parsing table by a given initial rule init.
  static Automaton Make(RuleID init);

  void Dump() const;

  // (DEBUG)
  const DFA &GetDFA() const { return dfa_; }

 private:

  Automaton() = default;

  DFA dfa_;

 protected:

  virtual State startState(RuleID init);

  virtual ItemSet closure(ItemSet::iterator first, ItemSet::iterator last) const;

};

} // namespace LR0

} // namespace parser

#endif //PARSER_LR0_H