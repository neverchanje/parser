//
// Created by neverchanje on 12/24/15.
//

#include "First.h"
#include "Rule.h"

namespace parser {

static std::vector<SymbolSet> globFirst;

// calculate FIRST(X) and add it to symset, X is a non-terminal.
// return true if X -> epsilon is a production.
static bool insertNonTermFirst(SymbolSet &symset, SymbolID X) {
  // X is a non-terminal
  // If X -> Y1 Y2 ... Yi ... Yn is a production

  if (!globFirst[X].empty()) {
    symset.insert(globFirst[X].begin(), globFirst[X].end());
    // If epsilon is in the set of FIRST(X), then X -> epsilon must be a production.
    return globFirst[X].find(Symbol::Epsilon().GetID()) != globFirst[X].end();
  }

  bool ret = false;
  const auto &derives = RuleTable::GetDerives(X);

  for (auto rid: derives) {
    const Rule &rule = RuleTable::GetRule(rid);
    SymbolID Y;

    for (size_t i = 0; i < rule.GetRHSSize(); i++) {
      Y = rule.GetRHS(i);

      // to prevent recursive calculation.
      if (Y == X) {
        break;
      }

      if (Symbol::IsTerminal(Y)) {
        symset.insert(Y);
        if (Y != Symbol::Epsilon().GetID()) {
          ret = false;
          break;
        }
      } else {
        if (!insertNonTermFirst(symset, Y)) {
          ret = false;
          break;
        }
      }
    }
  }
  return ret;
}

const SymbolSet &
First(SymbolID X) {
  if (!globFirst[X].empty()) {
    return globFirst[X];
  }
  if (Symbol::IsTerminal(X)) {
    // if X is a terminal, then FIRST(X) = {X}
    globFirst[X].insert(X);
  } else {
    insertNonTermFirst(globFirst[X], X);
  }
  return globFirst[X];
}

void InitFirst() {
  globFirst.resize(SymbolTable::GetNSymbols());
}

} // namespace parser
