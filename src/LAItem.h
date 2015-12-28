//
// Created by neverchanje on 12/26/15.
//

#ifndef PARSER_LAITEM_H
#define PARSER_LAITEM_H

#include "Item.h"

namespace parser {

// Item with lookaheads.
struct LAItem: public Item {
  SymbolID lookahead;

  LAItem() = default;

  LAItem(RuleID id, size_t off, SymbolID la) :
      Item(id, off),
      lookahead(la) {
  }
};

struct LAItemSetSort {
// Each item A -> a •X b in ItemSet I are sorted by X in ascending order,
// so that items can be grouped by different X.
  inline bool operator()(const LAItem &i1, const LAItem &i2) const {
    SymbolID x1 = i1.GetPointed();
    SymbolID x2 = i2.GetPointed();
    if (x1 == x2)
      return std::make_tuple(i1.rule_id, i1.offset, i1.lookahead)
          < std::make_tuple(i2.rule_id, i2.offset, i1.lookahead);
    return x1 < x2;
  }
};

typedef std::set<LAItem, LAItemSetSort> LAItemSet;

} // namespace parser

#endif //PARSER_LAITEM_H
