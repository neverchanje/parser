//
// Created by neverchanje on 12/23/15.
//

#include "AutomatonTestHelper.h"
#include "LR1.h"

using namespace parser;

TEST(LR1_Basics1, LR1_Basics1_Test) {
  RuleTable::Clear();

  Symbol::Make("S_", Symbol::Type::NONTERMINAL);
  Symbol::Make("S", Symbol::Type::NONTERMINAL);
  Symbol::Make("C", Symbol::Type::NONTERMINAL);
  Symbol::Make("c", Symbol::Type::TERMINAL);
  Symbol::Make("d", Symbol::Type::TERMINAL);

  SymbolTable::Pack();

  SymbolID
      S_ = SymbolTable::GetSymbol("S_").GetID(),
      S = SymbolTable::GetSymbol("S").GetID(),
      C = SymbolTable::GetSymbol("C").GetID(),
      c = SymbolTable::GetSymbol("c").GetID(),
      d = SymbolTable::GetSymbol("d").GetID();

//  S_ → S
//  S → CC
//  C → cC
//  C → d
  RuleID
      r1 = Rule::Make(S_, {S}).GetID(),
      r2 = Rule::Make(S, {C, C}).GetID(),
      r3 = Rule::Make(C, {c, C}).GetID(),
      r4 = Rule::Make(C, {d}).GetID();

  auto actual = LR1::Automaton::Make(r1);

  DFA expect;
  expect.AddTrans(0, S, 1);
  expect.AddTrans(0, C, 2);
  expect.AddTrans(0, c, 3);
  expect.AddTrans(0, d, 4);
  expect.AddTrans(2, C, 5);
  expect.AddTrans(2, c, 6);
  expect.AddTrans(2, d, 7);
  expect.AddTrans(3, C, 8);
  expect.AddTrans(3, c, 3);
  expect.AddTrans(3, d, 4);
  expect.AddTrans(6, C, 9);
  expect.AddTrans(6, c, 6);

  EXPECT_PRED_FORMAT2 (AssertDFACmp, expect, actual.GetDFA());
}