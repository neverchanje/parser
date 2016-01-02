//
// Created by neverchanje on 12/30/15.
//

#ifndef PARSER_ITEMSETTESTHELPER_H
#define PARSER_ITEMSETTESTHELPER_H

#include <gtest/gtest.h>
#include <boost/make_unique.hpp>
#include "LAItem.h"

namespace parser {

std::string ToString(const ItemSet &is) {
  std::string ret;
  for (auto &it : is) {
    ret += "\n" + it->ToString();
  }
  return ret;
}

::testing::AssertionResult AssertItemSetCmp(const char *expect_expr,
                                            const char *actual_expr,
                                            const ItemSet &expect,
                                            const ItemSet &actual) {
  ItemSetEqual itemset_eq_fn;
  if (itemset_eq_fn(expect, actual))
    return ::testing::AssertionSuccess();

  auto res = ::testing::AssertionFailure();
  res << "Value of: " << actual_expr << std::endl;
  res << "  Actual: " << ToString(actual) << std::endl;
  res << "Expected: " << expect_expr << std::endl;
  res << "Which is: " << ToString(expect) << std::endl;
  return res;
}

} // namespace parser

#endif //PARSER_ITEMSETTESTHELPER_H
