//
// Created by neverchanje on 12/22/15.
//

#ifndef PARSER_ITEM_H
#define PARSER_ITEM_H

#include <unordered_set>
#include <boost/functional/hash.hpp>

namespace parser {

typedef int RuleID;

typedef std::pair<RuleID, size_t> Item;

inline Item MakeItem(RuleID rule, size_t offset) {
  return std::make_pair<RuleID, size_t>(RuleID(rule), size_t(offset));
}

struct ItemHasher {
  size_t operator()(const Item &val) const {
    return boost::hash_value(val);
  }
};

typedef std::unordered_set<Item, ItemHasher> ItemSet;

} // namespace parser

#endif //PARSER_ITEM_H
