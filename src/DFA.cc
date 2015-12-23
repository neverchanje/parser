//
// Created by neverchanje on 12/22/15.
//

#include "DFA.h"

namespace parser {

typedef DFA::State State;

void DFA::AddTrans(State from, SymbolID sym, State to) {
  trans_[from][sym] = to;
}

bool DFA::HasTrans(State from, SymbolID sym) const {
  if (trans_.find(from) == trans_.end()) {
    return false;
  }
  auto &t1 = trans_.find(from)->second;
  return (t1.find(sym) != t1.end());
}

State DFA::GetTrans(State from, SymbolID sym) const {
  return trans_.find(from)->second.find(sym)->second;
}

void DFA::Dump() const {
  for (auto t1 = trans_.begin(); t1 != trans_.end(); t1++) {
    for (auto t2 = (*t1).second.begin(); t2 != (*t1).second.end(); t2++) {
      fprintf(stderr, "<from:%d, sym:%d, to:%d>\n",
              (*t1).first, (*t2).first, (*t2).second);
    }
  }
}

} // namespace parser