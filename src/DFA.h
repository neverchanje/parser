//
// Created by neverchanje on 12/22/15.
//

#ifndef PARSER_DFA_H

#include <unordered_map>

namespace parser {

typedef int SymbolID;

/**
 * Deterministic Finite Automaton
 */
class DFA {

 public:

  typedef int State;

  static const State START_STATE = 0;

  // DFA is created with a start state.
  DFA() :
      start_(START_STATE),
      maxStateId_(1) {
  }

  int NumOfStates() const { return maxStateId_; }

  State MaxStateId() const { return maxStateId_; }

  State MakeState() { return maxStateId_++; }

  void AddTrans(State from, SymbolID sym, State to);

  bool HasTrans(State from, SymbolID sym) const;

  State GetTrans(State, SymbolID sym) const;

  // Debugging method to write out all of the transitions in the DFA.
  void Dump() const;

 private:

  std::unordered_map<State, std::unordered_map<SymbolID, State> > trans_;

  State start_;

  int maxStateId_;

};

} // namespace parser

#endif //PARSER_DFA_H
