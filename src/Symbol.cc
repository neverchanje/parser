//
// Created by neverchanje on 12/7/15.
//

#include <cassert>
#include <unordered_map>
#include <vector>
#include "Symbol.h"

using namespace parser;

// Fixme: Type of value of globSymbolTable should be std::shared_ptr<Symbol>,
// since Symbol is allowed to have aliases, in other words, multiple tags
// could share a Symbol.
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

const Symbol &
Symbol::Make(const std::string &tag, Type type) {
  return SymbolTable::AddSymbol(std::unique_ptr<Symbol>(new Symbol(tag, type)));
}

Symbol::Symbol() :
    type_(Type::UNKNOWN),
    id_(UNDEFINED_ID) {
}

const Symbol &
SymbolTable::GetSymbol(const std::string &tag) {
  return *globSymbolTable[tag];
}

const Symbol &
SymbolTable::GetSymbol(SymbolID id) {
  return Symbol::IsTerminal(id) ? *globTerminals[id] : *globNonTerminals[id];
}

const Symbol &
SymbolTable::AddSymbol(std::unique_ptr<Symbol> &&pSym) {
  std::string tag = pSym->GetTag();
  const auto &pRet = globSymbolTable[std::move(tag)] = std::move(pSym);

  if (pSym->GetType() == Symbol::Type::TERMINAL) {
    nTerminals++;
  } else if (pSym->GetType() == Symbol::Type::NONTERMINAL) {
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

void Symbol::SetID(SymbolID id) {
  assert(id_ == UNDEFINED_ID);
  id_ = id;
}

void SymbolTable::Pack() {
  globTerminals = std::vector<std::unique_ptr<Symbol> >(nTerminals);
  globNonTerminals = std::vector<std::unique_ptr<Symbol> >(nNonTerminals);
  nTerminals = nNonTerminals = 0;

  for (auto &it : globSymbolTable) {
    auto &pSym = it.second;
    Symbol::Type type = pSym->GetType();
    SymbolID id;

    if (type == Symbol::Type::TERMINAL) {
      globTerminals[nTerminals] = std::unique_ptr<Symbol>(new Symbol(*pSym));
      id = static_cast<int>(nTerminals);
      globTerminals[nTerminals]->SetID(id);
      pSym->SetID(id);
      nTerminals++;
    } else if (type == Symbol::Type::NONTERMINAL) {
      globNonTerminals[nNonTerminals] = std::unique_ptr<Symbol>(new Symbol(*pSym));
      id = static_cast<int>(nNonTerminals);
      globNonTerminals[nNonTerminals]->SetID(id);
      pSym->SetID(id);
      nNonTerminals++;
    }
  }
}

void SymbolTable::Dump() {
  fprintf(stderr, "\n------- Beginning of dumping the SymbolTable. -------\n");
  fprintf(stderr, "NTerminals: %lu, NNonTerminals: %lu\n", nTerminals, nNonTerminals);
  fprintf(stderr, "Symbols: \n");
  for (const auto &it : globSymbolTable) {
    const auto &pSym = it.second;
    pSym->Print();
    fputs("", stderr);
  }
  fprintf(stderr, "------- Ending of dumping the SymbolTable. -------\n");
}