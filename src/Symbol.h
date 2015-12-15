//
// Created by neverchanje on 12/7/15.
//

#ifndef PARSER_SYMBOL_H
#define PARSER_SYMBOL_H

#include <string>

namespace parser {

typedef size_t SymbolID;

class Symbol {

 public:

  // Only terminals have a precedence.
  enum Type {
    UNKNOWN,
    NONTERMINAL,
    TERMINAL
  };

  // Return true iff the symbol id is terminal.
  static inline bool IsTerminal(SymbolID id);

  // Return true iff the symbol id is non-terminal.
  static inline bool IsNonterminal(SymbolID id);

  static Symbol Make(const std::string &tag, Type type);

 public:

  void Print() const;

  std::string GetTag() const { return tag_; }
  SymbolID GetID() const { return id_; }
  Type GetType() const { return type_; }

 private:

  Symbol(const std::string &tag, Type type);

  // Name of the symbol.
  std::string tag_;

  Type type_;

  // Each Symbol is marked by a SymbolID.
  SymbolID id_;

};

// SymbolTable is a singleton class.
class SymbolTable {

 public:

  static Symbol GetSymbol(const std::string &tag);

  static Symbol GetSymbol(SymbolID id);

  static void AddSymbol(const Symbol &sym);

  static size_t GetNSymbols();

  static size_t GetNTerminals();

  static size_t GetNNonTerminals();

};

} // namespace parser

#endif //PARSER_SYMBOL_H
