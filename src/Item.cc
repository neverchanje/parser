//
// Created by neverchanje on 12/23/15.
//

#include "Item.h"

namespace parser {

#define RULE_RHS_SYMBOL_TAG(rule, i) (SymbolTable::GetSymbol((rule).GetRHS((i))).GetTag())
#define RULE_LHS_SYMBOL_TAG(rule)    (SymbolTable::GetSymbol((rule).GetLHS()).GetTag())

std::string Item::ToString() const {
  const Rule &rule = GetRule();
  std::string ret = RULE_LHS_SYMBOL_TAG(rule) + " -> ";

  for (size_t i = 0; i < offset; ++i) {
    ret += RULE_RHS_SYMBOL_TAG(rule, i) + " ";
  }
  ret += "•" + RULE_RHS_SYMBOL_TAG(rule, offset);
  for (size_t i = offset + 1; i < rule.GetRHSSize(); ++i) {
    ret += " " + RULE_RHS_SYMBOL_TAG(rule, i);
  }
  return ret;
}

#undef RULE_RHS_SYMBOL_TAG
#undef RULE_LHS_SYMBOL_TAG

} // namespace parser