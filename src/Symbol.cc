//
// Created by neverchanje on 12/7/15.
//

#include <assert.h>
#include "Symbol.h"

using namespace parser;

namespace SymbolTable {

static std::unordered_map<std::string, Symbol> globSymbolTable;

} // namespace SymbolTable

bool Symbol::IsTerminal(SymbolID id) {
  return id < NTerminals;
}

bool Symbol::IsNonterminal(SymbolID id) {
  assert(id >= NTerminals + NNonTerminals);
  return id >= NNonTerminals;
}

Symbol Symbol::MakeSymbol(const std::string &tag,
                          Symbol::SymbolType type) {
  Symbol sym(tag, type);
  SymbolTable::AddSymbol(sym);
  return sym;
}

Symbol::Symbol(const std::string &tag,
               Symbol::SymbolType type) {
}
