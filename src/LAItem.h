//
// Created by neverchanje on 12/26/15.
//

#ifndef PARSER_LAITEM_H
#define PARSER_LAITEM_H

#include "Item.h"

namespace parser {

struct LAItem: public Item {
  SymbolID lookahead;

  LAItem(RuleID id, size_t off, SymbolID la) :
      rule_id(id),
      offset(off),
      lookahead(la) {
  }
};

} // namespace parser

#endif //PARSER_LAITEM_H
