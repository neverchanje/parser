//
// Created by neverchanje on 12/22/15.
//

#include "GoTo.h"
#include "Rule.h"

namespace parser {

ItemSet GoTo(const ItemSet &I, SymbolID X) {
  ItemSet ret;
  SymbolID sid;
  for (auto &it : I) {
    sid = RuleTable::GetRule(it.first).GetRHS(it.second);
    if (sid == X) {
      ret.insert(MakeItem(it.first, it.second + 1);
    }
  }
  return ret;
}

} // namespace parser
