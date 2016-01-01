//
// Created by neverchanje on 1/1/16.
//

#ifndef PARSER_AUTOMATONTESTHELPER_H
#define PARSER_AUTOMATONTESTHELPER_H

#include "LR0.h"
#include <gtest/gtest.h>

namespace parser {

// For the use of gtest.
inline bool DFACmp(const DFA &lhs, const DFA &rhs) {
  return lhs.GetTransTable() == rhs.GetTransTable();
}

::testing::AssertionResult AssertItemSetCmp(const char *expect_expr,
                                            const char *actual_expr,
                                            const DFA &expect,
                                            const DFA &actual) {
  if (DFACmp(expect, actual))
    return ::testing::AssertionSuccess();

  auto res = ::testing::AssertionFailure();
  res << "Value of: " << actual_expr << std::endl;
  res << "  Actual: " << actual.ToString() << std::endl;
  res << "Expected: " << expect_expr << std::endl;
  res << "Which is: " << expect.ToString() << std::endl;
  return res;
}

} // namespace parser

#endif //PARSER_AUTOMATONTESTHELPER_H
