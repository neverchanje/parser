//
// Created by neverchanje on 12/22/15.
//

#ifndef PARSER_ITEM_H
#define PARSER_ITEM_H

#include <set>
#include <boost/any.hpp>
#include <boost/operators.hpp>
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

  // The return value of AtEnd denotes whether the item hits the end, which means
  // its dot is on the left of the end symbol $.
  bool AtEnd() const {
    return RuleTable::GetRule(rule_id).GetRHSSize() <= offset;
  }

  bool operator==(const Item &rhs) const {
    return rule_id == rhs.rule_id && offset == rhs.offset
        && CompareOthers(rhs) && CompareOthers(*this);
  }

  // return true if Others() < rhs.Others();
  // return false here, since it's not required to be implemented in Item.
  virtual bool CompareOthers(const Item &rhs) const {
    return false;
  }

  virtual boost::any Others() const {
    return 0;
  }

  virtual std::string ToString() const;

  void Print() const {
    fprintf(stderr, "%s\n", ToString().c_str());
  }

  // TODO: return value should be unique_ptr
  virtual Item Next() const {
    return Item(rule_id, offset + 1);
  }
};

typedef std::unique_ptr<Item> UPItem;

namespace detail {

struct ItemPtrLess {
// Each item A -> a •X b in ItemSet I are sorted by X in ascending order,
// so that items can be grouped by different X.
  inline bool operator()(const UPItem &p1, const UPItem &p2) const {
    SymbolID x1 = p1->GetPointed();
    SymbolID x2 = p2->GetPointed();
    if (x1 == x2) {
      std::pair<RuleID, size_t> i1(p1->rule_id, p1->offset);
      std::pair<RuleID, size_t> i2(p2->rule_id, p2->offset);
      if (i2 == i1) {
        return p1->CompareOthers(*p2);
      }
      return i1 < i2;
    }
    return x1 < x2;
  }
};

} // namespace detail

// Each item A -> a •X b in ItemSet I are sorted by X in ascending order,
// so that items can be grouped by different X.
typedef std::set<UPItem, detail::ItemPtrLess> ItemSet;

} // namespace parser

#endif //PARSER_ITEM_H
