//
// Created by neverchanje on 12/7/15.
//

#include <assert.h>visu
#include <unordered_map>
#include <vector>
#include "Symbol.h"

using namespace parser;

static std::unordered_map<std::string, Symbol> globSymbolTable;
static std::vector<Symbol> globSymbols;
static size_t nTerminals = 0;
static size_t nNonterminals = 0;

bool Symbol::IsTerminal(SymbolID id) {
  return globSymbols[id].GetType() == Type::TERMINAL;
}

bool Symbol::IsNonterminal(SymbolID id) {
  return globSymbols[id].GetType() == Type::NONTERMINAL;
}

Symbol::Symbol(const std::string &tag,
               Symbol::Type type) :
    id_(globSymbols.size()),
    tag_(tag),
    type_(type) {
}

// An instance of Symbol is designed to be created by static function,
// rather than by its constructor, because C++ constructor has not completed
// the construction of the object, while in the constructor we are adding
// the symbol into the symbol-table at the same time.
Symbol Symbol::Make(const std::string &tag, Type type) {
  Symbol sym(tag, type);
  SymbolTable::AddSymbol(sym);
  return sym;
}

Symbol SymbolTable::GetSymbol(const std::string &tag) {
  return globSymbolTable[tag];
}

Symbol SymbolTable::GetSymbol(SymbolID id) {
  return globSymbols[id];
}

void SymbolTable::AddSymbol(const Symbol &sym) {
  globSymbolTable[sym.GetTag()] = sym;
  globSymbols.push_back(sym);
  if (sym.GetType() == Symbol::Type::TERMINAL)
    nTerminals++;
  else if (sym.GetType() == Symbol::Type::NONTERMINAL) {
    nNonterminals++;
  }
}

size_t SymbolTable::GetNSymbols() {
  return nTerminals + nNonterminals;
}

size_t SymbolTable::GetNTerminals() {
  return nTerminals;
}

size_t SymbolTable::GetNNonTerminals() {
  return nNonterminals;
}

void Symbol::Print() const {
  fprintf(stdout, "{ ID: %lu, TAG: %s }", id_, tag_.c_str());
}