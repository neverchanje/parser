//
// Created by neverchanje on 12/30/15.
//

#ifndef PARSER_ITEMSETTESTHELPER_H
#define PARSER_ITEMSETTESTHELPER_H

#include <gtest/gtest.h>
#include <boost/make_unique.hpp>
#include "LAItem.h"

namespace parser {

// For the use of gtest.
inline bool ItemSetCmp(const ItemSet &lhs,
                       const ItemSet &rhs) {
  return rhs.size() == lhs.size() &&
      std::equal(lhs.begin(), lhs.end(), rhs.begin(),
                 [](const std::unique_ptr<Item> &p1,
                    const std::unique_ptr<Item> &p2) {
                   detail::ItemPtrLess cmp;
                   return !cmp(p1, p2) && !cmp(p2, p1);
                 });
}

std::unique_ptr<Item> MakeItem(RuleID r, size_t off) {
  return boost::make_unique<Item>(RuleID(r), size_t(off));
}

std::unique_ptr<LAItem> MakeLAItem(RuleID r, size_t off, SymbolID la) {
  return boost::make_unique<LAItem>(LAItem(r, off, la));
}

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
  if (ItemSetCmp(expect, actual))
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
