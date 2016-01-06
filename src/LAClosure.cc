//
// Created by neverchanje on 12/27/15.
//

#include <boost/make_unique.hpp>
#include "LAClosure.h"
#include "First.h"

namespace parser {

// For the given Item (A -> a •B b, la), calculate the lookahead symbol of
// Item A -> a B •b, which is FIRST(b la).
//
// if b -> $ is not a production
//  FIRST(b la) = FIRST(b)
// else
//  if la is not $
//    FIRST(b la) = FIRST(b) + la - $
//  else
//    FIRST(b la) = FIRST(b) + la
//
static SymbolSet calculateLA(SymbolID b, SymbolID la) {
  SymbolSet symset = First(b);
  SymbolID eor = Symbol::EOR().GetID();

  if (symset.find(eor) != symset.end()) {
    symset.insert(la);
    if (la != eor) {
      symset.erase(eor);
    }
  }
  return symset;
}

ItemSet Closure(std::vector<LAItem> &&I) {
  ItemSet clsr;
  SymbolID B, b;
  SymbolSet la_set;

  while (!I.empty()) {
    auto it = I.back();
    I.pop_back();

    clsr.insert(std::unique_ptr<LAItem>(new LAItem(it)));

    if (it.AtEnd()) {
      continue;
    }

    B = it.GetPointed();

    if (Symbol::IsNonTerminal(B)) {
      // b is the symbol next to B
      b = RuleTable::GetRule(it.rule_id).GetRHS(it.offset + 1);
      la_set = calculateLA(b, it.lookahead);
      const auto &derives = RuleTable::GetDerives(B);

      for (RuleID r : derives) {
        for (SymbolID la : la_set) {
          std::unique_ptr<Item> pni(new LAItem(r, 0, la));
          if (clsr.find(pni) == clsr.end()) {
            I.push_back(LAItem(r, 0, la));
          }
        }
      }
    }
  }
  return clsr;
}

} // namespace parser
