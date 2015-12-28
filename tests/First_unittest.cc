//
// Created by neverchanje on 12/26/15.
//

#include <gtest/gtest.h>

#include "First.h"
#include "Rule.h"

using namespace parser;

TEST(First_Basics1, First_Basics1_Test) {

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

  InitFirst();

  EXPECT_EQ(SymbolSet({multiply, id}), First(S));

  EXPECT_EQ(SymbolSet({multiply, id}), First(L));
}

TEST(First_Basics2, First_Basics2_Test) {
  RuleTable::Clear();

  Symbol::Make("E", Symbol::Type::NONTERMINAL);
  Symbol::Make("F", Symbol::Type::NONTERMINAL);
  Symbol::Make("(", Symbol::Type::TERMINAL);
  Symbol::Make(")", Symbol::Type::TERMINAL);
  Symbol::Make("id", Symbol::Type::TERMINAL);

  SymbolTable::Pack();

  SymbolID
      E = SymbolTable::GetSymbol("E").GetID(),
      F = SymbolTable::GetSymbol("F").GetID(),
      right_bracket = SymbolTable::GetSymbol(")").GetID(),
      left_bracket = SymbolTable::GetSymbol("(").GetID(),
      id = SymbolTable::GetSymbol("id").GetID();

  // F -> (E)
  // F -> id
  RuleID
      r0 = Rule::Make(F, {left_bracket, E, right_bracket}).GetID(),
      r1 = Rule::Make(F, {id}).GetID();

  InitFirst();

  EXPECT_EQ(SymbolSet({left_bracket, id}), First(F));

  // The production T -> T * F is left-recursive.
//  EXPECT_EQ(SymbolSet({left_bracket, id}), First(T));
}

TEST(First_Basics3, First_Basics3_Test) {
  RuleTable::Clear();

  Symbol::Make("S", Symbol::Type::NONTERMINAL);
  Symbol::Make("A", Symbol::Type::NONTERMINAL);
  Symbol::Make("B", Symbol::Type::NONTERMINAL);
  Symbol::Make("a", Symbol::Type::TERMINAL);
  Symbol::Make("C", Symbol::Type::NONTERMINAL);

  SymbolTable::Pack();

  SymbolID
      S = SymbolTable::GetSymbol("S").GetID(),
      A = SymbolTable::GetSymbol("A").GetID(),
      B = SymbolTable::GetSymbol("B").GetID(),
      C = SymbolTable::GetSymbol("C").GetID(),
      a = SymbolTable::GetSymbol("a").GetID(),
      eor = SymbolTable::GetSymbol("$").GetID();

//  S -> A
//  A -> B
//  B -> a | C
//  C -> $
  RuleID
      r0 = Rule::Make(S, {A}).GetID(),
      r1 = Rule::Make(A, {B}).GetID(),
      r2 = Rule::Make(B, {a}).GetID(),
      r3 = Rule::Make(B, {C}).GetID(),
      r4 = Rule::MakeEps(C).GetID();

  RuleTable::Dump();
  InitFirst();

  EXPECT_EQ(SymbolSet({eor}), First(C));
  EXPECT_EQ(SymbolSet({a, eor}), First(B));
}
