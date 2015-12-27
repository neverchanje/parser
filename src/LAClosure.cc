//
// Created by neverchanje on 12/27/15.
//

#include <unordered_set>
#include "LAClosure.h"
#include "First.h"

namespace parser {

// For the given Item (A -> a •B b, la), calculate the lookahead symbol of
// Item A -> a B •b, which is FIRST(b la). If b -> epsilon is a production,
// then add la to FIRST(b la).
static SymbolSet calculateLA(SymbolID b, const SymbolSet &la) {
  SymbolSet symset = First(b);
  // if b -> epsilon is a production
  if (symset.find(Symbol::Epsilon().GetID()) != symset.end()) {
    symset.insert(la.begin(), la.end());
  }
  return symset;
}

LAItemSet LAClosure(std::vector<LAItem> &&I) {
  LAItemSet clsr;
  SymbolID B, b;
  SymbolSet la;

  while (!I.empty()) {
    auto it = I.back();
    I.pop_back();
    clsr.insert(it);
    B = it.GetPointed();

    if (it.IsTheLast()) {
      la = it.lookahead;
    } else {
      b = RuleTable::GetRule(it.rule_id).GetRHS(it.offset + 1);
      la = calculateLA(b, it.lookahead);
    }

    if (Symbol::IsNonTerminal(B)) {
      const auto &derives = RuleTable::GetDerives(B);
      for (RuleID r : derives) {
        I.push_back(LAItem(r, 0, la));
      }
    }
  }
  return clsr;
}

} // namespace parser
