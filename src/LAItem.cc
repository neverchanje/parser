//
// Created by neverchanje on 12/29/15.
//

#include "LAItem.h"

namespace parser {

std::string LAItem::ToString() const {
  return Item::ToString()
      + " , "
      + SymbolTable::GetSymbol(lookahead).GetTag();
}

} // namespace parser