//
// Created by neverchanje on 12/7/15.
//

#include "Closure.h"

using namespace parser;

static inline const Rule &
GetRuleByItem(const Item &item) {
  return RuleTable::GetRule(item.first);
}

static inline const Symbol &
GetSymbolInRuleRHS(const Rule &rule, ItemID item) {
  return SymbolTable::GetSymbol(rule.GetRHS()[item]);
}

Closure Closure::Make(const std::vector<Item> &I) {
  Closure clsr;
  clsr.items_ = I;

  for (int i = 0; i < I.size(); i++) {
    const Rule &rule = GetRuleByItem(I[i]);
    const Symbol &sym = GetSymbolInRuleRHS(rule, I[i].first);
  }

  return clsr;
}
