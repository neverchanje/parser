//
// Created by neverchanje on 12/7/15.
//

#include <assert.h>
#include <unordered_map>
#include <vector>
#include <boost/make_unique.hpp>
#include "Symbol.h"

using namespace parser;

static std::unordered_map<std::string, std::unique_ptr<Symbol> > globSymbolTable;
static std::vector<std::unique_ptr<Symbol> > globTerminals;
static std::vector<std::unique_ptr<Symbol> > globNonTerminals;

static size_t nTerminals = 0;
static size_t nNonTerminals = 0;

bool Symbol::IsTerminal(SymbolID id) {
  return id >= 0 && id < nTerminals;
}

bool Symbol::IsNonTerminal(SymbolID id) {
  return id >= nTerminals;
}

Symbol::Symbol(const std::string &tag,
               Symbol::Type type) :
    id_(UNDEFINED_ID),
    tag_(tag),
    type_(type) {
}

const Symbol &Symbol::Make(const std::string &tag, Type type) {
  return SymbolTable::AddSymbol(std::unique_ptr<Symbol>(new Symbol(tag, type)));
}

Symbol::Symbol() :
    type_(Type::UNKNOWN),
    id_(UNDEFINED_ID) {
}

const Symbol &SymbolTable::GetSymbol(const std::string &tag) {
  return *globSymbolTable[tag];
}

const Symbol &SymbolTable::GetSymbol(SymbolID id) {
  return Symbol::IsTerminal(id) ? *globTerminals[id] : *globNonTerminals[id];
}

const Symbol &SymbolTable::AddSymbol(std::unique_ptr<Symbol> &&pSym) {
  const auto &pRet = globSymbolTable[pSym->GetTag()] = std::move(pSym);
  if (pSym->GetType() == Symbol::Type::TERMINAL)
    nTerminals++;
  else if (pSym->GetType() == Symbol::Type::NONTERMINAL) {
    nNonTerminals++;
  }
  return *pRet;
}

size_t SymbolTable::GetNSymbols() {
  return nTerminals + nNonTerminals;
}

size_t SymbolTable::GetNTerminals() {
  return nTerminals;
}

size_t SymbolTable::GetNNonTerminals() {
  return nNonTerminals;
}

void Symbol::Print() const {
  fprintf(stderr, "{ ID: %d, TAG: %s }", id_, tag_.c_str());
}

void SymbolTable::Pack() {
  for (const auto &it : globSymbolTable) {
    const auto &pSym = it.second;
    Symbol::Type type = pSym->GetType();
    if (type == Symbol::Type::TERMINAL) {
      globTerminals.push_back(std::unique_ptr<Symbol>(new Symbol(*pSym)));
    } else if (type == Symbol::Type::NONTERMINAL) {
      globNonTerminals.push_back(std::unique_ptr<Symbol>(new Symbol(*pSym)));
    }
  }
}

void SymbolTable::Dump() {
  fprintf(stderr, "\n------- Begining of dumping the SymbolTable. -------\n");
  fprintf(stderr, "NTerminals: %lu, NNonTerminals: %lu\n", nTerminals, nNonTerminals);
  fprintf(stderr, "Symbols: \n");
  for (const auto &it : globSymbolTable) {
    const auto &pSym = it.second;
    pSym->Print();
    fputs("", stderr);
  }
  fprintf(stderr, "------- Ending of dumping the SymbolTable. -------\n");
}