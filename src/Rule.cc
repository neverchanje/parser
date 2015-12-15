//
// Created by neverchanje on 12/11/15.
//

#include <vector>
#include <boost/make_unique.hpp>
#include "Rule.h"

using namespace parser;

static std::vector<std::unique_ptr<Rule> > globRuleTable;
static size_t nRules = 0;

const Rule &RuleTable::GetRule(RuleID id) {
  return *globRuleTable[id];
}

const Rule &RuleTable::AddRule(std::unique_ptr<Rule> &&pRule) {
  globRuleTable.push_back(pRule.release());
  return *globRuleTable[nRules++];
}

void Rule::Dump() const {

}
