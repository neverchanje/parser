//
// Created by neverchanje on 12/22/15.
//

#ifndef PARSER_ITEM_H
#define PARSER_ITEM_H

#include <set>
#include <boost/functional/hash.hpp>
#include "Rule.h"

namespace parser {

typedef int RuleID;

struct Item {
  RuleID rule_id;
  size_t offset;

  Item() = default;

  Item(RuleID ruleID, size_t off) :
      rule_id(ruleID),
      offset(off) {
  }

  SymbolID GetPointed() const {
    return RuleTable::GetRule(rule_id).GetRHS(offset);
  }

  const Symbol &GetPointedSym() const {
    return SymbolTable::GetSymbol(GetPointed());
  }

  const Rule &GetRule() const {
    return RuleTable::GetRule(rule_id);
  }

  // The return value of AtEnd denotes that if the item hit the end, which means
  // its dot is on the left of the end symbol $.
  bool AtEnd() const {
    return RuleTable::GetRule(rule_id).GetRHSSize() <= offset;
  }

  friend std::size_t hash_value(Item const &v) {
    std::size_t seed = 0;
    boost::hash_combine(seed, v.rule_id);
    boost::hash_combine(seed, v.offset);
    return seed;
  }

  friend bool operator==(const Item &x, const Item &y) {
    return x.rule_id == y.rule_id && x.offset == y.offset;
  }

  virtual std::string ToString() const;

  virtual void Print() const;

  virtual Item Next() const {
    return Item(rule_id, offset + 1);
  }
};

namespace detail {

struct ItemPtrLess {
// Each item A -> a •X b in ItemSet I are sorted by X in ascending order,
// so that items can be grouped by different X.
  inline bool operator()(const std::unique_ptr<Item> &p1,
                         const std::unique_ptr<Item> &p2) const {
    SymbolID x1 = p1->GetPointed();
    SymbolID x2 = p2->GetPointed();
    if (x1 == x2)
      return std::pair<RuleID, size_t>(p1->rule_id, p1->offset) <
          std::pair<RuleID, size_t>(p2->rule_id, p2->offset);
    return x1 < x2;
  }
};

} // namespace detail

typedef std::set<std::unique_ptr<Item>, detail::ItemPtrLess> ItemSet;

} // namespace parser

#endif //PARSER_ITEM_H
