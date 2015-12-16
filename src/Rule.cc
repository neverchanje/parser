//
// Created by neverchanje on 12/11/15.
//

#include <vector>
#include "Rule.h"

using namespace parser;

static std::vector<std::unique_ptr<Rule> > globRuleTable;
static std::vector<SymbolID> globRItems;

const Rule &
Rule::Make(SymbolID lhs, std::vector<SymbolID> &&rhs) {
  return RuleTable::AddRule(std::unique_ptr<Rule>(new Rule(lhs, std::move(rhs))));
}

Rule::Rule(SymbolID lhs, std::vector<SymbolID> &&rhs) :
    lhs_(lhs),
    rhs_(rhs) {
  rhs_.push_back(0);
}

void Rule::Dump() const {
  std::string ostr = SymbolTable::GetSymbol(lhs_).GetTag() + " -> ";
  for (int i = 0; i < rhs_.size(); ++i) {
    ostr += SymbolTable::GetSymbol(rhs_[i]).GetTag();
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
