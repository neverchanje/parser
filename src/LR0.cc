//
// Created by neverchanje on 12/7/15.
//

#include <vector>
#include <queue>
#include <unordered_map>
#include <boost/functional/hash.hpp>
#include "LR0.h"
#include "Closure.h"

namespace parser {

namespace LR0 {

static inline std::vector<Item> itemSetToVector(const ItemSet &I) {
  return std::vector<Item>(I.begin(), I.end());
}

struct ItemSetHasher {
  size_t operator()(const ItemSet &val) const {
    return boost::hash_value(val);
  }
};

typedef std::unordered_map<ItemSet, DFA::State, ItemSetHasher> StateTable;

#define QBACK_ISET(que) (que.back()->first)
#define QBACK_STATE(que) (que.back()->second)
#define QFRONT_ISET(que) (que.front()->first)
#define QFRONT_STATE(que) (que.front()->second)

static inline std::pair<StateTable::iterator, bool>
insertInTable(StateTable &table, ItemSet &&iset, DFA::State &&state) {
  return table.insert(std::make_pair(iset, state));
}

Automaton Automaton::Make(RuleID init) {
  Automaton atm;

  //Each ItemSet in stateSet contains only kernel items.
  StateTable table;
  std::queue<StateTable::iterator> que;
  SymbolID X, Y;
  ItemSet clsr, tmp;
  std::pair<StateTable::iterator, bool> ret;

  ret = insertInTable(table, {Item(init, 0)}, DFA::State(DFA::START_STATE));
  que.push(ret.first);

  while (!que.empty()) {
    const auto &I = QFRONT_ISET(que); // I contains only kernel items.
    clsr = Closure(itemSetToVector(I));
    DumpClosure(clsr);
    tmp.clear();

    for (auto i = clsr.begin(); i != clsr.end(); i++) {
      const Rule &rule = i->GetRule();
      if (rule.GetRHSSize() <= i->offset) { // hit the end
        continue;
      }

      // There's an X exists so that item A -> a •X b is in ItemSet I
      X = i->GetPointed();

      // Y is the symbol id pointed by the next item.
      // If X exists, then Y must exist.
      if (std::next(i) == clsr.end()) {
        Y = -1;
      } else {
        auto ni = std::next(i);
        Y = ni->GetPointed();
      }

      tmp.insert(Item(i->rule_id, i->offset + 1));
      if (X != Y) {
        ret = insertInTable(table, std::move(tmp), -1);
        if (ret.second) {
          ret.first->second = atm.dfa_.MakeState();
          que.push(ret.first);
        }
        atm.dfa_.AddTrans(QFRONT_STATE(que), X, ret.first->second);
        tmp.clear();
      }
    }

    que.pop();
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