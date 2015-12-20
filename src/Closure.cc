//
// Created by neverchanje on 12/7/15.
//

#include <algorithm>
#include <unordered_set>
#include "Closure.h"

using namespace parser;

Closure Closure::Make(std::vector<Item> &&I) {
  Closure clsr;
  std::unordered_set<SymbolID> symset;

  while (!I.empty()) {
    auto it = I.back();
    I.pop_back();
    clsr.items_.insert(it);

    SymbolID sid = RuleTable::GetRule(it.first).GetRHS(it.second);

    if (Symbol::IsNonTerminal(sid) && symset.find(sid) == symset.end()) {
      const auto &derives = RuleTable::GetDerives(sid);
      for (RuleID r : derives) {
        I.push_back(MakeItem(r, 0));
      }
      symset.insert(sid);
    }
  }

  return clsr;
}

#define RULE_RHS_SYMBOL_TAG(rule, i) (SymbolTable::GetSymbol((rule).GetRHS((i))).GetTag().c_str())
#define RULE_LHS_SYMBOL_TAG(rule)    (SymbolTable::GetSymbol((rule).GetLHS()).GetTag().c_str())

void Closure::Dump() {
  fprintf(stderr, "\n------- Beginning of dumping the Closure. -------\n");
  for (auto &it : items_) {
    const Rule &rule = RuleTable::GetRule(it.first);

    fprintf(stderr, "%s -> ", RULE_LHS_SYMBOL_TAG(rule));
    for (size_t i = 0; i < it.second; ++i) {
      fprintf(stderr, "%s ", RULE_RHS_SYMBOL_TAG(rule, i));
    }
    fprintf(stderr, "•%s", RULE_RHS_SYMBOL_TAG(rule, it.second));
    for (size_t i = it.second + 1; i < rule.GetRHSSize(); ++i) {
      fprintf(stderr, " %s", RULE_RHS_SYMBOL_TAG(rule, i));
    }
    fprintf(stderr, "\n");
  }
  fprintf(stderr, "------- Ending of dumping the Closure. -------\n");

}

#undef RULE_RHS_SYMBOL_TAG
#undef RULE_LHS_SYMBOL_TAG
