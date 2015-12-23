//
// Created by neverchanje on 12/7/15.
//

#include <algorithm>
#include <unordered_set>
#include "Closure.h"
#include "Rule.h"

namespace parser {

ItemSet Closure(std::vector<Item> &&I) {
  ItemSet clsr;
  std::unordered_set<SymbolID> symset; // use bitset ?

  while (!I.empty()) {
    auto it = I.back();
    I.pop_back();
    clsr.insert(it);
    RuleTable::GetRule(it.first).Dump();

    SymbolID sid = RuleTable::GetRule(it.first).GetRHS(it.second);

    // Expand the non-terminal sid and check it has not been expanded.
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


void DumpClosure(const ItemSet &clsr) {
  fprintf(stderr, "\n------- Beginning of dumping the Closure. -------\n");
  for (auto &it : clsr) {
    PrintItem(it);
    fprintf(stderr, "\n");
  }
  fprintf(stderr, "------- Ending of dumping the Closure. -------\n");
}
} // namespace parser
