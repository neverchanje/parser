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
  globSymbolTable[tag] = sym;
  if (type == Type::NONTERMINAL) {
    globNonTerminals.push_back(sym);
    NNonTerminals++;
    assert(NNonTerminals == globNonTerminals.size());
  } else if (type == Type::TERMINAL) {
    globTerminals.push_back(sym);
    NTerminals++;
    assert(NTerminals == globTerminals.size());
  }
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

void Symbol::Print() const {
  fprintf(stdout, "{ ID: %lu, TAG: %s }", id_, tag_.c_str());
}