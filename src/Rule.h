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
typedef int ItemID;

/**
 * Rule:
 * lhs -> rhs1 rhs2 ... rhs{RHSSize}
 */
template<size_t RHSSize>
class Rule {

 public:

  void Dump();

  void DumpLHS();

  void DumpRHS();

  // Return the length of the rhs.
  size_t GetRHSSize() { return RHSSize; }

 private:

  SymbolID lhs_;

  // +1 for the end symbol $
  std::array<ItemID, RHSSize + 1> rhs_;

};

} // namespace parser

#endif //PARSER_RULE_H
