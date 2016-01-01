//
// Created by neverchanje on 12/21/15.
//

#include "LR1.h"
#include "LAItem.h"
#include "LAClosure.h"
#include <boost/functional/hash.hpp>
#include <queue>

namespace parser {

namespace LR1 {

State Automaton::startState(RuleID init) {
  ItemSet iset;
  iset.insert(LAItem::MakeUnique(init, 0, Symbol::EOR().GetID()));
  return MakeState(std::move(iset), DFA::State(DFA::START_STATE));
}

ItemSet Automaton::closure(ItemSet::iterator first, ItemSet::iterator last) const {
  std::vector<LAItem> vec;
  for (auto it = first; it != last; it++) {
    vec.push_back(DownCast<LAItem>(*it));
  }
  return Closure(std::move(vec));
}
} // namespace LR1

} // namespace parser