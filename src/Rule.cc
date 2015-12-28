//
// Created by neverchanje on 12/11/15.
//

#include <vector>
#include <unordered_map>
#include "Rule.h"

using namespace parser;

static std::vector<std::unique_ptr<Rule> > globRuleTable;
static std::vector<SymbolID> globRItems;
static std::unordered_map<SymbolID, std::vector<RuleID> > globDerives;
static RuleID maxRuleID = 0;

const Rule &
Rule::Make(SymbolID lhs, std::vector<SymbolID> &&rhs) {
  const Rule &ret = RuleTable::AddRule(std::unique_ptr<Rule>(new Rule(lhs, std::move(rhs))));

  // rhs1 rhs2 ... rhsn EOR
  for (size_t i = 0; i < rhs.size(); i++)
    globRItems.push_back(rhs[i]);
  globRItems.push_back(Symbol::EOR().GetID());

  globDerives[lhs].push_back(ret.GetID());
  return ret;
}

const Rule &Rule::MakeEps(SymbolID lhs) {
  return Make(lhs, std::vector<SymbolID>());
}

Rule::Rule(SymbolID lhs, std::vector<SymbolID> &&rhs) :
    lhs_(lhs),
    rhssize_(rhs.size() + 1), // +1 for EOR
    rhs_offset_(globRItems.size()),
    id_(maxRuleID++) {
}

SymbolID Rule::GetRHS(size_t n) const {
  return globRItems[rhs_offset_ + n];
}

void Rule::Dump() const {
  std::string ostr = SymbolTable::GetSymbol(lhs_).GetTag() + " ->";
  for (size_t i = 0; i < rhssize_; ++i) {
    ostr += " " + SymbolTable::GetSymbol(GetRHS(i)).GetTag();
  }
  fprintf(stderr, "%s\n", ostr.c_str());
}

const Rule &RuleTable::GetRule(RuleID id) {
  return *globRuleTable[id];
}

const Rule &RuleTable::AddRule(std::unique_ptr<Rule> &&pRule) {
  globRuleTable.push_back(std::move(pRule));
  return *globRuleTable.back();
}

size_t RuleTable::GetNRule() {
  return globRuleTable.size();
}

void RuleTable::Dump() {
  fprintf(stderr, "\n------- Beginning of dumping the RuleTable. -------\n");

  for (auto &entry : globDerives) {
    SymbolID lhs = entry.first;
    for (auto &ruleid : entry.second) {
      RuleTable::GetRule(ruleid).Dump();
    }
  }

  fprintf(stderr, "------- Ending of dumping the RuleTable. -------\n");
}

void RuleTable::Clear() {
  globRuleTable.clear();
  globDerives.clear();
  globRItems.clear();
  SymbolTable::Clear();
  maxRuleID = 0;
}

const std::vector<RuleID> &
RuleTable::GetDerives(SymbolID sym) {
  return globDerives[sym];
}
