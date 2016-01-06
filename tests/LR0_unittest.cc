//
// Created by neverchanje on 12/23/15.
//

#include <gtest/gtest.h>
#include "LR0.h"
#include "AutomatonTestHelper.h"

using namespace parser;

TEST(LR0_Basics1, LR0_Basics1_Test) {
  RuleTable::Clear();

  Symbol::Make("S", Symbol::Type::NONTERMINAL);
  Symbol::Make("S_", Symbol::Type::NONTERMINAL);
  Symbol::Make("L", Symbol::Type::NONTERMINAL);
  Symbol::Make("R", Symbol::Type::NONTERMINAL);
  Symbol::Make("=", Symbol::Type::TERMINAL);
  Symbol::Make("*", Symbol::Type::TERMINAL);
  Symbol::Make("id", Symbol::Type::TERMINAL);

  SymbolTable::Pack();

  SymbolID
      S_ = SymbolTable::GetSymbol("S_").GetID(),
      S = SymbolTable::GetSymbol("S").GetID(),
      L = SymbolTable::GetSymbol("L").GetID(),
      R = SymbolTable::GetSymbol("R").GetID(),
      equal = SymbolTable::GetSymbol("=").GetID(),
      multiply = SymbolTable::GetSymbol("*").GetID(),
      id = SymbolTable::GetSymbol("id").GetID();

//  S_ -> S $
//  S -> L = R $
//  S -> R $
//  L -> * R $
//  L -> id $
//  R -> L $
  RuleID
      r1 = Rule::Make(S_, {S}).GetID(),
      r2 = Rule::Make(S, {L, equal, R}).GetID(),
      r3 = Rule::Make(S, {R}).GetID(),
      r4 = Rule::Make(L, {multiply, R}).GetID(),
      r5 = Rule::Make(L, {id}).GetID(),
      r6 = Rule::Make(R, {L}).GetID();

  auto actual = LR0::Automaton::Make(r1);

//  <from:8, sym:L, to:7>
//  <from:8, sym:R, to:9>
//  <from:8, sym:id, to:2>
//  <from:8, sym:*, to:1>
//  <from:1, sym:L, to:7>
//  <from:1, sym:R, to:6>
//  <from:1, sym:id, to:2>
//  <from:1, sym:*, to:1>
//  <from:5, sym:=, to:8>
//  <from:0, sym:L, to:5>
//  <from:0, sym:R, to:4>
//  <from:0, sym:S, to:3>
//  <from:0, sym:id, to:2>
//  <from:0, sym:*, to:1>
  actual.Dump();

  DFA expect;
  expect.AddTrans(8, L, 7);
  expect.AddTrans(8, R, 9);
  expect.AddTrans(8, id, 2);
  expect.AddTrans(8, multiply, 1);
  expect.AddTrans(1, L, 7);
  expect.AddTrans(1, R, 6);
  expect.AddTrans(1, id, 2);
  expect.AddTrans(1, multiply, 1);
  expect.AddTrans(5, equal, 8);
  expect.AddTrans(0, L, 5);
  expect.AddTrans(0, R, 4);
  expect.AddTrans(0, S, 3);
  expect.AddTrans(0, id, 2);
  expect.AddTrans(0, multiply, 1);
  EXPECT_PRED_FORMAT2 (AssertDFACmp, expect, actual.GetDFA());
}


TEST(LR0_Basics2, LR0_Basics2_Test) {
  RuleTable::Clear();

  Symbol::Make("E_", Symbol::Type::NONTERMINAL);
  Symbol::Make("E", Symbol::Type::NONTERMINAL);
  Symbol::Make("T", Symbol::Type::NONTERMINAL);
  Symbol::Make("F", Symbol::Type::NONTERMINAL);
  Symbol::Make("+", Symbol::Type::TERMINAL);
  Symbol::Make("*", Symbol::Type::TERMINAL);
  Symbol::Make("(", Symbol::Type::TERMINAL);
  Symbol::Make(")", Symbol::Type::TERMINAL);
  Symbol::Make("id", Symbol::Type::TERMINAL);
  Symbol::EOR();

  SymbolTable::Pack();

  SymbolID
      E_ = SymbolTable::GetSymbol("E_").GetID(),
      E = SymbolTable::GetSymbol("E").GetID(),
      T = SymbolTable::GetSymbol("T").GetID(),
      F = SymbolTable::GetSymbol("F").GetID(),
      plus = SymbolTable::GetSymbol("+").GetID(),
      right_bracket = SymbolTable::GetSymbol(")").GetID(),
      left_bracket = SymbolTable::GetSymbol("(").GetID(),
      multiply = SymbolTable::GetSymbol("*").GetID(),
      id = SymbolTable::GetSymbol("id").GetID();

  // E_ -> E
  // E -> E + T
  // E -> T
  // T -> T * F
  // T -> F
  // F -> (E)
  // F -> id
  RuleID
      r0 = Rule::Make(E_, {E}).GetID(),
      r1 = Rule::Make(E, {E, plus, T}).GetID(),
      r2 = Rule::Make(E, {T}).GetID(),
      r3 = Rule::Make(T, {T, multiply, F}).GetID(),
      r4 = Rule::Make(T, {F}).GetID(),
      r5 = Rule::Make(F, {left_bracket, E, right_bracket}).GetID(),
      r6 = Rule::Make(F, {id}).GetID();

  auto atm = LR0::Automaton::Make(r0);

//  <from:8, sym:T, to:11>
//  <from:8, sym:(, to:2>
//  <from:8, sym:F, to:3>
//  <from:8, sym:id, to:1>
//  <from:7, sym:(, to:2>
//  <from:7, sym:F, to:10>
//  <from:7, sym:id, to:1>
//  <from:6, sym:+, to:8>
//  <from:6, sym:), to:9>
//  <from:4, sym:*, to:7>
//  <from:2, sym:E, to:6>
//  <from:2, sym:T, to:4>
//  <from:2, sym:(, to:2>
//  <from:2, sym:F, to:3>
//  <from:2, sym:id, to:1>
//  <from:5, sym:+, to:8>
//  <from:11, sym:*, to:7>
//  <from:0, sym:E, to:5>
//  <from:0, sym:T, to:4>
//  <from:0, sym:(, to:2>
//  <from:0, sym:F, to:3>
//  <from:0, sym:id, to:1>
  atm.Dump();
}