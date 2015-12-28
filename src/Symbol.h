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

  // Marks that no id has been assigned to the Symbol.
  // The Symbol will not own an id until SymbolTable::Pack()
  // has been processed.
  static const SymbolID UNDEFINED_ID = -1;

  // Only terminals have a precedence.
  enum Type {
    NONTERMINAL,
    TERMINAL
  };

  // Return true iff the symbol id is terminal.
  static bool IsTerminal(SymbolID id);

  // Return true iff the symbol id is non-terminal.
  static bool IsNonTerminal(SymbolID id);

  static const Symbol &Make(const std::string &tag, Type type);

  // end-of-rule symbol
  // of type TERMINAL
  static const Symbol &EOR();

 public:

  Symbol(const Symbol &) = default; // copyable.

  // Print the symbol in the form of "{ ID: id, TAG: tag }"
  void Print() const;

  std::string GetTag() const { return tag_; }
  SymbolID GetID() const { return id_; }
  Type GetType() const { return type_; }

  void SetID(SymbolID id);

 private:

  Symbol(const std::string &tag, Type type);

  // Name of the symbol.
  std::string tag_;

  Type type_;

  // Each Symbol is marked by a SymbolID.
  // ID of terminals ranges between [0, nTerminals-1],
  // ID of non-terminals ranges between [nTerminals, nTerminals+nNonTerminals-1]
  SymbolID id_;

};

// SymbolTable is a singleton class.
class SymbolTable {

 public:

  // Get the symbol by its tag.
  static const Symbol &GetSymbol(const std::string &tag);

  // Get the symbol by its corresponding SymbolID.
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

  // Pack up the SymbolTable and each of the Symbol will be marked by a SymbolID.
  // We have to do this, in order to dividing the symbols into two groups, terminals
  // and non-terminals.
  static void Pack();

  // (DEBUG) Print out all of the symbols in the SymbolTable.
  static void Dump();

  // (DEBUG) Clear up the SymbolTable.
  static void Clear();

 private:

  SymbolTable() = default;
  SymbolTable(const SymbolTable &) = delete;
  void operator=(const SymbolTable &) = delete;

};

} // namespace parser

#endif //PARSER_SYMBOL_H
