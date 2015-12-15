//
// Created by neverchanje on 12/7/15.
//

#include <assert.h>visu
#include <unordered_map>
#include <vector>
#include "Symbol.h"

using namespace parser;

static std::unordered_map<std::string, Symbol> globSymbolTable;
static std::vector<Symbol> globTerminals;
static std::vector<Symbol> globNonTerminals;

bool Symbol::IsTerminal(SymbolID id) {
  return id < NTerminals && id >= 0;
}

bool Symbol::IsNonterminal(SymbolID id) {
  return id >= NNonTerminals && id < NTerminals + NNonTerminals;
}

Symbol::Symbol(const std::string &tag,
               Symbol::Type type) :
    id_(NTerminals),
    tag_(tag),
    type_(type) {
  if (type == Type::NONTERMINAL)
    id_ += NONTERMINAL;
}

// An instance of Symbol is designed to be created by static function,
// rather than by its constructor, because C++ constructor has not completed
// the construction of the object, while in the constructor we are adding
// the symbol into the symbol-table at the same time.
Symbol Symbol::MakeSymbol(const std::string &tag, Type type) {
  Symbol sym(tag, type);
  SymbolTable::AddSymbol(sym);
  return sym.
}

Symbol SymbolTable::GetSymbol(const std::string &tag) {
  return globSymbolTable[tag];
}

Symbol SymbolTable::GetSymbol(SymbolID id) {
  if (Symbol::IsTerminal(id)) {
    return globTerminals[id];
  } else if (Symbol::IsNonterminal(id)) {
    return globNonTerminals[id];
  } else {
    fprintf(stderr, "Unregistered ID!");
    abort();
  }
}

void SymbolTable::AddSymbol(const Symbol &sym) {
  globSymbolTable[sym.GetTag()] = sym;
  if (sym.GetType() == Symbol::Type::NONTERMINAL) {
    globNonTerminals.push_back(sym);
    Symbol::NNonTerminals++;
    assert(Symbol::NNonTerminals == globNonTerminals.size());
  } else if (sym.GetType() == Symbol::Type::TERMINAL) {
    globTerminals.push_back(sym);
    Symbol::NTerminals++;
    assert(Symbol::NTerminals == globTerminals.size());
  }
}

void Symbol::Print() const {
  fprintf(stdout, "{ ID: %lu, TAG: %s }", id_, tag_.c_str());
}
