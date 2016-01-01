//
// Created by neverchanje on 12/26/15.
//

#ifndef PARSER_LAITEM_H
#define PARSER_LAITEM_H

#include <boost/make_unique.hpp>
#include <type_traits>
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

  static UPItem MakeUnique(RuleID r, size_t off, SymbolID la) {
    return UPItem(new LAItem(r, off, la));
  }

  UPItem Next() const override {
    return UPItem(new LAItem(rule_id, offset + 1, lookahead));
  }

  bool Compare(const Item &rhs) const override {
    typedef std::tuple<RuleID, size_t, SymbolID> LAItemTuple;
    return LAItemTuple(rule_id, offset, lookahead) <
        LAItemTuple(rhs.rule_id, rhs.offset, boost::any_cast<SymbolID>(rhs.Others()));
  }

  boost::any Others() const override {
    return lookahead;
  }

  std::string ToString() const override;

};

template<class T>
typename std::enable_if<std::is_same<T, LAItem>::value, LAItem>::type
DownCast(const UPItem &pItem) {
  LAItem ret(pItem->rule_id,
             pItem->offset,
             boost::any_cast<SymbolID>(pItem->Others()));
  return ret;
}

} // namespace parser

#endif //PARSER_LAITEM_H
