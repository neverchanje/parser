//
// Created by neverchanje on 12/7/15.
//

#ifndef PARSER_SYMBOL_H
#define PARSER_SYMBOL_H

#include <string>
#include <unordered_map>

namespace parser {

typedef size_t SymbolID;

class Symbol {

 public:

  // Only terminals have a precedence.
  enum SymbolType {
    UNKNOWN,
    NONTERMINAL,
    TERMINAL
  };

  // Total number of terminals.
  static size_t NTerminals = 0;

  // Total number of non-terminals.
  static size_t NNonTerminals = 0;

  // Return true iff the symbol id is terminal.
  static inline bool IsTerminal(SymbolID id);

  // Return true iff the symbol id is non-terminal.
  static inline bool IsNonterminal(SymbolID id);

  // An instance of Symbol is designed to be created by static function,
  // rather than by its constructor, because C++ constructor has not completed
  // the construction of the object, while in the constructor we are adding
  // the symbol into the symbol-table at the same time.
  static Symbol MakeSymbol(const std::string &tag, SymbolType type);

 public:

  void Print() const;

 private:

  Symbol(const std::string &tag, SymbolType type);

  // Name of the symbol.
  std::string tag_;

  SymbolType type_;

  // Each Symbol is marked by a SymbolID.
  SymbolID id_;

};

// SymbolTable is a singleton here, so we declare it as a namespace and wrap its
// methods as static functions, hide its private members in Symbol.cc.
namespace SymbolTable {

Symbol GetSymbol(const std::string& tag);

void AddSymbol(const Symbol& symbol);

} // namespace SymbolTable

} // namespace parser

#endif //PARSER_SYMBOL_H
