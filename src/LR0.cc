//
// Created by neverchanje on 12/7/15.
//

#include <vector>
#include <boost/make_unique.hpp>
#include <queue>
#include "LR0.h"
#include "Closure.h"

namespace parser {

namespace LR0 {

static inline std::vector<Item> itemSetToVector(const ItemSet &I) {
  return std::vector<Item>(I.begin(), I.end());
}

typedef std::pair<DFA::State, std::unique_ptr<ItemSet> > StateMap;

static StateMap inline makeStateMap(DFA::State state) {
  return std::make_pair(state, boost::make_unique<ItemSet>());
}

#define QBACK_ISET(que) (*(que.back().second))
#define QBACK_STATE(que) ((que.back().first))
#define QFRONT_ISET(que) (*(que.front().second))
#define QFRONT_STATE(que) ((que.front().first))

Automaton Automaton::Make(RuleID init) {
  Automaton atm;
  std::queue<StateMap> que;
  SymbolID X, prev;
  ItemSet clsr;

  que.push(makeStateMap(DFA::START_STATE));
  QBACK_ISET(que).insert(MakeItem(init, 0));

  while (!que.empty()) {
    auto &I = QFRONT_ISET(que); // I contains only kernel items.
    clsr = Closure(itemSetToVector(I));
    I.insert(clsr.begin(), clsr.end());

    prev = -1;

    for (auto &it : I) {
      const Rule &rule = RuleTable::GetRule(it.first);
      if (rule.GetRHSSize() <= it.second) {
        continue;
      }
      // There's an X exists so that item A -> a •X b is in ItemSet I
      X = rule.GetRHS(it.second);
      if (X != prev) {
        que.push(makeStateMap(atm.dfa_.MakeState()));
        atm.dfa_.AddTrans(QFRONT_STATE(que), X, QBACK_STATE(que));
        prev = X;
      }
      QBACK_ISET(que).insert(MakeItem(it.first, it.second + 1));
    }

    que.pop();
    break;
  }

  return atm;
}

void Automaton::Dump() const {
  const auto &trans = dfa_.GetTransTable();
  fprintf(stderr, "\n------- Begining of dumping the LR0. -------\n");
  for (auto t1 = trans.begin(); t1 != trans.end(); t1++) {
    for (auto t2 = (*t1).second.begin(); t2 != (*t1).second.end(); t2++) {
      fprintf(stderr, "<from:%d, sym:%s, to:%d>\n",
              (*t1).first,
              SymbolTable::GetSymbol((*t2).first).GetTag().c_str(),
              (*t2).second);
    }
  }
  fprintf(stderr, "------- Ending of dumping the LR0. -------\n");
}

} // namespace LR0

} // namespace parser