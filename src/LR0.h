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

// LR0::State
// A LR0::State represents a set of items, which are generated during the process of
// the LR0 algorithm, corresponding to the State in DFA.
typedef std::pair<ItemSet, DFA::State> State;

struct ItemSetHasher {
  size_t operator()(const ItemSet &val) const;
};

typedef std::unordered_map<ItemSet,
                           DFA::State,
                           ItemSetHasher,
                           ItemSetEqual> StateTable;

// Create an LR0::State.
inline State MakeState(ItemSet &&iset, DFA::State &&state) {
  return std::make_pair(std::move(iset), state);
}

class Automaton {

 public:

  // TODO: Function Make should be passed by a list of initial symbols.
  // Construct a LR(0) parsing table by a given initial rule init.
  static Automaton Make(RuleID init);

  // (DEBUG)
  void Dump() const;

  // (DEBUG)
  const DFA &GetDFA() const { return dfa_; }

 private:

  DFA dfa_;

 protected:

  Automaton() = default;

  virtual State startState(RuleID init);

  virtual ItemSet closure(ItemSet::iterator first,
                          ItemSet::iterator last) const;

  virtual void construct(RuleID init) final;

};

} // namespace LR0

} // namespace parser

#endif //PARSER_LR0_H