//
// Created by neverchanje on 12/7/15.
//

#include <algorithm>
#include <unordered_set>
#include <boost/make_unique.hpp>
#include "Closure.h"

namespace parser {

ItemSet Closure(std::vector<Item> &&I) {
  ItemSet clsr;
  std::unordered_set<SymbolID> symset; // use bitset ?

  while (!I.empty()) {
    auto &it = I.back();
    I.pop_back();
    clsr.insert(boost::make_unique<Item>(Item(it.rule_id, it.offset)));

    if (it.AtEnd()) {
      continue;
    }

    SymbolID sid = it.GetPointed();

    // Expand the non-terminal sid and check it has not been expanded.
    if (Symbol::IsNonTerminal(sid) && symset.find(sid) == symset.end()) {
      const auto &derives = RuleTable::GetDerives(sid);
      for (RuleID r : derives) {
        I.push_back(Item(r, 0));
      }
      symset.insert(sid);
    }
  }

  return clsr;
}

void DumpClosure(const ItemSet &clsr) {
  fprintf(stderr, "\n------- Beginning of dumping the Closure. -------\n");
  for (auto &it : clsr) {
    it->Print();
    fprintf(stderr, "\n");
  }
  fprintf(stderr, "------- Ending of dumping the Closure. -------\n");
}

} // namespace parser
