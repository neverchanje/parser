//
// Created by neverchanje on 12/24/15.
//

#include <cassert>
#include "First.h"
#include "Rule.h"

namespace parser {

static std::vector<SymbolSet> globFirst;

// Calculate FIRST(X) and add it to symset, X is a non-terminal.
// return true if there's an epsilon production.
static bool insertNonTermFirst(SymbolSet &symset, SymbolID X) {
  // X is a non-terminal
  // If X -> Y1 Y2 ... Yi ... Yn $ is a production

  if (!globFirst[X].empty()) {
    symset.insert(globFirst[X].begin(), globFirst[X].end());

    // if FIRST(X) = $, then it's a epsilon production
    return globFirst[X].find(Symbol::EOR().GetID()) != globFirst[X].end();
  }

  bool ret = false;
  const auto &derives = RuleTable::GetDerives(X);

  for (auto rid: derives) {
    const Rule &rule = RuleTable::GetRule(rid);
    SymbolID Y;

    // if X -> $ is a production, then add $ to FIRST(X)
    if (rule.GetRHS(0) == Symbol::EOR().GetID()) {
      assert(rule.GetRHSSize() > 0);
      ret = true;
      symset.insert(Symbol::EOR().GetID());
      continue;
    }

    for (size_t i = 0; i < rule.GetRHSSize() - 1; i++) {
      Y = rule.GetRHS(i);

      // to prevent recursive calculation.
      if (Y == X) {
        break;
      }

      if (Symbol::IsTerminal(Y)) {
        symset.insert(Y);
        ret = false;
        break;
      } else if (!insertNonTermFirst(symset, Y)) {
        ret = false;
        break;
      }
    }
  }
  return ret;
}


/// NOTE: FIRST($) = $
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
