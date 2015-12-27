//
// Created by neverchanje on 12/26/15.
//

#ifndef PARSER_LAITEM_H
#define PARSER_LAITEM_H

#include <unordered_set>
#include "Item.h"

namespace parser {

typedef std::unordered_set<SymbolID> SymbolSet;

struct LAItem: public Item {
  SymbolSet lookahead;

  LAItem(RuleID id, size_t off, const SymbolSet &la) :
      Item(id, off),
      lookahead(la) {
  }
};

// The order of LAItem in an LAItemSet is nothing to do with lookahead.
typedef std::set<LAItem, ItemSetSort> LAItemSet;

} // namespace parser

#endif //PARSER_LAITEM_H
