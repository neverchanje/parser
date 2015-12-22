//
// Created by neverchanje on 12/7/15.
//

#include <vector>
#include <boost/make_unique.hpp>
#include "LR0.h"
#include "Closure.h"

namespace parser {

namespace LR0 {

Automaton Automaton::Make(RuleID init) {

#define ADD_ITEMSET(rule_id, rhs_id) itemSetTable.push_back(boost::make_unique(Closure({std::make_pair((rule_id), (rhs_id))})));

  Automaton atm;
  std::vector<std::unique_ptr<ItemSet> > itemSetTable;

  // DFA::START_STATE -> Item(init, 0)
  ADD_ITEMSET(init, 0);


  return atm;
}

void Automaton::Dump() {

}

} // namespace LR0

} // namespace parser