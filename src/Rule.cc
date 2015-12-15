//
// Created by neverchanje on 12/11/15.
//

#include <vector>
#include "Rule.h"

using namespace parser;

static std::vector<std::unique_ptr<Rule> > globRuleTable;

const Rule &RuleTable::GetRule(RuleID id) {
  return *globRuleTable[id];
}

const Rule &RuleTable::AddRule(std::unique_ptr<Rule> &&pRule) {
  globRuleTable.push_back(pRule.release());
  return *globRuleTable.back();
}

size_t RuleTable::GetNRule() {
  return globRuleTable.size();
}

void Rule::Dump() const {

}
