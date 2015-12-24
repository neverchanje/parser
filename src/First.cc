//
// Created by neverchanje on 12/24/15.
//

#include "First.h"
#include "Rule.h"

namespace parser {

SymbolSet First(SymbolID Xid) {
  SymbolSet symset;

  const Symbol &X = SymbolTable::GetSymbol(Xid);
  if (Symbol::IsTerminal(Xid)) {
    if ()

  } else {

  }

  return symset;
}

} // namespace parser
