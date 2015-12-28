//
// Created by neverchanje on 12/27/15.
//

#include <unordered_set>
#include "LAClosure.h"
#include "First.h"

namespace parser {

// For the given Item (A -> a •B b, la), calculate the lookahead symbol of
// Item A -> a B •b, which is FIRST(b la). If b -> $ is a production,
// then add la to FIRST(b la).
static SymbolSet calculateLA(SymbolID b, SymbolID la) {
  SymbolSet symset = First(b);
  // if b -> $ is a production
  if (symset.find(Symbol::EOR().GetID()) != symset.end()) {
    symset.insert(la);
  }
  return symset;
}

LAItemSet LAClosure(std::vector<LAItem> &&I) {
  LAItemSet clsr;
  SymbolID B, b;
  SymbolSet la_set;
  LAItem ni;

  while (!I.empty()) {
    auto it = I.back();
    I.pop_back();

    if (it.AtEnd()) {
      continue;
    }

    la_set.clear();
    B = it.GetPointed();

    if (it.IsTheLast()) {
      la_set.insert(it.lookahead);
    } else {
      b = RuleTable::GetRule(it.rule_id).GetRHS(it.offset + 1);
      la_set = calculateLA(b, it.lookahead);
    }

    if (Symbol::IsNonTerminal(B)) {
      const auto &derives = RuleTable::GetDerives(B);
      for (RuleID r : derives) {
        for (SymbolID la : la_set) {
          ni = LAItem(r, 0, la);
          if (clsr.find(ni) == clsr.end()) {
            I.push_back(LAItem(r, 0, la));
          }
        }
      }
    }
  }
  return clsr;
}

} // namespace parser
