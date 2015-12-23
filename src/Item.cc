//
// Created by neverchanje on 12/23/15.
//

#include "Item.h"

namespace parser {

#define RULE_RHS_SYMBOL_TAG(rule, i) (SymbolTable::GetSymbol((rule).GetRHS((i))).GetTag().c_str())
#define RULE_LHS_SYMBOL_TAG(rule)    (SymbolTable::GetSymbol((rule).GetLHS()).GetTag().c_str())

void PrintItem(const Item &it) {
  const Rule &rule = RuleTable::GetRule(it.first);

  fprintf(stderr, "%s -> ", RULE_LHS_SYMBOL_TAG(rule));
  for (size_t i = 0; i < it.second; ++i) {
    fprintf(stderr, "%s ", RULE_RHS_SYMBOL_TAG(rule, i));
  }
  fprintf(stderr, "•%s", RULE_RHS_SYMBOL_TAG(rule, it.second));
  for (size_t i = it.second + 1; i < rule.GetRHSSize(); ++i) {
    fprintf(stderr, " %s", RULE_RHS_SYMBOL_TAG(rule, i));
  }
}

#undef RULE_RHS_SYMBOL_TAG
#undef RULE_LHS_SYMBOL_TAG

} // namespace parser