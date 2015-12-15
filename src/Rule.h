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

typedef size_t RuleID;
typedef SymbolID ItemID;

/**
 * Rule:
 * lhs -> rhs1 rhs2 ...
 */
class Rule {

 public:

  static const Rule &Make(SymbolID lhs, std::vector<ItemID> &&rhs);

 public:

  void Dump() const;

  // Return the length of the rhs.
  size_t GetRHSSize() const { return rhs_.size(); }

 private:

  Rule(SymbolID lhs, std::vector<ItemID> &&rhs);

  SymbolID lhs_;

  // +1 for the end symbol $
  std::vector<ItemID> rhs_;

  RuleID id_;

};

class RuleTable {

 public:

  static const Rule &GetRule(RuleID id);

  static const Rule &AddRule(std::unique_ptr<Rule> &&pRule);

  static size_t GetNRule();

};

} // namespace parser

#endif //PARSER_RULE_H
