//
// Created by neverchanje on 12/29/15.
//

#include <boost/functional/hash.hpp>
#include "LAItem.h"

namespace parser {

std::string LAItem::ToString() const {
  return Item::ToString()
      + " , "
      + SymbolTable::GetSymbol(lookahead).GetTag();
}

std::size_t LAItem::HashValue() const {
  std::size_t seed = 0;
  boost::hash_combine(seed, rule_id);
  boost::hash_combine(seed, offset);
  boost::hash_combine(seed, lookahead);
  return seed;
}

} // namespace parser