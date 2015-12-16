//
// Created by neverchanje on 12/7/15.
//

#ifndef PARSER_SYMBOL_H
#define PARSER_SYMBOL_H

#include <string>

namespace parser {

typedef int SymbolID;

class Symbol {

 public:

  const int UNDEFINED_ID = -1;

  // Only terminals have a precedence.
  enum Type {
    UNKNOWN,
    NONTERMINAL,
    TERMINAL
  };

  // Return true iff the symbol id is terminal.
  static inline bool IsTerminal(SymbolID id);

  // Return true iff the symbol id is non-terminal.
  static inline bool IsNonTerminal(SymbolID id);

  static const Symbol &Make(const std::string &tag, Type type);

 public:

  Symbol();
  Symbol(const Symbol &) = default; // copyable.

  // Print the symbol in the form of "{ ID: id, TAG: tag }"
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

  // Get the symbol by its tag.
  static const Symbol &GetSymbol(const std::string &tag);

  static const Symbol &GetSymbol(SymbolID id);

  // Receive a rvalue pointer of symbol created by boost::make_unique,
  // and insert the symbol into SymbolTable.
  static const Symbol &AddSymbol(std::unique_ptr<Symbol> &&pSym);

  // Return the total number of symbols (terminals + non-terminals).
  static size_t GetNSymbols();

  // Return the total number of terminals.
  static size_t GetNTerminals();

  // Return the total number of non-terminals.
  static size_t GetNNonTerminals();

  // Pack the SymbolTable and each of the Symbol will be marked by a SymbolID.
  static void Pack();

  static void Dump();

 private:

  SymbolTable() = default;
  SymbolTable(const SymbolTable &) = delete;
  void operator=(const SymbolTable &) = delete;

};

} // namespace parser

#endif //PARSER_SYMBOL_H
