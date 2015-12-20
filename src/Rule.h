//
// Created by neverchanje on 12/11/15.
//

#ifndef PARSER_RULE_H
#define PARSER_RULE_H

#include <vector>
#include "Symbol.h"

namespace parser {

/**
 * Production Rule.
 * See https://en.wikipedia.org/wiki/Production_(computer_science)
 * for the definition of production.
 */
typedef int RuleID;

/**
 * Rule:
 * lhs -> rhs1 rhs2 ...
 */
class Rule {

 public:

  static const Rule &Make(SymbolID lhs, std::vector<SymbolID> &&rhs);

 public:

  void Dump() const;

  // Return the length of the rhs.
  size_t GetRHSSize() const { return rhssize_; }

  SymbolID GetLHS() const { return lhs_; }

  // Return the nth SymbolID in the right hand side of the Rule.
  // n is ranging from 0 to rhssize-1;
  SymbolID GetRHS(size_t n) const;

  RuleID GetID() const { return id_; }

 private:

  Rule(SymbolID lhs, std::vector<SymbolID> &&rhs);

  SymbolID lhs_;

  size_t rhs_offset_;
  size_t rhssize_;

  RuleID id_;

};

// RuleTable is a singleton class.
class RuleTable {

 public:

  static const Rule &GetRule(RuleID id);

  static const Rule &AddRule(std::unique_ptr<Rule> &&pRule);

  // Return the total number of rules.
  static size_t GetNRule();

  static const std::vector<RuleID> &GetDerives(SymbolID sym);

  // (DEBUG) Print out all of the rules in the RuleTable.
  static void Dump();

  // (DEBUG) Clear up the RuleTable.
  static void Clear();

 private:

  RuleTable() = default;
  RuleTable(const RuleTable &) = delete;
  void operator=(const RuleTable &) = delete;

};

} // namespace parser

#endif //PARSER_RULE_H
