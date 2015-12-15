//
// Created by neverchanje on 12/11/15.
//

#ifndef PARSER_RULE_H
#define PARSER_RULE_H

#include <array>
#include "Symbol.h"

namespace parser {

/**
 * Production Rule.
 * See https://en.wikipedia.org/wiki/Production_(computer_science)
 * for the definition of production.
 */

typedef int RuleID;
typedef SymbolID ItemID;

class Rule;
class RuleTable {

 public:

  static const Rule &GetRule(RuleID id);

  static const Rule &AddRule(std::unique_ptr<Rule> &&pRule);

};


/**
 * Rule:
 * lhs -> rhs1 rhs2 ... rhs{RHSSize}
 */
template<size_t RHSSize>
class Rule {

 public:

  static const Rule &MakeRule(SymbolID lhs,
                              std::array<ItemID, RHSSize> &&rhs) {
    return RuleTable::AddRule(std::unique_ptr<Rule>(new Rule(lhs, rhs)));
  }

 public:

  void Dump() const;

  // Return the length of the rhs.
  size_t GetRHSSize() const { return RHSSize; }

 private:

  Rule(SymbolID lhs, const std::array<ItemID, RHSSize> &rhs) :
      lhs_(lhs),
      rhs_(rhs) {
    rhs_[RHSSize] = 0;
  }

  SymbolID lhs_;

  // +1 for the end symbol $
  std::array<ItemID, RHSSize + 1> rhs_;

  RuleID id_;

};

} // namespace parser

#endif //PARSER_RULE_H
