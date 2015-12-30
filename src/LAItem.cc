//
// Created by neverchanje on 12/29/15.
//

#include "LAItem.h"

namespace parser {

void LAItem::Print() const {
  Item::Print();
  printf(" , %s", SymbolTable::GetSymbol(lookahead).GetTag().c_str());
}

} // namespace parser