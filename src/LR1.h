//
// Created by neverchanje on 12/21/15.
//

#ifndef PARSER_LR1_H
#define PARSER_LR1_H

#include "DFA.h"
#include "LR0.h"
#include "LAItem.h"

namespace parser {

namespace LR1 {

typedef LR0::State State;
typedef LR0::StateTable StateTable;

inline State MakeState(ItemSet &&iset, DFA::State &&state) {
  return std::make_pair(std::move(iset), state);
}

class Automaton: public LR0::Automaton {

 public:

  static Automaton Make(RuleID init) {
    Automaton atm;
    //return LR0::Automaton::Make(init);
  }

 private:

  Automaton() = default;

 protected:

  State startState(RuleID init) override;

  ItemSet closure(ItemSet::iterator first, ItemSet::iterator last) const override;

};

} // namespace LR1

} // namespace parser

#endif //PARSER_LR1_H
