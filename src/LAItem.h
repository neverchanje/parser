//
// Created by neverchanje on 12/26/15.
//

#ifndef PARSER_LAITEM_H
#define PARSER_LAITEM_H

#include <assert.h>
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

  Item Next() const override {
    return LAItem(rule_id, offset + 1, lookahead);
  }

  bool CompareOthers(const Item &rhs) const override {
    return lookahead < boost::any_cast<SymbolID>(rhs.Others());
  }

  boost::any Others() const override {
    return lookahead;
  }

  std::string ToString() const override;

};

} // namespace parser

#endif //PARSER_LAITEM_H
