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

State Automaton::startState(RuleID init) {
  ItemSet iset;
  iset.insert(Item::MakeUnique(init, 0));
  return MakeState(std::move(iset), DFA::State(DFA::START_STATE));
}

#define QFRONT_ISET(que) (que.front()->first)
#define QFRONT_STATE(que) (que.front()->second)

Automaton Automaton::Make(RuleID init) {
  Automaton atm;

  //Each ItemSet in StateTable contains only kernel items.
  StateTable table;
  std::queue<StateTable::iterator> que;
  SymbolID X, Y;
  ItemSet clsr, tmp;
  std::pair<StateTable::iterator, bool> ret;

  ret = table.insert(atm.startState(init));
  que.push(ret.first);

  while (!que.empty()) {
    const auto &IS = QFRONT_ISET(que); // I contains only kernel items.
    clsr = atm.closure(IS.begin(), IS.end());
    DumpClosure(clsr);
    tmp.clear();

    for (auto i = clsr.begin(); i != clsr.end(); i++) {
      const Rule &rule = (*i)->GetRule();

      // There's an X exists so that item A -> a •X b is in ItemSet I
      X = (*i)->GetPointed();

      // Y is the symbol id pointed by the next item.
      // If X exists, then Y must exist.
      if (std::next(i) == clsr.end()) {
        Y = -1;
      } else {
        auto ni = std::next(i);
        Y = (*ni)->GetPointed();
      }

      if (!(*i)->AtEnd()) {
        tmp.insert((*i)->Next());
      }

      if (X != Y) {
        ret = table.insert(std::make_pair(std::move(tmp), -1));
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

ItemSet Automaton::closure(ItemSet::iterator first, ItemSet::iterator last) const {
  std::vector<Item> vec;
  for (auto it = first; it != last; it++) {
    vec.push_back(*(*it));
  }
  return Closure(std::move(vec));
}

} // namespace LR0

size_t ItemSetHasher::operator()(const ItemSet &val) const {
  return boost::hash_value(val);
}

} // namespace parser