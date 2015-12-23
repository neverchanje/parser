//
// Created by neverchanje on 12/22/15.
//

#ifndef PARSER_ITEM_H
#define PARSER_ITEM_H

#include <set>
#include "Rule.h"

namespace parser {

typedef int RuleID;

typedef std::pair<RuleID, size_t> Item;

inline Item MakeItem(RuleID rule, size_t offset) {
  return std::make_pair<RuleID, size_t>(RuleID(rule), size_t(offset));
}

struct ItemSetSort {
// Each item A -> a •X b in ItemSet I are sorted by X in ascending order,
// so that items can be grouped by different X.
  inline bool operator()(const Item &i1, const Item &i2) const {
    SymbolID x1 = RuleTable::GetRule(i1.first).GetRHS(i1.second);
    SymbolID x2 = RuleTable::GetRule(i2.first).GetRHS(i2.second);
    if (x1 == x2)
      return i1 < i2;
    return x1 < x2;
  }
};

void PrintItem(const Item &item);

typedef std::set<Item, ItemSetSort> ItemSet;

} // namespace parser

#endif //PARSER_ITEM_H
