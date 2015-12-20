//
// Created by neverchanje on 12/7/15.
//

#ifndef PARSER_CLOSURE_H
#define PARSER_CLOSURE_H

#include <vector>
#include <unordered_set>
#include <boost/functional/hash.hpp>

#include "Rule.h"

namespace parser {

typedef std::pair<RuleID, size_t> Item;

struct ItemHasher {
  size_t operator()(const Item &val) const {
    return boost::hash_value(val);
  }
};

typedef std::unordered_set<Item, ItemHasher> ItemSet;

inline Item MakeItem(RuleID rule, size_t offset) {
  return std::make_pair<RuleID, size_t>(RuleID(rule), size_t(offset));
}

class Closure {

 public:

  static Closure Make(std::vector<Item> &&I);

  void Dump();

  const ItemSet &GetItems() const { return items_; }

 private:

  Closure() = default;

  ItemSet items_;

};

} // namespace parser

#endif //PARSER_CLOSURE_H
